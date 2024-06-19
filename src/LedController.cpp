#include "LedController.h"
#include <Arduino.h>

LedController::LedController() :
{
}

LedController::~LedController() 
{
}

void LedController::Init(int ledPin) 
{
    ledcSetup(ledChannel, 5000, 8);
    
    ledcAttachPin(ledPin, ledChannel);
}

void LedController::Loop() 
{
    /*if(Standard)
    {
        ledcWrite(ledChannel, 255);
    }
    else if(Fade)
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
    else if(Flash) 
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
    }*/
}