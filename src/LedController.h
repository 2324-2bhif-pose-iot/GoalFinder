#pragma once

class LedController
{

private:
    
    int ledChannel;

public:
   void Loop();
};

LedController::LedController()
{
}

LedController::~LedController()
{
}
