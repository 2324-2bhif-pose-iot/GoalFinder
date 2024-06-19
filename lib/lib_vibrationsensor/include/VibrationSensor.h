#pragma once

class VibrationSensor {
    public: 
        virtual ~VibrationSensor();
        void Init();
        long Vibration();

        /** 
         * Sets the sensitivity of the sensor in the range of 0 to 100%.
         * The value is clipped.
         */
        void SetSensitivity(int sensitivity);
        
    private:
        int vs;
};

