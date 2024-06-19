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
const int GoalfinderApp::pinRandomSeed = 36;

const int GoalfinderApp::ledPwmChannel = 0;
const int GoalfinderApp::ledPwmFrequency = 5000;
const int GoalfinderApp::ledPwmResolution = 8;


const char* GoalfinderApp::hitClips[] = {
    "/hit-1.mp3",
    "/hit-2.mp3",
};
const int   GoalfinderApp::hitClipsCnt = sizeof(GoalfinderApp::hitClips) / sizeof(GoalfinderApp::hitClips[0]);
const char* GoalfinderApp::tickClips[] = {
    "/tick.mp3"
};
const int   GoalfinderApp::tickClipsCnt = sizeof(GoalfinderApp::tickClips) / sizeof(GoalfinderApp::tickClips[0]);
const char* GoalfinderApp::missClips[] = {
    "/miss-1.mp3",
    "/miss-2.mp3",
};
const int   GoalfinderApp::missClipsCnt = sizeof(GoalfinderApp::missClips) / sizeof(GoalfinderApp::missClips[0]);

const char* GoalfinderApp::defaultSsid = "Goal-Finder";
const char* GoalfinderApp::defaultWifiPw = 0; // no PW
// const char* GoalfinderApp::defaultWifiPw "esp123456";
const int GoalfinderApp::defaultAudioVolume = 5;

GoalfinderApp::GoalfinderApp() :
    Singleton<GoalfinderApp>(),
    fileSystem(true),
    webServer(&fileSystem),
    sntp(),
    audioPlayer(&fileSystem, pinI2sBclk, pinI2sWclk, pinI2sDataOut),
    tofSensor(),
    vibrationSensor(),
    ledController(pinLedPwm, ledPwmChannel)
{
}

GoalfinderApp::~GoalfinderApp() 
{
    // if (audioPlayer != 0) {
    //     delete audioPlayer;
    // }
}

void GoalfinderApp::Init() 
{
    delay(100); // swing in ;)
    Serial.begin(115200);    
    randomSeed(analogRead(pinRandomSeed));

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

    // audioPlayer = new AudioPlayer(&fileSystem, pinI2sBclk, pinI2sWclk, pinI2sDataOut);    
    
    int volume = Settings::GetInstance()->GetVolume();
    audioPlayer.SetVolume(volume);
}

void GoalfinderApp::Process()
{
    Serial.printf("%4.3f: process loop\n", millis() / 1000.0);

    const char* clipName = 0;
    if(!audioPlayer.GetIsPlaying())
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
                AnnounceHit();
            }
            else
            {
                AnnounceMiss();
            }
        }
        else {
            Serial.printf("%4.3f: reading ToF w/ vibration\n", millis() / 1000.0);
            if(tofSensor.ReadSingleMillimeters() < RANGE_WHEN_BALL_GOES_IN)
            {
                AnnounceHit();
            }
        }
    }
}

void GoalfinderApp::OnSettingsUpdated() 
{
    int volume = Settings::GetInstance()->GetVolume();
    audioPlayer.SetVolume(volume);
}

void GoalfinderApp::OnShotDetected() { 
    AnnounceEvent("-> shot", 0, 0);
}

void GoalfinderApp::AnnounceHit() {     
    AnnounceEvent("-> hit", hitClips, hitClipsCnt);
}

void GoalfinderApp::AnnounceMiss() {
    AnnounceEvent("-> miss", missClips, missClipsCnt);
}

void GoalfinderApp::AnnounceEvent(const char* traceMsg, const char* sounds[], size_t soundCnt) {    
    Serial.println(traceMsg);
    if (sounds != 0 && soundCnt > 0) {
        const char* clipName = sounds[random(0, soundCnt + 1)];
        PlaySound(clipName);
    }
}

void GoalfinderApp::PlaySound(const char* soundFileName) {
    if (soundFileName != 0 && !audioPlayer.GetIsPlaying()) {
        audioPlayer.PlayMP3(soundFileName);
        audioPlayer.Loop();
    }
}