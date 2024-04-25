#pragma once
#include <ESPAsyncWebServer.h>
#include <file_system/FileSystem.h>

class WebServer 
{
    public:
        void Begin();
        void Stop();
        WebServer(FileSystem* fileSystem);
    private:
        //AsyncWebServer server;
        AsyncWebServer server;
        void Init();
};