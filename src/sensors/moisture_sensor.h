#include <Arduino.h>

class MoistureSensor
{
public:
    int getHumidityPercentage()
    {
        return map(constrain(analogRead(A1), 1900, 3110), 3110, 1900, 0, 100);
    }
};
