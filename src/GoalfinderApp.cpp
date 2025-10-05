#include <GoalfinderApp.h>
#include <HardwareSerial.h>
#include <Settings.h>

// Konstante Pins für Peripherie
const int GoalfinderApp::pinTofSda = 22;
const int GoalfinderApp::pinTofScl = 21;
const int GoalfinderApp::pinI2sBclk = 23;
const int GoalfinderApp::pinI2sWclk = 5;
const int GoalfinderApp::pinI2sDataOut = 19;
const int GoalfinderApp::pinLedPwm = 17;
const int GoalfinderApp::pinRandomSeed = 36;

const int GoalfinderApp::ledPwmChannel = 0;

const int GoalfinderApp::ballHitDetectionDistance = 500;
const int GoalfinderApp::shotVibrationThreshold = 4000;
const int GoalfinderApp::maxShotDurationMs = 5000;

const char* GoalfinderApp::waitingClip = "/waiting.mp3";

const char* GoalfinderApp::hitClips[] = { "/hit-1.mp3" };
const int   GoalfinderApp::hitClipsCnt = sizeof(GoalfinderApp::hitClips) / sizeof(GoalfinderApp::hitClips[0]);

const char* GoalfinderApp::tickClips[] = { "/tick-1.mp3" };
const int   GoalfinderApp::tickClipsCnt = sizeof(GoalfinderApp::tickClips) / sizeof(GoalfinderApp::tickClips[0]);

const char* GoalfinderApp::missClips[] = { "/miss-1.mp3" };
const int   GoalfinderApp::missClipsCnt = sizeof(GoalfinderApp::missClips) / sizeof(GoalfinderApp::missClips[0]);

TaskHandle_t Task1;
TaskHandle_t Task2;
TaskHandle_t Task3;

SemaphoreHandle_t xMutex;

void Task1code(void *pvParameters);
void Task2code(void *pvParameters);
void Task3code(void *pvParameters);

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

void GoalfinderApp::SetIsSoundEnabled(bool value)
{
    this->isSoundEnabled = value;
}

bool GoalfinderApp::IsSoundEnabled()
{
    return this->isSoundEnabled;
}

GoalfinderApp::~GoalfinderApp() 
{
}

void GoalfinderApp::Init() 
{
    delay(100);
    Serial.begin(115200);
    randomSeed(analogRead(pinRandomSeed));

    if (!fileSystem.Begin()) 
    {
        Serial.println("FS initialization failed");
        return;
    } 
    Serial.println("FS initialized");

    Settings* settings = Settings::GetInstance();
    String ssid = settings->GetDeviceName();
    String wifiPw = settings->GetDevicePassword();

    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, wifiPw);
    WiFi.setSleep(false);
    Serial.println(WiFi.softAPIP());

    webServer.Begin();
    
    sntp.Init();
    vibrationSensor.Init();
    tofSensor.Init(pinTofScl, pinTofSda);

    ledController.SetMode(LedMode::Flash);

    UpdateSettings(true);

    xTaskCreatePinnedToCore(Task1code, "Task1", 8192, NULL, 1, &Task1, 0);
    delay(500);

    xTaskCreatePinnedToCore(Task2code, "Task2", 8192, NULL, 1, &Task2, 1);
    delay(500);

    xTaskCreatePinnedToCore(Task3code, "Task3", 8192, NULL, 2, &Task3, 1);
    delay(500);
}


void GoalfinderApp::UpdateSettings(bool force) {
    Settings* settings = Settings::GetInstance();
    if (force || settings->IsModified()) {
        audioPlayer.SetVolume(settings->GetVolume());
        ledController.SetMode(settings->GetLedMode());
        vibrationSensor.SetSensitivity(settings->GetVibrationSensorSensitivity());
        // TODO: Add metronome interval in milliseconds
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
       Serial.println("Metronome");
    }
}

void GoalfinderApp::OnShotDetected() {
    announcement = Announcement::Shot;
    Serial.printf("%4.3f: announce shot: %d\n", millis() / 1000.0, announcement);
}

void GoalfinderApp::AnnounceHit() {
    announcement = Announcement::Hit;
}

void GoalfinderApp::AnnounceMiss() {
    announcement = Announcement::Miss;
}

void GoalfinderApp::ProcessAnnouncement() {
    Serial.println("Announce Process");
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
        Serial.printf("%4.3f: starting playback of: '%s'\n", millis() / 1000.0, soundFileName);
        audioPlayer.PlayMP3(soundFileName);
    }
}

void GoalfinderApp::DetectShot() {
    Serial.println("Detecting Shot");
    if (lastShockTime == 0) {
        {
            long vibration = 0;
            //Serial.printf("Vibration: %d\n", vibration);
            if (vibration > 0) {
                lastShockTime = millis();
                Serial.printf("Last shock time: %d\n", lastShockTime);
                Serial.printf("%4.3f: shot detected\n", millis() / 1000.0);
            }
        }
    }
        unsigned long currentTime = millis();
   
        int distance = tofSensor.ReadSingleMillimeters();
        Serial.printf("Distance: %d\n", distance);
        if(distance > 20 && distance < ballHitDetectionDistance) {
            AnnounceHit();
            lastShockTime = 0;
        }
}

void GoalfinderApp::Process()
{
    UpdateSettings();
}

void Task1code(void *pvParameters) {
    Serial.printf("Task1 running on core %d\n", xPortGetCoreID());

    GoalfinderApp* app = GoalfinderApp::GetInstance();
    if (!app) {
        Serial.println("GoalfinderApp instance is NULL");
        vTaskDelete(NULL);
        return;
    }

    for (;;) {
        app->audioPlayer.Loop();
        if (!app->audioPlayer.IsPlaying()) {
            app->TickMetronome();
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

/**/
void Task2code(void *pvParameters) {
    Serial.printf("Task2 running on core %d\n", xPortGetCoreID());

    GoalfinderApp* app = GoalfinderApp::GetInstance();
    if (!app) {
        Serial.println("GoalfinderApp instance is NULL");
        vTaskDelete(NULL);
        return;
    }

    for (;;) {
        app->DetectShot();
        app->ProcessAnnouncement();
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void Task3code(void *pvParameters) {
    Serial.printf("Task3 running on core %d\n", xPortGetCoreID());

    GoalfinderApp* app = GoalfinderApp::GetInstance();
    if (!app) {
        Serial.println("GoalfinderApp instance is NULL");
        vTaskDelete(NULL);
        return;
    }

    for (;;) {
        app->ledController.Loop();
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}
