#pragma once
#include <ESPAsyncWebServer.h>
#include <FileSystem.h>

class WebServer 
{
    public:
        virtual ~WebServer();
        void Begin();
        void Stop();
        WebServer(FileSystem* fileSystem);
    private:
        //AsyncWebServer server;
        AsyncWebServer server;
        void Init();
};