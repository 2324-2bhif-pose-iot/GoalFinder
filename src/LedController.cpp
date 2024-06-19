#include "LedController.h"
#include <Arduino.h>

#define DEFAULT_FREQUENCY 5000
#define DEFAULT_RESOLUTION 8

LedController::LedController(int ledPin, int ledChannel)
{
    ledcSetup(ledChannel, DEFAULT_FREQUENCY, DEFAULT_RESOLUTION);
    
    ledcAttachPin(ledPin, ledChannel);
    this->ledChannel = ledChannel;
}

LedController::~LedController() 
{
}

void LedController::Loop() 
{
    if(currMode == LedMode::Standard)
    {
        ledcWrite(ledChannel, 255);
    }
    else if(currMode == LedMode::Fade)
    {
        for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++)
        {
            ledcWrite(ledChannel, dutyCycle);
            delay(5);
        }

        for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--)
        {
            ledcWrite(ledChannel, dutyCycle);
            delay(5);
        }
    }
    else if(currMode == LedMode::Flash) 
    {
        ledcWrite(ledChannel, 255);
        delay(100);
        
        ledcWrite(ledChannel, 0);
        delay(500);
    }
    else 
    {
       for (int i = 0; i < 10; i++) { 
            ledcWrite(ledChannel, 255);
            delay(50); 
            
            ledcWrite(ledChannel, 0);
            delay(50); 
        }
        delay(500); 
    }
}

void LedController::SetMode(LedMode mode)
{
    currMode = mode;
}

LedMode LedController::GetMode()
{
    return currMode;
}



