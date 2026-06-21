#include "sensor.h"
#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

class TemperatureSensor : public Sensor
{
private:
    OneWire oneWire;
    DallasTemperature sensor;

    TemperatureSensor(int pin) : oneWire(pin)
    {
        sensor = DallasTemperature(&oneWire);
        sensor.begin();
    }

public:
    float getTemperature()
    {
        sensor.requestTemperatures();
        return sensor.getTempCByIndex(0);
    }
};