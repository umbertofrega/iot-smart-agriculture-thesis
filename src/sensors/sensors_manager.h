#include "temperature_sensor.h"

class SensorsManager
{
private:
    float temperature;
    TemperatureSensor temperatureSensor{PIN_DAC1};

public:
    float getData()
    {
        float temperature = temperatureSensor.readData();
        Serial.println("The temperature is: ");
        Serial.println(temperature);
    }
};