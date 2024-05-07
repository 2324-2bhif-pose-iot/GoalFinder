#include <ToFSensor.h>

void ToFSensor::Init() 
{
    if(!sensor->begin())
    {
        Serial.println(F("Failed to boot VL53L0X"));
    }
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

ToFSensor::~ToFSensor()
{
    delete sensor;
}
