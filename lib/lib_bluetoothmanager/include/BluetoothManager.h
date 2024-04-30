#pragma once
#include "BluetoothSerial.h"

class BluetoothManager {
    public:
        virtual ~BluetoothManager();
        void Init();
        void Connect();
    private:
        BluetoothSerial* SerialBT;
};