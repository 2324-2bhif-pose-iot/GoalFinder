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

GoalfinderApp::GoalfinderApp() :
    Singleton<GoalfinderApp>(),
    fileSystem(true),
    webServer(&fileSystem),
    sntp(),
    audioPlayer(&fileSystem, pinI2sBclk, pinI2sWclk, pinI2sDataOut),
    tofSensor(),
    vibrationSensor(),
    ledController(pinLedPwm, ledPwmChannel),
    metronomeIntervalMs(1500),
    lastMetronomeTickTime(0),
    announcement(Announcement::None),
    lastShockTime(0)
{
}

GoalfinderApp::~GoalfinderApp() 
{
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
    
    Settings* settings = Settings::GetInstance();
    String ssid = settings->GetDeviceName();
    String wifiPw = settings->GetDevicePassword();

    WiFi.softAP(ssid, wifiPw);
    WiFi.setSleep(false);
    Serial.println(WiFi.softAPIP());

    webServer.Begin();
    
    sntp.Init();
    vibrationSensor.Init();
    tofSensor.Init(pinTofScl, pinTofSda);

    ledController.SetMode(LedMode::Flash);

    UpdateSettings(true);
}

void GoalfinderApp::Process()
{
    // Serial.printf("%4.3f: processing ...\n", millis() / 1000.0);

    UpdateSettings();
    audioPlayer.Loop();
    
    if (!audioPlayer.GetIsPlaying()) {
        ledController.Loop();
        TickMetronome();
    }
    if (!audioPlayer.GetIsPlaying()) {
        GoalfinderApp::DetectShot();
        ProcessAnnouncement();
    }
}

void GoalfinderApp::UpdateSettings(bool force) {
    Settings* settings = Settings::GetInstance();
    if (force || settings->IsModified()) {
        audioPlayer.SetVolume(settings->GetVolume());
        vibrationSensor.SetSensitivity(settings->GetVibrationSensorSensitivity());
        // TODO: Add Led-Mode setting
        // TODO: Add metronome interval in milliseconds
    }
}

void GoalfinderApp::TickMetronome() {
    unsigned long currentTime = millis();
    if ((currentTime - lastMetronomeTickTime) > metronomeIntervalMs) {
        lastMetronomeTickTime = currentTime;
        PlaySound(tickClips[0]);
        audioPlayer.Loop();
    }
}

void GoalfinderApp::OnShotDetected() {
    announcement = Announcement::Shot;
    Serial.printf("%4.3f: announce shot: %d\n", millis() / 1000.0, announcement);
}

void GoalfinderApp::AnnounceHit() {
    announcement = Announcement::Hit;
    Serial.printf("%4.3f: announce hit: %d\n", millis() / 1000.0, announcement);
}

void GoalfinderApp::AnnounceMiss() {
    announcement = Announcement::Miss;
}

void GoalfinderApp::ProcessAnnouncement() {
    // Serial.printf("%4.3f: processing announcements: %d\n", millis() / 1000.0, announcement);
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
    if (soundFileName != 0) {
        Serial.printf("%4.3f: starting playback of: '%s'\n", millis() / 1000.0, soundFileName != 0 ? soundFileName : "NULL");
        audioPlayer.PlayMP3(soundFileName);
    }
}

void GoalfinderApp::DetectShot() {
    // Serial.printf("%4.3f: reading vibration\n", millis() / 1000.0);
    if(lastShockTime == 0 && vibrationSensor.Vibration() > shotVibrationThreshold) {
        lastShockTime = millis();
        Serial.printf("%4.3f: shot detected\n", millis() / 1000.0);
    }

    unsigned long currentTime = millis();
    if (lastShockTime > 0 && (currentTime - lastShockTime) < maxShotDurationMs) {
        int distance = tofSensor.ReadSingleMillimeters();
        Serial.printf("%4.3f: detecting hit: d = [%d < %d]\n", millis() / 1000.0, distance, ballHitDetectionDistance);
        if(distance < ballHitDetectionDistance) {
            AnnounceHit();
            lastShockTime = 0;
        }
    }
    if (lastShockTime > 0 && (currentTime - lastShockTime) > maxShotDurationMs) {
        Serial.printf("%4.3f: miss detected\n", millis() / 1000.0);
        AnnounceMiss();
        lastShockTime = 0;
    }
}