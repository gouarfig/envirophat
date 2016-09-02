#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <curl/curl.h>

#include "bmp280.h"
#include "pi.h"
#include "pi_temp.h"
#include "sensor.h"
#include "curl_send.h"

/*
 ***********************************************************************
 * The main program
 ***********************************************************************
 */

int main(int argc, char **argv)
{
    int sensor_temperature = 0;
    int sensor_pressure = 0;
    int debug = 0;

    initWiringPi();
    int internalTemperature = getPiTemperature(debug);
    int sensor = getBMP280TemperatureAtmosphericPressure(&sensor_temperature, &sensor_pressure, debug);
    if (debug && internalTemperature)
    {
        printf("Raspberry Pi temperature: %5.2fC\n", internalTemperature / 100.0);
    }
    if (debug && (sensor == SUCCESS))
    {
        printf("BMP280 sensor temperature: %5.2fC, atmospheric pressure: %5.2f hPa\n", sensor_temperature / 100.0, sensor_pressure / 100.0);
    }

    if (sensor == SUCCESS)
    {
        sendInformation(internalTemperature, sensor_temperature, sensor_pressure, debug);
    }

    return EXIT_SUCCESS;
}
