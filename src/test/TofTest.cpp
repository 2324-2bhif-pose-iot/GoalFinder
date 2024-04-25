#pragma once
#include <ToFSensor.h>

class TofTest 
{
    public:
        void Setup() 
        {
            ToFSensor tofSensor;
            tofSensor.Init();
        }  

        void Loop() 
        {
            
        }
    private:
        //variables
};