#include <GoalfinderApp.h>
#include <Arduino.h>
#include <ToFSensor.h>
#include <VibrationSensor.h>
#include <BluetoothManager.h>
#include <web/WebServer.h>
#include <web/SNTP.h>
#include <FileSystem.h>

#define FORMAT_FS_IF_FAILED true
#define TOF_SDA_PIN 27
#define TOF_SCL_PIN 25

#define SSID "Goal Finder"
#define PASSWORD "esp123456"

FileSystem fileSystem(FORMAT_FS_IF_FAILED);
WebServer webServer(&fileSystem);
SNTP sntp;

ToFSensor tofSensor;
VibrationSensor vibrationSensor;

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
    
    WiFi.softAP(SSID, PASSWORD);

    WiFi.setSleep(false);

    Serial.println(WiFi.softAPIP());

    webServer.Begin();
    
    sntp.Init();
    vibrationSensor.Init();
    tofSensor.Init(TOF_SCL_PIN, TOF_SDA_PIN);     
}

void GoalfinderApp::Process() 
{
    
}