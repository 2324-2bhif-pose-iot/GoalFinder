#pragma once
#include <ESPAsyncWebServer.h>
#include <FileSystem.h>
#include "SoftwareUpdater.h"

class WebServer 
{
    public:
        virtual ~WebServer();
        void Begin();
        void Stop();
        WebServer(FileSystem* fileSystem);
    private:
        AsyncWebServer server;
        SoftwareUpdater updater;
        void Init();
};