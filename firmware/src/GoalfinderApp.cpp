#include <GoalfinderApp.h>
// #include <Arduino.h>
#include <HardwareSerial.h>
#include <Settings.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ESPmDNS.h>

#define WEBAPP_DOMAIN "goalfinder"

// Cleanup - replaced by constants
// #define RANGE_WHEN_BALL_GOES_IN 180
// #define VIBRATION_WHEN_BALL_HITS_BOARD 2000

const int GoalfinderApp::wifiTimeout = 10; // In Seconds
const int GoalfinderApp::pinTofSda = 22;
const int GoalfinderApp::pinTofScl = 21;
const int GoalfinderApp::pinI2sBclk = 23;
const int GoalfinderApp::pinI2sWclk = 5;
const int GoalfinderApp::pinI2sDataOut = 19;
const int GoalfinderApp::pinLedPwm = 17;
const int GoalfinderApp::pinRandomSeed = 36;

const int GoalfinderApp::ledPwmChannel = 0;

// const int GoalfinderApp::ballHitDetectionDistance = 180; // TODO: Make configurable
const int GoalfinderApp::shotVibrationThreshold = 3000; // TODO: Make configurable??
const int GoalfinderApp::maxShotDurationMs = 1500;//3500;      // TODO: Mtake configurable

//const char *GoalfinderApp::waitingClip = "/waiting.mp3";

const char *GoalfinderApp::hitClips[] = {
    "/hit-1.mp3",
    // "/hit-2.mp3",
};

const int GoalfinderApp::hitClipsCnt = sizeof(GoalfinderApp::hitClips) / sizeof(GoalfinderApp::hitClips[0]);

const char *GoalfinderApp::tickClips[] = {
    "/tick-1.mp3",
    "/waiting.mp3",
    "/tick-4.mp3"
};

const int GoalfinderApp::tickClipsCnt = sizeof(GoalfinderApp::tickClips) / sizeof(GoalfinderApp::tickClips[0]);

const char *GoalfinderApp::missClips[] = {
    "/miss-1.mp3",
    "/miss-3.mp3",
    "/miss-2.mp3",
};
const int GoalfinderApp::missClipsCnt = sizeof(GoalfinderApp::missClips) / sizeof(GoalfinderApp::missClips[0]);

GoalfinderApp::GoalfinderApp() : Singleton<GoalfinderApp>(),
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

void GoalfinderApp::SetIsSoundEnabled(bool value)
{
    this->isSoundEnabled = value;
}

bool GoalfinderApp::IsSoundEnabled()
{
    return this->isSoundEnabled;
}

bool GoalfinderApp::GetIsClient()
{
    return this->isClient;
}

int GoalfinderApp::GetDetectedHits()
{
    return detectedHits;
}

int GoalfinderApp::GetDetectedMisses()
{
    return detectedMisses;
}

GoalfinderApp::~GoalfinderApp()
{
    MDNS.end();
    webServer.Stop();
}

void GoalfinderApp::InitAP()
{
    if (!MDNS.begin(WEBAPP_DOMAIN))
    {
        Serial.println("[ERROR] Could not start mDNS service!");
    }

    Settings *settings = Settings::GetInstance();

    String ssid = settings->GetDeviceName();
    String wifiPw = settings->GetDevicePassword();

    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, wifiPw);
    WiFi.setSleep(false);
    Serial.println(WiFi.softAPIP());
}

