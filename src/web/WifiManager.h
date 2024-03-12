#pragma once
#include <Arduino.h>
#include <WiFi.h>

class WifiManager {
    public:
        static void CreateWifiNetwork(String ssid, String password);
        static const String SSID; 
        static const String PASSWORD;
};