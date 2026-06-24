#include <Arduino.h>
#include "sensor.h"

class MoistureSensor
{
public:
    float getHumidity()
    {
        return analogRead(A1);
    }
};
