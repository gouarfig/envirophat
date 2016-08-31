
#ifndef BMP280_H
#define BMP280_H

#define SWAP_2BYTES(x) (((x & 0xFFFF) >> 8) | ((x & 0xFF) << 8))

/* BMP280 default address */
#define BMP280_I2CADDR 0x77
#define BMP280_CHIPID 0xD0

/* BMP280 Registers */

#define BMP280_DIG_T1 0x88 /* R   Unsigned Calibration data (16 bits) */
#define BMP280_DIG_T2 0x8A /* R   Signed Calibration data (16 bits) */
#define BMP280_DIG_T3 0x8C /* R   Signed Calibration data (16 bits) */
#define BMP280_DIG_P1 0x8E /* R   Unsigned Calibration data (16 bits) */
#define BMP280_DIG_P2 0x90 /* R   Signed Calibration data (16 bits) */
#define BMP280_DIG_P3 0x92 /* R   Signed Calibration data (16 bits) */
#define BMP280_DIG_P4 0x94 /* R   Signed Calibration data (16 bits) */
#define BMP280_DIG_P5 0x96 /* R   Signed Calibration data (16 bits) */
#define BMP280_DIG_P6 0x98 /* R   Signed Calibration data (16 bits) */
#define BMP280_DIG_P7 0x9A /* R   Signed Calibration data (16 bits) */
#define BMP280_DIG_P8 0x9C /* R   Signed Calibration data (16 bits) */
#define BMP280_DIG_P9 0x9E /* R   Signed Calibration data (16 bits) */

#define BMP280_CONTROL 0xF4
#define BMP280_RESET 0xE0
#define BMP280_CONFIG 0xF5
#define BMP280_PRESSUREDATA 0xF7
#define BMP280_TEMPDATA 0xFA

void bmp280_load_calibration(int fd);

int bmp280_read_raw(int fd, int reg);

int bmp280_compensate_temp(int raw_temp);

float bmp280_read_temperature(int fd);

float bmp280_read_pressure(int fd);

#endif