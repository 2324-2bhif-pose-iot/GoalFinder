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
#define RANGE_WHEN_BALL_GOES_IN 180
#define VIBRATION_WHEN_BALL_HITS_BOARD 2000

#define SSID "Goal Finder"
#define PASSWORD "esp123456"

FileSystem fileSystem(FORMAT_FS_IF_FAILED);
WebServer webServer(&fileSystem);
SNTP sntp;

ToFSensor tofSensor;
VibrationSensor vibrationSensor;
const int ledPin = 17;

const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
    

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

    
    ledcSetup(ledChannel, freq, resolution);
    
    ledcAttachPin(ledPin, ledChannel);

}

void GoalfinderApp::Process()
{
    for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){

        ledcWrite(ledChannel, dutyCycle);
        delay(5);
    }


    for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){

      ledcWrite(ledChannel, dutyCycle);   
      delay(5);
    }

    if(vibrationSensor.Vibration() > VIBRATION_WHEN_BALL_HITS_BOARD)
    {
        delay(3000);

        if(tofSensor.ReadSingleMillimeters() < RANGE_WHEN_BALL_GOES_IN)
        {
            Serial.println("Hit detection");
        }
        else
        {
            Serial.println("Miss detection");
        }
       
    }
    else if(tofSensor.ReadSingleMillimeters() < RANGE_WHEN_BALL_GOES_IN)
    {
        Serial.println("Hit detection");
    }
    
}

