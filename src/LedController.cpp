#include <LedController.h>
#include <Arduino.h>

LedController::LedController() : ledPwmChannel(1)
{
}

LedController::~LedController()
{
}

void LedController::Loop()
{
    for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){

        ledcWrite(ledPwmChannel, dutyCycle);
        delay(5);
    }


    for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){

      ledcWrite(ledPwmChannel, dutyCycle);
      delay(5);
    }
}