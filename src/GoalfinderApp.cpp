#include "GoalfinderApp.h"
#include <Arduino.h>
#include <ToFSensor.h>

ToFSensor tofSensor;

GoalfinderApp::GoalfinderApp() :
    Singleton<GoalfinderApp>() {
}

GoalfinderApp::~GoalfinderApp() {
}

void GoalfinderApp::Init() 
{
    Serial.begin(115200);
    
    tofSensor.Init();
}

void GoalfinderApp::Process() {
   Serial.print("Distance (mm): ");
   Serial.println(tofSensor.ReadSingleMillimeters());
   delay(500);
}