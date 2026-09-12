#include <Arduino.h>

class Sprinkler
{

private:
    int pin = 4;

public:
    Sprinkler()
    {
        pinMode(pin, OUTPUT);
    }

    void start()
    {
        digitalWrite(pin, HIGH);
    }

    void stop()
    {
        digitalWrite(pin, LOW);
    }
};