#pragma once
#include <Arduino.h>
#include <LittleFS.h>

class FileSystem 
{
    public:
        bool Begin();
        File OpenFile(String path);
        bool FileExists(String path);
        int GetFreeSpace();
        fs::FS* GetInternalFileSystem();
        FileSystem(bool deleteOnFailed);
    private:
        bool deleteOnFailed;
};