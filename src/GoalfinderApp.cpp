#include <GoalfinderApp.h>
#include <Arduino.h>
#include <ToFSensor.h>
#include <VibrationSensor.h>
#include <BluetoothManager.h>

ToFSensor tofSensor;
VibrationSensor vibrationSensor;
BluetoothManager bluetoothManager;

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
    bluetoothManager.Init();    
}

void GoalfinderApp::Process() 
{
    Serial.print("Distance (mm): ");
    Serial.println(tofSensor.ReadSingleMillimeters());
    delay(500);

    Serial.print("Vibration Measurement: ");
    Serial.println(vibrationSensor.Vibration());
    delay(500);   
}