#pragma once
#include "lib_extra/BluetoothA2DP.h"

class BluetoothManager {
    public:
        void Test();
        void Init();
        void Connect();
    private:
       BluetoothA2DPSource a2dp_source;
};