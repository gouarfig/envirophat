#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

#include <wiringPi.h>
#include <wiringPiI2C.h>

#include "bmp280.h"

uint cal_t1 = 27504;
int cal_t2 = 26435;
int cal_t3 = -1000;
uint cal_p1 = 36477;
int cal_p2 = -10685;
int cal_p3 = 3024;
int cal_p4 = 2855;
int cal_p5 = 140;
int cal_p6 = -7;
int cal_p7 = 15500;
int cal_p8 = -14500;
int cal_p9 = 6000;

void bmp280_load_calibration(int fd)
{
    cal_t1 = wiringPiI2CReadReg16(fd, BMP280_DIG_T1);
    cal_t2 = wiringPiI2CReadReg16(fd, BMP280_DIG_T2);
    // TO DO: double check the value for t3
    //cal_t3 = wiringPiI2CReadReg16(fd, BMP280_DIG_T3);
    cal_p1 = wiringPiI2CReadReg16(fd, BMP280_DIG_P1);
    cal_p2 = wiringPiI2CReadReg16(fd, BMP280_DIG_P2);
    cal_p3 = wiringPiI2CReadReg16(fd, BMP280_DIG_P3);
    cal_p4 = wiringPiI2CReadReg16(fd, BMP280_DIG_P4);
    cal_p5 = wiringPiI2CReadReg16(fd, BMP280_DIG_P5);
    cal_p6 = wiringPiI2CReadReg16(fd, BMP280_DIG_P6);
    cal_p7 = wiringPiI2CReadReg16(fd, BMP280_DIG_P7);
    cal_p8 = wiringPiI2CReadReg16(fd, BMP280_DIG_P8);
    cal_p9 = wiringPiI2CReadReg16(fd, BMP280_DIG_P9);
}

int bmp280_read_raw(int fd, int reg)
{
    int raw = SWAP_2BYTES(wiringPiI2CReadReg16(fd, reg));
    raw <<= 8;
    raw = raw | wiringPiI2CReadReg8(fd, reg + 2);
    raw >>= 4;
    return raw;
}

int bmp280_compensate_temp(int raw_temp)
{
    int t1 = (((raw_temp >> 3) - (cal_t1 << 1)) * (cal_t2)) >> 11;
    int t2 = (((((raw_temp >> 4) - (cal_t1)) *
            ((raw_temp >> 4) - (cal_t1))) >> 12) *
            (cal_t3)) >> 14;
    return t1 + t2;
}

float bmp280_read_temperature(int fd)
{
    int raw_temp = bmp280_read_raw(fd, BMP280_TEMPDATA);
    int compensated_temp = bmp280_compensate_temp(raw_temp);
    return (float)((compensated_temp * 5 + 128) >> 8) / 100;
}

float bmp280_read_pressure(int fd)
{
    int raw_temp = bmp280_read_raw(fd, BMP280_TEMPDATA);
    int compensated_temp = bmp280_compensate_temp(raw_temp);
    int raw_pressure = bmp280_read_raw(fd, BMP280_PRESSUREDATA);

    int64_t p1 = compensated_temp - 128000;
    int64_t p2 = p1 * p1 * (int64_t)cal_p6;
    int64_t buf = (p1 * (int64_t)cal_p5);
    p2 += buf << 17;
    p2 += (int64_t)cal_p4 << 35;
    p1 = ((p1 * p1 * cal_p3) >> 8) + ((p1 * cal_p2) << 12);
    p1 = (((int64_t)1 << 47) + p1) * ((int64_t)cal_p1) >> 33;

    // Avoid exception caused by division by zero
    if (0 == p1)
    {
        return 0;
    }

    int64_t p = 1048576 - raw_pressure;
    p = (((p << 31) - p2) * 3125) / p1;
    p1 = ((int64_t)cal_p9 * (p >> 13) * (p >> 13)) >> 25;
    p2 = ((int64_t)cal_p8 * p) >> 19;
    p = ((p + p1 + p2) >> 8) + (((int64_t)cal_p7) << 4);

    return (float)(p / 256);
}

