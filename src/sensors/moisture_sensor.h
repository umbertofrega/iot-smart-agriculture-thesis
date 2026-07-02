#include <Arduino.h>

class MoistureSensor
{
public:
    int getHumidityPercentage()
    {
        return map(analogRead(A1), 3110, 1930, 0, 100);
    }
};
