#include "GoalfinderApp.h"
#include <Arduino.h>
#include <ToFSensor.h>
#include <VibrationSensor.h>

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
    vibrationSensor.Init();
    tofSensor.Init();
}

void GoalfinderApp::Process() {
   Serial.print("Distance (mm): ");
   Serial.println(tofSensor.ReadSingleMillimeters());
   delay(500);

   Serial.print("Vibration Measurement: ");
   Serial.println(vibrationSensor.Vibration());
   delay(500);
}