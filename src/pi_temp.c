#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <math.h>
#include <tgmath.h>

char *internalTemperatureSysFile = "/sys/class/thermal/thermal_zone0/temp";
const int maxFileLength = 8192;
const int minInternalTemperature = 0 * 100;	// Multiplied by 100, we store 38,52 as 3852
const int maxInternalTemperature = 100 * 100;	// Multiplied by 100, we store 38,52 as 3852

int getFileSize(char *fileName)
{
    struct stat fileStat;
    if (stat(fileName, &fileStat) < 0) {
        return 0;
    }
    return fileStat.st_size;
}

int validatePiTemperature(char *temperatureData)
{
    int temperature = 0;
    if (temperatureData == NULL) {
        return 0;
    }
    temperature = atoi(temperatureData);
    temperature = (int)(temperature / 10);
    if ((temperature <= minInternalTemperature) || (temperature > maxInternalTemperature)) {
        temperature = 0;
    }
    return temperature;
}

int getPiTemperature(int debug)
{
    int temperature = 0;
    int fileSize = getFileSize(internalTemperatureSysFile);
    if (fileSize > maxFileLength) {
        fprintf(stderr, "Internal temperature file looks corrupted. File size = %d\n", fileSize);
        return 0;
    }
    int filehandle = open(internalTemperatureSysFile, O_RDONLY);
    if (filehandle < 0) {
        fprintf(stderr, "Can't open the internal temperature file '%s'\n", internalTemperatureSysFile);
        return 0;
    }
    char temperatureData[fileSize];
    int reading = read(filehandle, temperatureData, fileSize);
    if (reading <= 0) {
        fprintf(stderr, "Can't read from the internal temperature file (read = %d)\n", reading);
        return 0;
    }
    close(filehandle);
    temperature = validatePiTemperature(temperatureData);
    if (debug) printf("Raspberry Pi Internal Temperature: %s => %d\n", temperatureData, temperature);
    return temperature;
}

