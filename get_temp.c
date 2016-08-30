#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <wiringPi.h>
#include <maxdetect.h>

#include "pi.h"
#include "bmp180.h"
#include "sensor.h"
#include "pi_temp.h"

/*
 ***********************************************************************
 * The main program
 ***********************************************************************
 */

int main(int argc, char **argv)
{
        int sensor_temperature = 0;
        int sensor_pressure = 0;
        int debug = 1;

        initPi();
        int internalTemperature = getPiTemperature(debug);
        int sensor = getBMP180TemperatureAtmosphericPressure(&sensor_temperature, &sensor_pressure, debug);
        if (debug && internalTemperature) {
                printf("Raspberry Pi temperature: %5.1fC\n", internalTemperature / 10.0);
        }
        if (debug && sensor) {
                printf("BMP180 sensor temperature: %5.1fC, atmospheric pressure: %5.1f hPa\n", sensor_temperature / 10.0, sensor_pressure / 100.0);
        }

  return EXIT_SUCCESS;
}


