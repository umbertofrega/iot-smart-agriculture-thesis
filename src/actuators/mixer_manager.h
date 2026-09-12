#include "mixer.h"

class MixersManager
{

private:
    Mixer acidicMixer;
    Mixer basicMixer;
    int pinAcidic = 2;
    int pinBasic = 1;

public:
    MixersManager() {}

    void mixBasic()
    {
        basicMixer = Mixer(pinBasic);
        basicMixer.mix();
        Serial.println("Mixed basic");
    }

    void mixAcidic()
    {
        acidicMixer = Mixer(pinAcidic);
        acidicMixer.mix();
        Serial.println("Mixed acidic");
    }
};