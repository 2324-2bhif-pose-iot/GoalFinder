#pragma once

class LedController
{
    private:    
        int ledChannel = 0;
    public:
        LedController();
        ~LedController();
        void Init(int ledPin);
        void Loop();
        //enum LedModus{Standard, Fade, Flash, Turbo};
};
