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
// const int GoalfinderApp::ledPwmFrequency = 5000;
// const int GoalfinderApp::ledPwmResolution = 8;


const int GoalfinderApp::ballHitDetectionDistance = 180;
const int GoalfinderApp::shotVibrationThreshold = 2000;
const int GoalfinderApp::maxShotDurationMs = 5000;


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
    announcement(Announcement::None),
    fileSystem(true),
    webServer(&fileSystem),
    sntp(),
    audioPlayer(&fileSystem, pinI2sBclk, pinI2sWclk, pinI2sDataOut),
    tofSensor(),
    vibrationSensor(),
    ledController(pinLedPwm, ledPwmChannel),
    shotDetectionTask(),
    shotDetectionActive(false)
{
}

GoalfinderApp::~GoalfinderApp() 
{
    shotDetectionActive = false;
    vTaskDelete(&shotDetectionTask);
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

    ledController.SetMode(LedMode::Flash);

    // audioPlayer = new AudioPlayer(&fileSystem, pinI2sBclk, pinI2sWclk, pinI2sDataOut);    
    
    int volume = Settings::GetInstance()->GetVolume();
    audioPlayer.SetVolume(volume);

    StartShotDetector();
}

void GoalfinderApp::Process()
{
    Serial.printf("%4.3f: processing ...\n", millis() / 1000.0);
    ledController.Loop();
    audioPlayer.Loop();
    ProcessAnnouncement();

    delay(1); // get other tasks a chance to run
        
    // if(!audioPlayer.GetIsPlaying())
    // {
    //     Serial.printf("%4.3f: reading vibration\n", millis() / 1000.0);
    //     if(vibrationSensor.Vibration() > shotVibrationThreshold)
    //     {
    //         OnShotDetected();
    //         delay(3000);

    //         Serial.printf("%4.3f: reading ToF\n", millis() / 1000.0);
    //         if(tofSensor.ReadSingleMillimeters() < ballHitDetectionDistance)
    //         {      
    //             AnnounceHit();
    //         }
    //         else
    //         {
    //             AnnounceMiss();
    //         }
    //     }
    //     else {
    //         Serial.printf("%4.3f: reading ToF w/ vibration\n", millis() / 1000.0);
    //         if(tofSensor.ReadSingleMillimeters() < ballHitDetectionDistance)
    //         {
    //             AnnounceHit();
    //         }
    //     }
    // }
}

void GoalfinderApp::OnSettingsUpdated() 
{
    int volume = Settings::GetInstance()->GetVolume();
    audioPlayer.SetVolume(volume);
}

void GoalfinderApp::OnShotDetected() { 
    announcement = Announcement::Shot;
}

void GoalfinderApp::AnnounceHit() { 
    announcement = Announcement::Hit;
}

void GoalfinderApp::AnnounceMiss() {
    announcement = Announcement::Miss;
}

void GoalfinderApp::ProcessAnnouncement() {
    switch(announcement) {
        case Announcement::Shot:
            AnnounceEvent("-> shot", 0, 0);
            break;
        case Announcement::Hit:
            AnnounceEvent("-> hit", hitClips, hitClipsCnt);
            break;
        case Announcement::Miss:
            AnnounceEvent("-> miss", missClips, missClipsCnt);
            break;
        default:
            break;
    }
    announcement = Announcement::None;
}

void GoalfinderApp::AnnounceEvent(const char* traceMsg, const char* sounds[], size_t soundCnt) {  
    Serial.printf("%4.3f: announcing event '%s'\n", millis() / 1000.0, traceMsg);  
    Serial.println(traceMsg);
    if (sounds != 0 && soundCnt > 0) {
        const char* clipName = sounds[random(0, soundCnt + 1)];
        PlaySound(clipName);
    }
}

void GoalfinderApp::PlaySound(const char* soundFileName) {
    if (soundFileName != 0 && !audioPlayer.GetIsPlaying()) {
Serial.printf("%4.3f: start playback\n", millis() / 1000.0);
        audioPlayer.PlayMP3(soundFileName);
    }
}

void GoalfinderApp::StartShotDetector() {  
    Serial.printf("%4.3f: starting shot detector\n", millis() / 1000.0);

    shotDetectionActive = true;
    const uint32_t stackDepth = 4096;
    void* taskArgs = this; 
    UBaseType_t priority = 6;
    BaseType_t coreId = 1;
    xTaskCreatePinnedToCore(GoalfinderApp::DetectShot, "shot_detector", 
        stackDepth, taskArgs, 
        priority, &shotDetectionTask, coreId);
}


void GoalfinderApp::DetectShot(void* args) {
    GoalfinderApp* app = (GoalfinderApp*)args;
    unsigned long lastShockTime = 0;

    while(app != 0 && app->shotDetectionActive) {
        Serial.printf("%4.3f: reading vibration\n", millis() / 1000.0);
        if(lastShockTime == 0 && app->vibrationSensor.Vibration() > shotVibrationThreshold) {
            lastShockTime = millis();
            Serial.printf("%4.3f: shot detected\n", millis() / 1000.0);
        }

        unsigned long currentTime = millis();
        if (lastShockTime > 0 && (currentTime - lastShockTime) < maxShotDurationMs) {
            Serial.printf("%4.3f: detecting hit\n", millis() / 1000.0);
            if(app->tofSensor.ReadSingleMillimeters() < ballHitDetectionDistance) {
                app->AnnounceHit();
                lastShockTime = 0;
            }
        }
        if (lastShockTime > 0 && (currentTime - lastShockTime) > maxShotDurationMs) {
            app->AnnounceMiss();
            lastShockTime = 0;
        }
    }
    
}