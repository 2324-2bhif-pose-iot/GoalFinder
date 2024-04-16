#include "GoalfinderApp.h"
#include <Arduino.h>
#include <ToFSensor.h>
#include <VibrationSensor.h>
#include <BluetoothManager.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b" // Beispiel-Service UUID
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8" // Beispiel-Charakteristik UUID

ToFSensor tofSensor;
VibrationSensor vibrationSensor;
BluetoothManager bluetoothManager;

BLEServer *pServer;
BLECharacteristic *pCharacteristic;
bool deviceConnected = false;
bool oldDeviceConnected = false;

class MyServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

GoalfinderApp::GoalfinderApp() :
    Singleton<GoalfinderApp>() {
}

GoalfinderApp::~GoalfinderApp() {
}

void GoalfinderApp::Init() 
{
    Serial.begin(115200);
    vibrationSensor.Init();
    tofSensor.Init();
    bluetoothManager.Init();

    
  BLEDevice::init("ESP32 BLE Server"); // Name des BLE-Geräts
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setValue("Hello World");
  pCharacteristic->setCallbacks(new BLECharacteristicCallbacks());

  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
    
}

void GoalfinderApp::Process() {
    Serial.print("Distance (mm): ");
    Serial.println(tofSensor.ReadSingleMillimeters());
    delay(500);

    Serial.print("Vibration Measurement: ");
    Serial.println(vibrationSensor.Vibration());
    delay(500);

   if (deviceConnected) {
    // Hier können Sie Code hinzufügen, der ausgeführt wird, wenn ein Gerät verbunden ist
    if(pCharacteristic->getValue().c_str() != "Hello World") {
      pCharacteristic->setValue("Hello World"); // Daten aktualisieren
      pCharacteristic->notify(); // Daten senden
    }
  }

  // Überprüfen, ob eine Verbindung getrennt wurde
  if (!deviceConnected && oldDeviceConnected) {
    delay(500); // Geben Sie dem Bluetooth-Stack Zeit, die Verbindung abzuschließen
    pServer->startAdvertising(); // Starten Sie das Werben erneut
    Serial.println("Starte wieder zu werben");
    oldDeviceConnected = deviceConnected;
  }
  // Speichern Sie den aktuellen Status der Verbindung für den nächsten Schleifendurchlauf
  oldDeviceConnected = deviceConnected;
  delay(10);    
}