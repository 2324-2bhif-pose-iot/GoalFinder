#pragma once
#include <Arduino.h>
#include "AsyncJson.h"
#include "ArduinoJson.h"
#include "WiFi.h"

class Settings
{
    private:
    public:
        String deviceName = "Goalfinder";
        String devicePassword = "ESP3232";
        int vibrationSensorSensitivity = 100;
        int volume = 100;
        String macAddress = "%02x:%02x:%02x:%02x:%02x:%02x";

        Settings() 
        {
            macAddress = String(WiFi.macAddress());
        }
};

