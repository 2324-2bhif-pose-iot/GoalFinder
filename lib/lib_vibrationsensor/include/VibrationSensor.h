#pragma once

class VibrationSensor {
    public: 
        virtual ~VibrationSensor();
        void Init();
        long Vibration();
    private:
        int vs;
};

