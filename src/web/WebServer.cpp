#include "WebServer.h"
#include <ESPmDNS.h>
#include <elegantWebpage.h>
#include <AsyncJson.h>
#include <ArduinoJson.h>
#include "Settings.h"

#define WEBAPP_DOMAIN "goalfinder"
#define WEBAPP_DIR "/web"
#define INDEX_PATH "/index.html"
#define COMPRESSED_FILE_EXTENSION ".gz"

FileSystem* internalFS;

static String GetContentType(const String* fileName) 
{
    if(fileName == 0) 
    {
        return "";
    }
    else if(fileName->endsWith("html")) 
    {
        return "text/html";
    }
    else if(fileName->endsWith("css")) 
    {
        return "text/css";
    }
    else if(fileName->endsWith("js")) 
    {
        return "application/javascript";
    }
    else if(fileName->endsWith("ico")) 
    {
        return "image/x-icon";
    }
    else 
    {
        //Serial.println("[ERROR] Unknown file type to get content type."); // Debugging: Handle unknown file types
        return "";
    }
}

static void HandleNotFound(AsyncWebServerRequest* request) 
{
    Serial.println("Failed Request: " + request->url());
    request->send(404, "text/plain", "Not found");
}

static void HandleRequest(AsyncWebServerRequest* request)
{
    //String filePath = WEBAPP_DIR + request->url();   
    
    String filePath = WEBAPP_DIR + request->url();  
    const String contentType = GetContentType(&filePath);
    filePath += COMPRESSED_FILE_EXTENSION;  

    Serial.println(filePath);

    if(!internalFS->FileExists(filePath))
    {
        filePath = WEBAPP_DIR INDEX_PATH COMPRESSED_FILE_EXTENSION;
    }

    File currFile = internalFS->OpenFile(filePath);  

    AsyncWebServerResponse *response = request->beginChunkedResponse(contentType, [currFile](uint8_t *buffer, size_t maxLen, size_t index) -> size_t 
    {
        File file = currFile;
        return file.read(buffer, maxLen);
    });

    request->onDisconnect([currFile] 
    {
        File file = currFile;
        file.close();
    }); 

    response->addHeader("Transfer-Encoding", "chunked");
    response->addHeader("Content-Encoding", "gzip"); //The complete webapp is compressed with gzip to save space and load the files faster
    request->send(response);
    request->beginResponseStream(contentType);
}

static void HandleLoadSettings(AsyncWebServerRequest* request) 
{
    AsyncJsonResponse* response = new AsyncJsonResponse();
    response->addHeader("Server", "Settings");
    JsonVariant& root = response->getRoot();

    Settings* settings = Settings::GetInstance();
    
    root["macAdress"] = settings->GetMacAddress();
    root["deviceName"] = settings->GetDeviceName();
    root["devicePassword"] = settings->GetDevicePassword();
    root["vibrationSensorSensitivity"] = settings->GetVibrationSensorSensitivity();
    root["volume"] = settings->GetVolume();

    response->setLength();
    request->send(response);
}

static void HandleSaveSettings(AsyncWebServerRequest* request) 
{
    JsonDocument document;

    if(request->hasParam("plain")) 
    {
        JsonDocument doc;
        
        deserializeJson(doc, request->getParam("plain")->value().c_str());

        Settings* settings = Settings::GetInstance();
        settings->SetDeviceName(doc["deviceName"]);
        settings->SetDevicePassword(doc["devicePassword"]);
        settings->SetVibrationSensorSensitivity(doc["vibrationSensorSensitivity"]);
        settings->SetVolume(doc["volume"]);
    }    

    request->send(204);
}

static void HandleRestart(AsyncWebServerRequest* request) 
{
    ESP.restart();
}

WebServer::WebServer(FileSystem* fileSystem) : server(80), updater(&server)
{
    internalFS = fileSystem;
    Init();
}

void WebServer::Init() 
{
    server.rewrite( "/", INDEX_PATH);        
    server.onNotFound(HandleNotFound); 
}

void WebServer::Begin() 
{
    if(!MDNS.begin(WEBAPP_DOMAIN)) 
    {
        Serial.println("[ERROR] Could not start mDNS service!");
    }

    updater.Begin();

    server.on("/loadsettings", HTTP_GET, HandleLoadSettings);
    server.on("/savesettings", HTTP_POST, HandleSaveSettings);
    server.on("/restart", HTTP_POST, HandleRestart);
    server.on("/*", HTTP_GET, HandleRequest);

    server.begin();
    Serial.println("[INFO] Started web server.");
}

void WebServer::Stop() 
{    
    MDNS.end();
    server.end();
}

WebServer::~WebServer()
{
    
}