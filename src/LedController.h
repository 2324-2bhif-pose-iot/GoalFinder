#pragma once

enum LedMode {Standard, Fade, Flash, Turbo};

class LedController
{
    private:    
        int ledChannel;
        LedMode currMode = LedMode::Standard;
    public:
        LedController(int ledPin, int ledChannel);
        ~LedController();
        void Init(int ledPin);
        void Loop();
        void SetMode(LedMode mode);
        LedMode GetMode();
};