#include "WebServer.h"
#include <ESPmDNS.h>

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

static void HandleError() 
{

}

WebServer::WebServer(FileSystem* fileSystem) : server(80)
{
    internalFS = fileSystem;
    Init();
}

void WebServer::Init() 
{
    server.rewrite( "/", INDEX_PATH);
    server.on("/*", HTTP_GET, HandleRequest);
    server.onNotFound(HandleNotFound); 
}

void WebServer::Begin() 
{
    if(!MDNS.begin(WEBAPP_DOMAIN)) 
    {
        Serial.println("[ERROR] Could not start mDNS service!");
    }

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