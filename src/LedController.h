#pragma once

class LedController
{
    private:    
        int ledChannel = 0;
    public:
        LedController();
        virtual ~LedController();
        void Init(int ledPin, int ledChannel, int freq, int resolution);
        void Loop();
        //enum LedModus{Standard, Fade, Flash, Turbo};
};

