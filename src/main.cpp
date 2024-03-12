#include <Arduino.h>
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
}
 
void loop() {
}