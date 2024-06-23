#pragma once
#include "LedMode.h"


class LedController
{
    private:    
        int ledChannel;
        LedMode currMode = LedMode::Standard;
    public:
        LedController(int ledPin, int ledChannel);
        ~LedController();
        void Loop();
        void SetMode(LedMode mode);
        LedMode GetMode();
};