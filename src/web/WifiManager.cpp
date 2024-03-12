#include "WifiManager.h"
    const String WifiManager::SSID = "Goal_Finder";
    const String WifiManager::PASSWORD = "Goalesp";

    void WifiManager::CreateWifiNetwork(String ssid, String password) {
        // Remove the password parameter, if you want the AP (Access Point) to be open
        WiFi.softAP(ssid, password);
    }

