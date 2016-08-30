#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <curl/curl.h>

#include "pi.h"
#include "pi_temp.h"
#include "sensor.h"

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
    int sensor = getBMP280TemperatureAtmosphericPressure(&sensor_temperature, &sensor_pressure, debug);
    if (debug && internalTemperature)
    {
        printf("Raspberry Pi temperature: %5.1fC\n", internalTemperature / 10.0);
    }
    if (debug && sensor)
    {
        printf("BMP280 sensor temperature: %5.1fC, atmospheric pressure: %5.1f hPa\n", sensor_temperature / 10.0, sensor_pressure / 100.0);
    }

    return EXIT_SUCCESS;
}
