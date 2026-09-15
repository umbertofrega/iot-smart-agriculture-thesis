#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
class TemperatureSensor
{
private:
    OneWire oneWire;
    DallasTemperature sensor;

public:
    TemperatureSensor() : oneWire(6), sensor(&oneWire) {}

    void begin()
    {
        sensor.begin();
    }

    float getTemperature()
    {
        sensor.requestTemperatures();
        return sensor.getTempCByIndex(0);
    }
};