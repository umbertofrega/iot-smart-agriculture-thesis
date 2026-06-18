#include <Arduino.h>

class Mixer
{
private:
    int pinNumber;

public:
    Mixer(int pin)
    {
        pinMode(pin, OUTPUT);
        pinNumber = pin;
    }

    void mix()
    {
        digitalWrite(pinNumber, HIGH);
        delay(10000);
        digitalWrite(pinNumber, LOW);
    };
};