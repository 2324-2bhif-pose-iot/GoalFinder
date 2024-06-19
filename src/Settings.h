#pragma once
#include <Arduino.h>
#include <Singleton.h>
#include <system/Settings.h>

class Settings : public Singleton<Settings>
{
    public:
        virtual ~Settings();
        
        // TODO: Make those members static const and private
        // Init the members in cpp, e.g:
        // .h:   static const String deviceName;
        // .cpp: const String Settings::deviceName = "GoalFinder";
        // see also implemented setting for volume
        String deviceName = "Goalfinder";
        String devicePassword = "ESP3232";
        int vibrationSensorSensitivity = 100;
        
        // already replaced - TODO: Adjust your code!
        // @deprecated
        int volume = 100;
        // @deprecated
        String macAddress = "%02x:%02x:%02x:%02x:%02x:%02x";

        /** Provides the MAC address of the WiFi interface. */
        String GetMacAddress();

        /** Provides the volume as a range from 0 to 100 percent. */
        int GetVolume();

        /** Sets the volume. The range is clipped to 0 to 100 percent.*/
        void SetVolume(int volume);

    private:
		friend class Singleton<Settings>;
        /** Singleton constructor */
        Settings();

        static const char* keyVolume;

        static const int defaultVolume;

        System::Settings store;
};