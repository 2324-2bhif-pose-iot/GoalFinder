#pragma once

class LedController
{
    private:    
        int ledChannel = 0;
    public:
        void Init(int ledPin, int freq, int resolution);
        void Loop();
        //enum LedModus{Standard, Fade, Flash, Turbo};
};