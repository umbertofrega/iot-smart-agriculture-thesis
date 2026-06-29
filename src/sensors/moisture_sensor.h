#include <Arduino.h>

class MoistureSensor
{
public:
    int getHumidityPercentage()
    {
        return map(analogRead(A1), 3100, 1940, 0, 100);
    }
};
