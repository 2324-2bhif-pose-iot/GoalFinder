#pragma once
#include <Arduino.h>
#include <Singleton.h>
#include <system/Settings.h>

class Settings : public Singleton<Settings>
{
    public:
        virtual ~Settings();

        bool IsModified() const;

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


    private:
		friend class Singleton<Settings>;
        /** Singleton constructor */
        Settings();
        void SetModified();

        static const char* keyVolume;

        static const int defaultVolume;

        static const String deviceName;
        static const String devicePassword;
        static const int vibrationSensorSensitivity;
        static const int volume;
        static const String macAddress;

        System::Settings store;
        bool modified;
};