void GoalfinderApp::Init()
{
    delay(100); // swing in ;)
    Serial.begin(115200);
    randomSeed(analogRead(pinRandomSeed));

    // TODO: Replace all serial outputs with "Log" for a more fine grained logging control
    if (!fileSystem.Begin())
    {
        Serial.println("FS initialization failed");
        return;
    }
    else
    {
        Serial.println("FS initialized");
    }

    Settings *settings = Settings::GetInstance();

    WiFi.mode(WIFI_STA);
    WiFi.begin("GoalFinder Hub");

    int timeout = 0;

    while (WiFi.status() != WL_CONNECTED && timeout <= wifiTimeout)
    {
        delay(1000);
        timeout += 1;
        Serial.print(".");
    }

    if (timeout <= wifiTimeout)
    {
        Serial.println(WiFi.localIP());

        HTTPClient http;
        http.begin("http://goalfinderhub.local:3000/api/devices/");

        JsonDocument doc;

        doc["macAddress"] = settings->GetMacAddress();
        doc["ipAddress"] = WiFi.localIP().toString();
        doc["deviceName"] = settings->GetDeviceName();
        doc["devicePassword"] = settings->GetDevicePassword();
        doc["vibrationSensorSensitivity"] = settings->GetVibrationSensorSensitivity();
        doc["volume"] = settings->GetVolume();
        doc["ledMode"] = (int)settings->GetLedMode();

        String requestBody;
        serializeJson(doc, requestBody);

        http.addHeader("Content-Type", "application/json");
        int responseCode = http.POST(requestBody);

        if (responseCode == 204)
        {
            Serial.printf("HTTP POST success: %d\n", responseCode);
            String response = http.getString();
            Serial.println(response);

            this->isClient = true;
        }
        else
        {
            Serial.printf("HTTP POST failed: %s\n", http.errorToString(responseCode).c_str());
        }

        http.end();
    }

    if (!this->isClient)
    {
        SetIsSoundEnabled(true);
        InitAP();
    }

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

    if (this->isSoundEnabled)
    {
        audioPlayer.Loop();
        DetectShot();
        ProcessAnnouncement();
        ledController.Loop();

        if (!audioPlayer.IsPlaying())
        {
            TickMetronome();
        }
    }

    delay(1); // For webserver
}

