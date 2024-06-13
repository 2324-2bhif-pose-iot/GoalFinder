#pragma once
#include <ESPAsyncWebServer.h>

class SoftwareUpdater 
{
    public:
        SoftwareUpdater(AsyncWebServer* server);
        void Begin();
    private:
        AsyncWebServer* server;
};