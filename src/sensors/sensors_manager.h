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

<<<<<<< HEAD
    float getPh(int temperature)
    {
        return phSensor.getPh(temperature);
=======
    float getPh(int temp)
    {
        return phSensor.getPh(temp);
>>>>>>> fb719b0dae666259cb2b23a8b919f978895e9579
    }

    int getHumidityPercentage()
    {
        return moistureSensor.getHumidityPercentage();
    }
};