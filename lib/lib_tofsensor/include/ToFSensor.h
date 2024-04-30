#pragma once

#include <Adafruit_VL53L0X.h>

class ToFSensor 
{
    public: 
        virtual ~ToFSensor();
        void Init();
        int ReadSingleMillimeters();
    private: 
        Adafruit_VL53L0X* sensor; 
};