#include "mixer.h"

class MixersManager
{

private:
    Mixer acidicMixer;
    Mixer basicMixer;

public:
    MixersManager(int pinAcidic, int pinBasic) : acidicMixer(pinAcidic),
                                                 basicMixer(pinBasic)
    {
    }

    void mixBasic()
    {
        basicMixer.mix();
        Serial.println("Mixed basic");
    }

    void mixAcidic()
    {
        acidicMixer.mix();
        Serial.println("Mixed acidic");
    }
};