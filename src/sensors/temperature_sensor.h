#include "sensor.h"
#include <DHT.h>
#include <Arduino.h>

#define DHTTYPE DHT22

class TemperatureSensor : public Sensor
{
private:
    int pin;
    unsigned long time;
    DHT dht;

public:
    TemperatureSensor(int digitalPin) : dht(digitalPin, DHT22)
    {
        pin = digitalPin;
        dht.begin();
        time = millis();
    }

    float readData() override
    {
        unsigned long elapsed = (millis() - time);

        if (elapsed <= 2000)
            delay(2000 - elapsed);

        float temperature = dht.readTemperature();

        if (!isnan(temperature))
        {
            return temperature;
        }
        return -99;
    }
};