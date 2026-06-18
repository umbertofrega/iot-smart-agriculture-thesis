#include "temperature_sensor.h"

class SensorsManager
{
private:
    float temperature;
    TemperatureSensor temperatureSensor{PIN_DAC1};

public:
    float getData()
    {
        float temperature = 8;
        Serial.println("The temperature is: ");
        Serial.println(temperature);
        return temperature;
    }
};