#include <GoalfinderApp.h>
#include <Arduino.h>

#define RANGE_WHEN_BALL_GOES_IN 180
#define VIBRATION_WHEN_BALL_HITS_BOARD 2000



const int GoalfinderApp::pinTofSda = 22;
const int GoalfinderApp::pinTofScl = 21;
const int GoalfinderApp::pinI2sBclk = 23;
const int GoalfinderApp::pinI2sWclk = 5;
const int GoalfinderApp::pinI2sDataOut = 19;
const int GoalfinderApp::pinLedPwm = 17;

const int GoalfinderApp::ledPwmFrequency = 5000;
const int GoalfinderApp::ledPwmChannel = 0;
const int GoalfinderApp::ledPwmResolution = 8;

const char* GoalfinderApp::defaultSsid = "Goal-Finder";
const char* GoalfinderApp::defaultWifiPw = 0; // no PW
// const char* GoalfinderApp::defaultWifiPw "esp123456";
const int GoalfinderApp::defaultAudioVolume = 5;

GoalfinderApp::GoalfinderApp() :
    Singleton<GoalfinderApp>(),
    settings(),
    fileSystem(true),
    webServer(&fileSystem, &settings),
    sntp(),
    audioPlayer(0),
    tofSensor(),
    vibrationSensor()
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
    audioPlayer->SetVolume(defaultAudioVolume);
    
    ledcSetup(ledPwmChannel, ledPwmFrequency, ledPwmResolution);
    ledcAttachPin(pinLedPwm, ledPwmChannel);
}

void GoalfinderApp::Process()
{
    Serial.printf("%4.3f: process loop\n", millis() / 1000.0);

    audioPlayer->Loop();

    if(!audioPlayer->GetIsPlaying())
    {
        Serial.printf("%4.3f: LED on\n", millis() / 1000.0);
        for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++)
        {
            ledcWrite(ledPwmChannel, dutyCycle);
            delay(5);
        }

        Serial.printf("%4.3f: LED off\n", millis() / 1000.0);
        for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--)
        {
            ledcWrite(ledPwmChannel, dutyCycle);   
            delay(5);
        }

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