#include <Arduino.h>
#include "sensor.h"

class MoistureSensor : public Sensor
{
private:
    int pin;

public:
    float readData()
    {
        return analogRead(pin);
    }
};
