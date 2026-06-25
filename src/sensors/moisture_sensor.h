#include <Arduino.h>

class MoistureSensor
{
public:
    float getHumidity()
    {
        return analogRead(A1);
    }
};
