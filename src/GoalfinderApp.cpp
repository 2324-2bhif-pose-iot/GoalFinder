#include <GoalfinderApp.h>
#include <Arduino.h>
#include <ToFSensor.h>
#include <VibrationSensor.h>
#include <BluetoothManager.h>
#include <web/WebServer.h>
#include <web/SNTP.h>
#include <FileSystem.h>

#include <test/BluetoothTest.cpp>
#include <test/TofTest.cpp>
#include <test/AudioTest.cpp>
#include <test/VibrationTest.cpp>

#define FORMAT_SPIFFS_IF_FAILED true

const char* ssid = "Omar iPhone 11";
const char* password = "bruderItachi!";

FileSystem fileSystem(FORMAT_SPIFFS_IF_FAILED);
WebServer webServer(&fileSystem);
SNTP sntp;

BluetoothTest btTest;
TofTest tofTest;
AudioTest audioTest(&fileSystem);
VibrationTest vibrationTest;

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

    if(!fileSystem.Begin()) 
    {
        Serial.println("Error FS");
        return;
    }

    btTest.Setup();    
    audioTest.Setup();
    //vibrationTest.Setup();
    //tofTest.Setup();

    /*WiFi.begin(ssid, password);

    while(WiFi.status() != WL_CONNECTED) 
    {
        Serial.println(".");
    }

    WiFi.setSleep(false);

    Serial.println(WiFi.localIP());

    

    webServer.Begin();
    sntp.Init();*/
    //vibrationSensor.Init();
    //tofSensor.Init();
    //bluetoothManager.Init();    
}

void GoalfinderApp::Process() 
{
    btTest.Loop();    
    audioTest.Loop();
    //vibrationTest.Loop();
    //tofTest.Loop();
    //Serial.print("Distance (mm): ");
    //Serial.println(tofSensor.ReadSingleMillimeters());
    //delay(500);

    //Serial.print("Vibration Measurement: ");
    //Serial.println(vibrationSensor.Vibration());
    //delay(500);   

    /*struct tm timeInfo = sntp.GetLocalTime();

    Serial.println(&timeInfo, "%A, %B %d %Y %H:%M:%S");
    Serial.print("Day of week: ");
    Serial.println(&timeInfo, "%A");
    Serial.print("Month: ");
    Serial.println(&timeInfo, "%B");
    Serial.print("Day of Month: ");
    Serial.println(&timeInfo, "%d");
    Serial.print("Year: ");
    Serial.println(&timeInfo, "%Y");
    Serial.print("Hour: ");
    Serial.println(&timeInfo, "%H");

    delay(1000);*/
}