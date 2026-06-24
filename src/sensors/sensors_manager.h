#include "temperature_sensor.h"
#include "ph_sensor.h"
#include "moisture_sensor.h"

class SensorsManager
{
private:
    TemperatureSensor temperatureSensor;
    PhSensor PhSensor;
    MoistureSensor moistureSensor;

public:
    float getTemp()
    {
        return temperatureSensor.getTemperature();
    }

    float getPh()
    {
        return 0;
    }

    float getHumidity()
    {
        return moistureSensor.getHumidity();
    }
};