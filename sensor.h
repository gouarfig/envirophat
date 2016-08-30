
#ifndef SENSOR_H
#define SENSOR_H

int getDHT22TemperatureHumidity(int *temperature, int *humidity);
int getDHT22TemperatureHumidityAverage(int *temperature, int *humidity, int debug);

int getBMP180TemperatureAtmosphericPressure(int *temperature, int *pressure, int debug);
int getBMP280TemperatureAtmosphericPressure(int *temperature, int *pressure, int debug);

#endif

