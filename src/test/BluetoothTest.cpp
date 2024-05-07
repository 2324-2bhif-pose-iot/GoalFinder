#pragma once
#include <BluetoothManager.h>

class BluetoothTest 
{
    public:
        void Setup() 
        {
            bt.Init();
        }  

        void Loop() 
        {
            bt.Test();
        }
    private:
        BluetoothManager bt;
        //variables
};