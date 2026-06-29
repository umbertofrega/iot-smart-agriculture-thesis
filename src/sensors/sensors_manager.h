#include "temperature_sensor.h"
#include "ph_sensor.h"
#include "moisture_sensor.h"

class SensorsManager
{
private:
    TemperatureSensor temperatureSensor;
    PhSensor phSensor;
    MoistureSensor moistureSensor;

public:
    void begin()
    {
        temperatureSensor.begin();
    }

    float getTemp()
    {
        return temperatureSensor.getTemperature();
    }

    float getPh(int temperature)
    {
        return phSensor.getPh(temperature);
    }

    int getHumidityPercentage()
    {
        return moistureSensor.getHumidityPercentage();
    }
};