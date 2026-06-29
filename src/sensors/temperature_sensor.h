#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

class TemperatureSensor
{
private:
    OneWire oneWire;
    DallasTemperature sensor;

public:
    TemperatureSensor() : oneWire(D3)
    {
        sensor = DallasTemperature(&oneWire);
        sensor.begin();
    }

    float getTemperature()
    {
        sensor.requestTemperatures();
        return sensor.getTempCByIndex(0);
    }
};