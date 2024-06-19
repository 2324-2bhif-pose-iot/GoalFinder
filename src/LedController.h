#pragma once

class LedController
{
    private:    
    public:
        LedController(int ledPin, int ledChannel);
        ~LedController();
        void Init(int ledPin);
        void Loop();
        //enum LedModus{Standard, Fade, Flash, Turbo};
};
