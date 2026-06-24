#include <Arduino.h>
#include "sensor.h"

class MoistureSensor
{
private:
    int pin;

public:
    float readData()
    {
        return analogRead(pin);
    }
};
