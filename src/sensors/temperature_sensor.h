#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

class TemperatureSensor
{
private:
    OneWire oneWire;
    DallasTemperature sensor;

public:
<<<<<<< HEAD
    TemperatureSensor() : oneWire(D3)
=======
    TemperatureSensor() : oneWire(A0)
>>>>>>> fb719b0dae666259cb2b23a8b919f978895e9579
    {
        sensor = DallasTemperature(&oneWire);
    }

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