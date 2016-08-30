#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <wiringPi.h>
#include <maxdetect.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>
#include <math.h>
#include "config.h"
#include "bmp180.h"

/*
 */
int getDHT22TemperatureHumidity(int *temperature, int *humidity) {
	int temp, rh;
	int tries = 5;
	int success;

	temp = rh = 0;

	do {
		tries--;
		success = readRHT03(RHT03_PIN, &temp, &rh);
		if (!success) {
			sleep(5);
		}
	} while ((!success) && (tries > 0));

	if (success) {
		if ((temp & 0x8000) != 0) // Negative
		{
			temp &= 0x7FFF;
			temp = -temp;
		}
	}
	if (rh > 1000) {
		success = 0;
	}
	*temperature = temp;
	*humidity = rh;

	return success;
}

int getAverage(int values[], int count) {
	int i;
	int total = 0;

	for (i = 0; i < count; i++) {
		total += values[i];
	}
	return (int) (total / count);
}

int getDHT22TemperatureHumidityAverage(int *temperature, int *humidity, int debug) {
	int reading = 3;
	int tries = 5;
	int read = 0;
	int success;
	int temperature_reading[reading];
	int humidity_reading[reading];

	while ((read < reading) && (tries > 0)) {
		tries--;
		success = getDHT22TemperatureHumidity(
				&temperature_reading[read],
				&humidity_reading[read]
				);
		if (success) {
			if (debug) printf("Reading %d: temp = %d, humidity = %d\n", read, temperature_reading[read], humidity_reading[read]);
			if (read > 0) {
				if ((abs(temperature_reading[read] - temperature_reading[read - 1]) < MAX_RAW_DIFFERENCE) && (abs(humidity_reading[read] - humidity_reading[read - 1]) < MAX_RAW_DIFFERENCE)) {
					read++;
				}
			} else {
				// Always keep the first value
				read++;
			}
		}
		if (read < reading) {
			sleep(5);
		}
	}
	// We need at least two readings (to avoid the case when the first reading was totally wrong)
	if (read > 1) {
		*temperature = getAverage(temperature_reading, read);
		*humidity = getAverage(humidity_reading, read);
		if (debug) printf("Average on %d readings: temp = %d, humidity = %d\n", read, *temperature, *humidity);
		success = 1;
	} else {
		success = 0;
	}
	return success;
}

int getBMP180TemperatureAtmosphericPressure(int *temperature, int *pressure, int debug) {
	int success = 0;
	int fd;
	fd = i2c_Open(I2CBus);
	if (fd) {
		bmp_Calibration(fd);
		bmp_GetTemperature(fd, temperature);
		bmp_GetPressure(fd, pressure);
		if (debug) printf("Temperature\t:%.1f C\n", (double)*temperature / 10.0);
		if (debug) printf("Pressure\t:%.2f hPa/mB\n", (double)*pressure / 100.0);
		close(fd);
		success = 1;
	} else {
		fprintf(stderr, "Can't open the I2C device '%s'\n", I2CBus);
	}

	return success;
}
