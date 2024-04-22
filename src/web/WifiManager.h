#pragma once
#include <Arduino.h>
#include <WiFi.h>

class WifiManager 
{
    public:
        void Connect();
        void CreateAccessPoint(String ssid, String password);
        void Disconnect();
};