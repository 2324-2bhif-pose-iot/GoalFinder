#include <Arduino.h>
#include "web/WifiManager.h"

void setup() {
    Serial.begin(115200);
    Serial.println();
        
    // Setting the ESP as an access point
    Serial.print("Setting AP (Access Point)…");
    WifiManager::CreateWifiNetwork(WifiManager::SSID, WifiManager::PASSWORD);
}

void loop() {
    
}