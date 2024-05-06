#include <GoalfinderApp.h>
#include "soc/soc.h"           // Disable brownout problems
#include "soc/rtc_cntl_reg.h"  // Disable brownout problems

GoalfinderApp gf;

void setup() 
{
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brownout detector
    gf.Init();
}

void loop() 
{
    gf.Process();
}