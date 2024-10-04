#include "SoftwareUpdater.h"
// #include <AsyncOTA.h>
// #include <ElegantOTA.h>

SoftwareUpdater::SoftwareUpdater(AsyncWebServer* server) 
{
    this->server = server;
}

void SoftwareUpdater::Begin() 
{
    // ElegantOTA.begin(server);    
    // AsyncOTA.begin(server);    
}