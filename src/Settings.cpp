#include "Settings.h"

    const String Settings::deviceName = "Goalfinder";
    const String Settings::devicePassword = "ESP3232";
    const int Settings::vibrationSensorSensitivity = 100;
    const int Settings::volume = 100;
    const String Settings::macAddress = "00-1D-60-4A-8C-CB";

Settings::Settings(System::Settings* settingStore)
{
    this->store = settingStore;
}

Settings::~Settings()
{
    delete store;
}


/** Provides the MAC address of the WiFi interface. */
String Settings::GetMacAddress()
{
    
};

/** Provides the volume as a range from 0 to 100 percent. */
int Settings::GetVolume()
{
    
}
/** Sets the volume. The range is clipped to 0 to 100 percent.*/
void Settings::SetVolume(int volume)
{

};

String Settings::GetDeviceName()
{

};

void Settings::SetDeviceName(String deviceName)
{

};

String GetDevicePassword()
{

};

void SetDevicePassword(String devicePassword)
{

};

int GetVibrationSensorSensitivity()
{

};

void SetVibrationSensorSensitivity(int vibrationSensorSensitivity)
{

};

