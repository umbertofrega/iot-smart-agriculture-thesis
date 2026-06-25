#include "mixer.h"

class MixersManager
{

private:
    Mixer acidicMixer;
    Mixer basicMixer;
    int pinAcidic;
    int pinBasic;

public:
    MixersManager(int pinA, int pinB)
    {
        pinAcidic = pinA;
        pinBasic = pinB;
    }

    void mixBasic()
    {
        acidicMixer = Mixer(pinBasic);
        basicMixer.mix();
        Serial.println("Mixed basic");
    }

    void mixAcidic()
    {
        basicMixer = Mixer(pinAcidic);
        acidicMixer.mix();
        Serial.println("Mixed acidic");
    }
};