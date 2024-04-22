#pragma once
#include <ESPAsyncWebServer.h>
#include <file_system/FileSystem.h>

class WebApp 
{
    public:
        void Begin();
        void Stop();
        WebApp(FileSystem* fileSystem);
    private:
        //AsyncWebServer server;
        AsyncWebServer server;
        void Init();
};