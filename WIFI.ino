
#include <ESP8266WiFi.h>

const char* ssid = "zzz";     // Name of WiFi network
const char* password = "12345678";   // At least 8 characters

void setup() {
  Serial.begin(115200);
  delay(100);

  // Start WiFi Access Point
  WiFi.softAP(ssid, password);  //ACCESS POINT(OWN HOTSPOT)

}

void loop() {
  // Nothing needed here
}