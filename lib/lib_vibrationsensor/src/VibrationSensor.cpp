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