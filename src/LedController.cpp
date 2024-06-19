#include "LedController.h"
#include <Arduino.h>

void LedController::Loop() 
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