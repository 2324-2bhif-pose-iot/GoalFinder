#pragma once

class LedController {

public:
    LedController();
    virtual ~LedController();
    void Loop();

private:    
    int ledPwmChannel;

};
