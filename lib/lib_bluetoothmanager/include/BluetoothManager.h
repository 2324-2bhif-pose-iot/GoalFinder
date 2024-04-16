#pragma once
#include "BluetoothSerial.h"

class BluetoothManager {
    public:
        void Init();
        void Connect();
    private:
        BluetoothSerial SerialBT;
};