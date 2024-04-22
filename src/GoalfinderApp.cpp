#include <GoalfinderApp.h>
#include <Arduino.h>
#include <ToFSensor.h>
#include <VibrationSensor.h>
#include <BluetoothManager.h>
#include <web/WebApp.h>
#include <file_system/FileSystem.h>

#define FORMAT_SPIFFS_IF_FAILED true

const char* ssid = "HUAWEI_H122_4772_1";
const char* password = "FBDYT61E8HR";

FileSystem fileSystem(FORMAT_SPIFFS_IF_FAILED);
WebApp webApp(&fileSystem);

//ToFSensor tofSensor;
//VibrationSensor vibrationSensor;
//BluetoothManager bluetoothManager;

GoalfinderApp::GoalfinderApp() :
    Singleton<GoalfinderApp>() {
}

GoalfinderApp::~GoalfinderApp() {
}

void GoalfinderApp::Init() 
{
    Serial.begin(115200);

    WiFi.begin(ssid, password);

    while(WiFi.status() != WL_CONNECTED) 
    {
        Serial.println(".");
    }

    WiFi.setSleep(false);

    Serial.println(WiFi.localIP());

    if(!fileSystem.Begin()) 
    {
        Serial.println("Error FS");
        return;
    }
    webApp.Begin();
    //vibrationSensor.Init();
    //tofSensor.Init();
    //bluetoothManager.Init();    
}

void GoalfinderApp::Process() 
{
    //Serial.print("Distance (mm): ");
    //Serial.println(tofSensor.ReadSingleMillimeters());
    //delay(500);

    //Serial.print("Vibration Measurement: ");
    //Serial.println(vibrationSensor.Vibration());
    //delay(500);   
}