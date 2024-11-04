#include <GoalfinderApp.h>
// #include <Arduino.h>
#include <HardwareSerial.h>
#include <Settings.h>

// Cleanup - replaced by constants
// #define RANGE_WHEN_BALL_GOES_IN 180
// #define VIBRATION_WHEN_BALL_HITS_BOARD 2000

const int GoalfinderApp::pinTofSda = 22;
const int GoalfinderApp::pinTofScl = 21;
const int GoalfinderApp::pinI2sBclk = 23;
const int GoalfinderApp::pinI2sWclk = 5;
const int GoalfinderApp::pinI2sDataOut = 19;
const int GoalfinderApp::pinLedPwm = 17;
const int GoalfinderApp::pinRandomSeed = 36;

const int GoalfinderApp::ledPwmChannel = 0;

const int GoalfinderApp::ballHitDetectionDistance = 500; // TODO: Make configurable
const int GoalfinderApp::shotVibrationThreshold = 4000; // TODO: Make configurable??
const int GoalfinderApp::maxShotDurationMs = 5000; // TODO: Make configurable

const char* GoalfinderApp::waitingClip = "/waiting.mp3";

const char* GoalfinderApp::hitClips[] = {
    "/hit-1.mp3",
    // "/hit-2.mp3",
};
const int   GoalfinderApp::hitClipsCnt = sizeof(GoalfinderApp::hitClips) / sizeof(GoalfinderApp::hitClips[0]);

const char* GoalfinderApp::tickClips[] = {
    "/tick-1.mp3"
};
const int   GoalfinderApp::tickClipsCnt = sizeof(GoalfinderApp::tickClips) / sizeof(GoalfinderApp::tickClips[0]);

const char* GoalfinderApp::missClips[] = {
    "/miss-1.mp3",
    // "/miss-2.mp3",
    // "/miss-3.mp3",
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
    announcing(false),
    metronomeIntervalMs(2000),
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

    // TODO: Replace all serial outputs with "Log" for a more fine grained logging control
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
    DetectShot();
    ProcessAnnouncement();
    ledController.Loop();
    
    if (!audioPlayer.IsPlaying()) {
        TickMetronome();
    }

    delay(1); //For webserver
}

void GoalfinderApp::UpdateSettings(bool force) {
    Settings* settings = Settings::GetInstance();
    if (force || settings->IsModified()) {
        audioPlayer.SetVolume(settings->GetVolume());
        ledController.SetMode(settings->GetLedMode());
        vibrationSensor.SetSensitivity(settings->GetVibrationSensorSensitivity());
        // TODO: Add metronome interval in milliseconds
        // TODO: Add "expert mode" for LED:
            // TODO: Add LED fade in time (softness),
            // TODO: Add LED on time (shine),
            // TODO: Add LED fade out time (softness),
            // TODO: Add option to sync LED fade out time with fade in time,
            // TODO: Add LED off time (dark),
            // TODO: Add number of repetitions (see "Turbo"),
            // TODO: Add blank time (only when for more than 1 repetition - see Turbo),
            // TODO: Implement a generic LED controller method based on the settings above 
            //       and reimplement predefined LED controller patterns to set those settings accordingly
    }
}

void GoalfinderApp::TickMetronome() {
    unsigned long currentTime = millis();
    if ((currentTime - lastMetronomeTickTime) > metronomeIntervalMs) {
        lastMetronomeTickTime = currentTime;
        const char* clipName = tickClips[0];
        if (lastShockTime > 0) {
            // shot detection pending
            clipName = waitingClip;
        }
        PlaySound(clipName);
    }
}

void GoalfinderApp::OnShotDetected() {
    announcement = Announcement::Shot;
    Serial.printf("%4.3f: announce shot: %d\n", millis() / 1000.0, announcement);
}

void GoalfinderApp::AnnounceHit() {
    announcement = Announcement::Hit;
    // Serial.printf("%4.3f: announce hit: %d\n", millis() / 1000.0, announcement);
}

void GoalfinderApp::AnnounceMiss() {
    announcement = Announcement::Miss;
    // Serial.printf("%4.3f: announce miss: %d\n", millis() / 1000.0, announcement);
}

void GoalfinderApp::ProcessAnnouncement() {
    // Serial.printf("%4.3f: processing announcements: %d\n", millis() / 1000.0, announcement);
    switch(announcement) {
        case Announcement::Shot:
            AnnounceEvent("-> shot", 0);
            break;
        case Announcement::Hit:
            AnnounceEvent("-> hit", hitClips[0]);
            break;
        case Announcement::Miss:
            AnnounceEvent("-> miss", missClips[0]);
            break;
        default:
            break;
    }
    announcement = Announcement::None;
}

void GoalfinderApp::AnnounceEvent(const char* traceMsg, const char* sound) {
    Serial.printf("%4.3f: announcing event '%s'\n", millis() / 1000.0, traceMsg);
    if (sound != 0) {
        announcing = true;
        PlaySound(sound);
    }
}

void GoalfinderApp::PlaySound(const char* soundFileName) {
    if (soundFileName != 0) {
        Serial.printf("%4.3f: starting playback of: '%s'\n", millis() / 1000.0, soundFileName != 0 ? soundFileName : "NULL");
        audioPlayer.PlayMP3(soundFileName);
    }
}

void GoalfinderApp::DetectShot() {
    // Serial.printf("%4.3f: starting shot detection ...\n", millis() / 1000.0);
    // if(lastShockTime == 0 && vibrationSensor.Vibration(5000) > shotVibrationThreshold) {
    if(lastShockTime == 0) {
        if (!(announcing && audioPlayer.IsPlaying())) {
            announcing = false; // reset announcing after playback is finished
            // TODO Make magic number of vibration measurement timeout constant
            long vibration = vibrationSensor.Vibration(10000);
            if (vibration > 0) {
                Serial.printf("%4.3f: measured vibration %ld ...\n", millis() / 1000.0, vibration);
            }
            // TODO Make "shotVibrationThreshold" the "sensibility" of the shock-sensor
            if (vibration > shotVibrationThreshold) {
                lastShockTime = millis();
                Serial.printf("%4.3f: shot detected\n", millis() / 1000.0);
            }
        }
    }

    unsigned long currentTime = millis();
    if (lastShockTime > 0 && (currentTime - lastShockTime) < maxShotDurationMs) {
        int distance = tofSensor.ReadSingleMillimeters();
        Serial.printf("%4.3f: detecting hit: d = [%d < %d]\n", millis() / 1000.0, distance, ballHitDetectionDistance);
        // TODO make lower limit a constant
        if(distance > 20 && distance < ballHitDetectionDistance) {
            AnnounceHit();
            lastShockTime = 0;
        }
    }
    if (lastShockTime > 0 && (currentTime - lastShockTime) > maxShotDurationMs) {
        Serial.printf("%4.3f: miss detected\n", millis() / 1000.0);
        AnnounceMiss();
        lastShockTime = 0;
    }
    // Serial.printf("%4.3f: ... completed shot detection\n", millis() / 1000.0);
}