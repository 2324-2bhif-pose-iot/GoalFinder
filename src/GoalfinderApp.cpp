#include <GoalfinderApp.h>
#include <Arduino.h>
#include <Settings.h>

#define RANGE_WHEN_BALL_GOES_IN 180
#define VIBRATION_WHEN_BALL_HITS_BOARD 2000

const int GoalfinderApp::pinTofSda = 22;
const int GoalfinderApp::pinTofScl = 21;
const int GoalfinderApp::pinI2sBclk = 23;
const int GoalfinderApp::pinI2sWclk = 5;
const int GoalfinderApp::pinI2sDataOut = 19;
const int GoalfinderApp::pinLedPwm = 17;

const int GoalfinderApp::ledPwmChannel = 0;
const int GoalfinderApp::ledPwmFrequency = 5000;
const int GoalfinderApp::ledPwmResolution = 8;

const char* GoalfinderApp::defaultSsid = "Goal-Finder";
const char* GoalfinderApp::defaultWifiPw = 0; // no PW
// const char* GoalfinderApp::defaultWifiPw "esp123456";
const int GoalfinderApp::defaultAudioVolume = 5;

GoalfinderApp::GoalfinderApp() :
    Singleton<GoalfinderApp>(),
    fileSystem(true),
    webServer(&fileSystem, Settings::GetInstance()),
    sntp(),
    audioPlayer(0),
    tofSensor(),
    vibrationSensor(),
    ledController()
{
}

GoalfinderApp::~GoalfinderApp() 
{
    if (audioPlayer != 0) {
        delete audioPlayer;
    }
}

void GoalfinderApp::Init() 
{
    delay(100);
    Serial.begin(115200);

    if(!fileSystem.Begin()) 
    {
        Serial.println("FS initialization failed");
        return;
    } else {
        Serial.println("FS initialized");
    }
    
    WiFi.softAP(defaultSsid, defaultWifiPw);
    WiFi.setSleep(false);
    Serial.println(WiFi.softAPIP());

    webServer.Begin();
    
    sntp.Init();
    vibrationSensor.Init();
    tofSensor.Init(pinTofScl, pinTofSda);

    audioPlayer = new AudioPlayer(&fileSystem, pinI2sBclk, pinI2sWclk, pinI2sDataOut);    
    
    int volume = Settings::GetInstance()->GetVolume();
    audioPlayer->SetVolume(volume);
    
	ledController.Init(pinLedPwm, ledPwmChannel, ledPwmFrequency, ledPwmResolution);
}

void GoalfinderApp::Process()
{
    Serial.printf("%4.3f: process loop\n", millis() / 1000.0);

    audioPlayer->Loop();

    if(!audioPlayer->GetIsPlaying())
    {
        Serial.printf("%4.3f: LED on\n", millis() / 1000.0);
        ledController.Loop();

        Serial.printf("%4.3f: processing input\n", millis() / 1000.0);
        if(vibrationSensor.Vibration() > VIBRATION_WHEN_BALL_HITS_BOARD)
        {
            Serial.printf("%4.3f: vibration\n", millis() / 1000.0);
            Serial.println("Shot detected: ");
            delay(3000);

            Serial.printf("%4.3f: reading ToF\n", millis() / 1000.0);
            if(tofSensor.ReadSingleMillimeters() < RANGE_WHEN_BALL_GOES_IN)
            {      
                Serial.println("-> hit");
            }
            else
            {
                Serial.println("-> miss");
                audioPlayer->PlayMP3("/miss.mp3");
            }
        }
        else {
            Serial.printf("%4.3f: reading ToF w/ vibration\n", millis() / 1000.0);
            if(tofSensor.ReadSingleMillimeters() < RANGE_WHEN_BALL_GOES_IN)
            {
                Serial.println("Hit without shot detected");
                audioPlayer->PlayMP3("/hit.mp3");
            }
        }
    } 
}

void GoalfinderApp::OnSettingsUpdated() 
{
    int volume = Settings::GetInstance()->GetVolume();
    audioPlayer->SetVolume(volume);
}