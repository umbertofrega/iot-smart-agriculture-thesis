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
    void beginAll()
    {
        beginTemp();
        beginpH();
    }

    void beginTemp()
    {
        temperatureSensor.begin();
    }

    float getTemp()
    {
        return temperatureSensor.getTemperature();
    }

    void beginpH()
    {
        phSensor.begin();
    }

    float getPh(int temp)
    {
        return phSensor.getPh(temp);
    }

    int getHumidityPercentage()
    {
        return moistureSensor.getHumidityPercentage();
    }
};