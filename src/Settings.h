#pragma once
#include <Arduino.h>
#include <Singleton.h>
#include <system/Settings.h>
#include "LedController.h"

class Settings : public Singleton<Settings>
{
    public:
        virtual ~Settings();

        bool IsModified() const;

        void ClearModifiedState();

        /** Provides the MAC address of the WiFi interface. */
        String GetMacAddress();

        /** Provides the volume as a range from 0 to 100 percent. */
        int GetVolume();

        /** Sets the volume. The range is clipped to 0 to 100 percent.*/
        void SetVolume(int volume);

        String GetDeviceName();

        void SetDeviceName(String deviceName);

        String GetDevicePassword();

        void SetDevicePassword(String devicePassword);

        int GetVibrationSensorSensitivity();

        void SetVibrationSensorSensitivity(int vibrationSensorSensitivity);

        LedMode GetLedMode();

        void SetLedMode(LedMode ledMode);


    private:
		friend class Singleton<Settings>;
        /** Singleton constructor */
        Settings();
        void SetModified();

        static const char* keyVolume;
        static const int defaultVolume;

        static const char* keyDeviceName;
        static const String defaultDeviceName;

        static const char* keyDevicePassword;
        static const String defaultDevicePassword;

        static const char* keyVibrationSensorSensitivity;
        static const int defaultVibrationSensorSensitivity;
        
        static const char* keyLedMode;
        static const LedMode defaultLedMode;

        System::Settings store;
        bool modified;
};