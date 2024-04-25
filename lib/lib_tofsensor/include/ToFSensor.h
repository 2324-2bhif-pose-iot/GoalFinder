#pragma once

#include <Adafruit_VL53L0X.h>

class ToFSensor 
{
    public: 
        void Init();
        void ConfigSensor(Adafruit_VL53L0X::VL53L0X_Sense_config_t vl_config);
        int ReadSingleMillimeters();

    private: 
        Adafruit_VL53L0X* sensor;
        
};