void GoalfinderApp::UpdateSettings(bool force)
{
    Settings *settings = Settings::GetInstance();
    if (force || settings->IsModified())
    {
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

void GoalfinderApp::ResetDetectedHits()
{
    detectedHits = 0;
}

void GoalfinderApp::ResetDetectedMisses()
{
    detectedMisses = 0;
}

void GoalfinderApp::TickMetronome()
{
    unsigned long currentTime = millis();
    if ((currentTime - lastMetronomeTickTime) > metronomeIntervalMs)
    {
        lastMetronomeTickTime = currentTime;
        //const char *clipName = tickClips[0];
        const char *clipName = tickClips[Settings::GetInstance()->GetMetronomeSound()];
        /*if (lastShockTime > 0)
        {
            // shot detection pending
            clipName = waitingClip;
        }*/
        PlaySound(clipName);
    }
}

void GoalfinderApp::OnShotDetected()
{
    announcement = Announcement::Shot;
    Serial.printf("%4.3f: announce shot: %d\n", millis() / 1000.0, announcement);
}

void GoalfinderApp::AnnounceHit()
{
    announcement = Announcement::Hit;
    detectedHits++;

    if (this->isClient)
    {
        HTTPClient http;
        http.begin("http://goalfinderhub.local:3000/api/games/hit");
        http.addHeader("Content-Type", "application/json");

        JsonDocument doc;

        doc["macAddress"] = Settings::GetInstance()->GetMacAddress();

        String requestBody;
        serializeJson(doc, requestBody);

        int responseCode = http.POST(requestBody);

        if (responseCode != 204)
        {
            Serial.printf("HTTP POST on hit failed: %s\n", http.errorToString(responseCode).c_str());
        }
    }
    // Serial.printf("%4.3f: announce hit: %d\n", millis() / 1000.0, announcement);
}

void GoalfinderApp::AnnounceMiss()
{
    announcement = Announcement::Miss;
    detectedMisses++;
    // Serial.printf("%4.3f: announce miss: %d\n", millis() / 1000.0, announcement);
}

void GoalfinderApp::ProcessAnnouncement()
{
    // Serial.printf("%4.3f: processing announcements: %d\n", millis() / 1000.0, announcement);
    switch (announcement)
    {
    case Announcement::Shot:
        AnnounceEvent("-> shot", 0);
        // Send websocket
        break;
    case Announcement::Hit:
        //AnnounceEvent("-> hit", hitClips[0]);
        AnnounceEvent("-> hit", hitClips[Settings::GetInstance()->GetHitSound()]);
        break;
    case Announcement::Miss:
        //AnnounceEvent("-> miss", missClips[0]);
        AnnounceEvent("-> miss", missClips[Settings::GetInstance()->GetMissSound()]);
        break;
    default:
        break;
    }
    announcement = Announcement::None;
}

void GoalfinderApp::AnnounceEvent(const char *traceMsg, const char *sound)
{
    Serial.printf("%4.3f: announcing event '%s'\n", millis() / 1000.0, traceMsg);
    if (sound != 0)
    {
        announcing = true;
        PlaySound(sound);
    }
}

void GoalfinderApp::PlaySound(const char *soundFileName)
{
    if (soundFileName != 0)
    {
        Serial.printf("%4.3f: starting playback of: '%s'\n", millis() / 1000.0, soundFileName != 0 ? soundFileName : "NULL");
        audioPlayer.PlayMP3(soundFileName);
    }
}

void GoalfinderApp::DetectShot()
{
    // TODO fix
    //Serial.printf("%4.3f: starting shot detection ...\n", millis() / 1000.0);
    //  if(lastShockTime == 0 && vibrationSensor.Vibration(5000) > shotVibrationThreshold) {
    /*if (lastShockTime == 0)
    {
        if (!announcing) // skip vibration only if announcing an event
        {
            long vibration = vibrationSensor.Vibration(10000);

            if (vibration > 0)
            {
                Serial.printf("%4.3f: measured vibration %ld ...\n", millis() / 1000.0, vibration);
            }

            if (vibration > shotVibrationThreshold)
            {
                lastShockTime = millis();
                Serial.printf("%4.3f: shot detected\n", millis() / 1000.0);
            }
        }
    }*/

    if (lastShockTime == 0)
    {
        if (!(announcing && audioPlayer.IsPlaying()))
        {
            announcing = false; // reset announcing after playback is finished

            // TODO Make magic number of vibration measurement timeout constant
            long vibration = vibrationSensor.Vibration(10000);
            if (vibration > 0)
            {
                Serial.printf("%4.3f: measured vibration %ld ...\n", millis() / 1000.0, vibration);
            }
            // TODO Make "shotVibrationThreshold" the "sensibility" of the shock-sensor
            if (vibration > shotVibrationThreshold)
            {
                lastShockTime = millis();
                Serial.printf("%4.3f: shot detected\n", millis() / 1000.0);
            }
        }
    }

    /*if (lastShockTime == 0)
    {
        if (audioPlayer.IsPlaying())
        {
            // While audio is playing, skip vibration measurement completely
            announcing = true; // flag that playback is ongoing
        }
        else
        {
            // Playback finished
            announcing = false;

            // Only measure vibration when no audio is playing
            long vibration = vibrationSensor.Vibration(10000);
            if (vibration > 0)
            {
                Serial.printf("%4.3f: measured vibration %ld ...\n", millis() / 1000.0, vibration);
            }
            if (vibration > shotVibrationThreshold)
            {
                lastShockTime = millis();
                Serial.printf("%4.3f: shot detected\n", millis() / 1000.0);
            }
        }
    }*/

    int ballHitDetectionDistance = 150; //Settings::GetInstance()->GetBallHitDetectionDistance();

    unsigned long currentTime = millis();
    if (lastShockTime > 0 && (currentTime - lastShockTime) < maxShotDurationMs)
    {
        int distance = tofSensor.ReadSingleMillimeters();
        Serial.printf("%4.3f: detecting hit: d = [%d < %d]\n", millis() / 1000.0, distance, ballHitDetectionDistance);
        
        // TODO make lower limit a constant
        if (distance < ballHitDetectionDistance)
        {
            AnnounceHit();
            lastShockTime = 0;
        }
    }
    if (lastShockTime > 0 && (currentTime - lastShockTime) > maxShotDurationMs)
    {
        Serial.printf("%4.3f: miss detected\n", millis() / 1000.0);
        AnnounceMiss();
        lastShockTime = 0;
    }
    
    // Serial.printf("%4.3f: ... completed shot detection\n", millis() / 1000.0);
}