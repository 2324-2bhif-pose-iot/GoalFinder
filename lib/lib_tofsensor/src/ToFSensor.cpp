#include <ToFSensor.h>
#include <Wire.h>

void ToFSensor::Init() 
{
    sensor = new Adafruit_VL53L0X();
    sensor->begin();
    Wire.begin();
}

int ToFSensor::ReadSingleMillimeters() 
{
    VL53L0X_RangingMeasurementData_t measure;
    sensor->rangingTest(&measure, false); // pass in 'true' to get debug data printout!

    if (measure.RangeStatus != 4) 
    { 
        return measure.RangeMilliMeter;
    } 
    else 
    {
        return -1;
    }
    
    delay(100);
}