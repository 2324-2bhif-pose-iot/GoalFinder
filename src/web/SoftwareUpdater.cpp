#include "SoftwareUpdater.h"
#include <AsyncElegantOTA.h>

SoftwareUpdater::SoftwareUpdater(AsyncWebServer* server) 
{
    this->server = server;
}

void SoftwareUpdater::Begin() 
{
    AsyncElegantOTA.begin(server);    
}