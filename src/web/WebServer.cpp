#include "WebServer.h"
#include <ESPmDNS.h>
#include <AsyncJson.h>
#include <ArduinoJson.h>
#include <GoalfinderApp.h>

#include "Settings.h"

#define WEBAPP_DOMAIN "goalfinder"
#define WEBAPP_DIR "/web"
#define INDEX_PATH "/index.html"
#define COMPRESSED_FILE_EXTENSION ".gz"

#define API_URL "/api"

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
    Serial.printf("Web Server: received request %s\n", request->url().c_str());

    String filePath = WEBAPP_DIR + request->url();  
    const String contentType = GetContentType(&filePath);
    //filePath += COMPRESSED_FILE_EXTENSION;

    if(!internalFS->FileExists(filePath))
    {
        filePath = WEBAPP_DIR INDEX_PATH;//COMPRESSED_FILE_EXTENSION;
    }

    //File currFile = internalFS->OpenFile(filePath);  

    /*AsyncWebServerResponse *response = request->beginChunkedResponse(contentType, [currFile](uint8_t *buffer, size_t maxLen, size_t index) -> size_t 
    {
        File file = currFile;
        return file.read(buffer, maxLen);
    });

    request->onDisconnect([currFile] 
    {
        File file = currFile;
        file.close();
    }); */

    AsyncWebServerResponse* response = request->beginResponse(LittleFS, filePath, contentType);
    //response->addHeader("Cache-Control", "max-age=604800");
    //response->addHeader("Transfer-Encoding", "chunked");
    //response->addHeader("Content-Encoding", "gzip"); //The complete webapp is compressed with gzip to save space and load the files faster
    request->send(response);
    request->beginResponseStream(contentType);
}

static void HandleLoadSettings(AsyncWebServerRequest* request) 
{
    AsyncJsonResponse* response = new AsyncJsonResponse();
    response->addHeader("Server", "Settings");
    JsonVariant& root = response->getRoot();

    Settings* settings = Settings::GetInstance();    
    
    root["deviceName"] = settings->GetDeviceName();
    root["devicePassword"] = settings->GetDevicePassword();
    root["vibrationSensorSensitivity"] = settings->GetVibrationSensorSensitivity();
    root["volume"] = settings->GetVolume();
    root["ledMode"] = (int)settings->GetLedMode();
    root["macAddress"] = settings->GetMacAddress();
    root["isSoundEnabled"] = GoalfinderApp::GetInstance()->IsSoundEnabled();
    root["hitSound"] = settings->GetHitSound();
    root["missSound"] = settings->GetMissSound();

    response->setLength();
    request->send(response);
}

static void HandleSaveSettings(AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total) 
{
    JsonDocument doc;
        
    Serial.printf("Web Server: received settings: %s\n", data);
    deserializeJson(doc, (const char*)data);

    GoalfinderApp* app = GoalfinderApp::GetInstance();
    app->SetIsSoundEnabled(doc["isSoundEnabled"]);

    Settings* settings = Settings::GetInstance();
    settings->SetDeviceName(doc["deviceName"]);
    settings->SetDevicePassword(doc["devicePassword"]);
    settings->SetVibrationSensorSensitivity(doc["shotSensitivity"]);
    settings->SetVolume(doc["volume"]);
    settings->SetLedMode(doc["ledMode"]);
    settings->SetHitSound(doc["hitSound"]);
    settings->SetMissSound(doc["missSound"]);

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
    server.rewrite("", INDEX_PATH);
    server.rewrite("/", INDEX_PATH);
    server.onNotFound(HandleNotFound); 
    
    // TODO Replace any serial.out with "Log"
    Serial.println("Web server initialized!");
}

void WebServer::Begin() 
{
    if(!MDNS.begin(WEBAPP_DOMAIN)) 
    {
        Serial.println("[ERROR] Could not start mDNS service!");
    }

    updater.Begin(API_URL"/update");

    server.on(API_URL"/settings", HTTP_GET, HandleLoadSettings);
    server.on(API_URL"/settings", HTTP_POST, [](AsyncWebServerRequest* request) {}, 0, HandleSaveSettings);
    server.on(API_URL"/restart", HTTP_POST, HandleRestart);    
    server.on("/*", HTTP_GET, HandleRequest);
    //server.serveStatic("/", LittleFS, "/web/").setDefaultFile("index.html").setCacheControl("max-age=604800");

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