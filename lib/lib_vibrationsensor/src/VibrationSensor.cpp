#include <VibrationSensor.h>
#include <Arduino.h>

void VibrationSensor::Init() 
{
    vs = 13;
    pinMode(vs, INPUT);
}

long VibrationSensor::Vibration() 
{
   long measurement = pulseIn(vs, HIGH);
   return measurement;
   
}

VibrationSensor::~VibrationSensor()
{

}


void VibrationSensor::SetSensitivity(int sensitivity)
{
    if (sensitivity < 0) {
        sensitivity = 0;
    } else if (sensitivity > 100) {
        sensitivity = 100;
    }

}