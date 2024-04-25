#pragma once
#include "time.h"

class SNTP 
{
    public:
        void Init(); 
        struct tm GetLocalTime();
};
