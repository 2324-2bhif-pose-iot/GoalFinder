#include <Arduino.h>
<<<<<<< HEAD
#include <WiFi.h>

const char* ssid = "goalfinder";
const char* password = "esp32123";

void setup() {
  // put your setup code here, to run once:
   // Serial port for debugging purposes
  Serial.begin(115200);
  Serial.println();
  
  // Setting the ESP as an access point
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);
=======
#include "WiFi.h"

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    digitalWrite(LED_BUILTIN, HIGH);
>>>>>>> dc15dfc81bd1455fa956215775063fc836a72be8
}
 
void loop() {
<<<<<<< HEAD
=======
  
>>>>>>> dc15dfc81bd1455fa956215775063fc836a72be8
}