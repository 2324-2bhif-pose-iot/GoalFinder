#include <BluetoothManager.h>

const char* BLUETOOTH_SPEAKER_NAME = "DEFAULT"; 

int32_t get_sound_data(Frame *data, int32_t frameCount) {
    // generate your sound data 
    // return the effective length (in frames) of the generated sound  (which usually is identical with the requested len)
    // 1 frame is 2 channels * 2 bytes = 4 bytes
    return frameCount;
}

void BluetoothManager::Test() {
    a2dp_source.set_auto_reconnect(true);
    a2dp_source.start(BLUETOOTH_SPEAKER_NAME, get_sound_data); 
}