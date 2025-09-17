#include <ESP8266WiFi.h>

const char* ssid = "zzz";
const char* password = "12345678";

WiFiServer server(80);

// IR sensor pin
#define IR  D2  // connect your IR sensor output pin here

// Machine status
String message = "Available";
String color = "#33cc33";  // 
unsigned long startTime = 0;
bool inUse = false;
const unsigned long useDuration = 5000;  // 5 seconds

void setup() {
  pinMode(IR, INPUT);
  WiFi.softAP(ssid, password);
  server.begin();
}

void loop() {
  unsigned long currentTime = millis();

  // ✅ IR sensor trigger
  int irValue = digitalRead(IR);
  if (irValue == LOW && !inUse) {   // some IR sensors give LOW when triggered
    message = "In Use";
    color = "#cc3333";  // red
    startTime = currentTime;
    inUse = true;
    
  }

  // ✅ Timer check
  if (inUse && (currentTime - startTime >= useDuration)) {
    message = "Available";
    color = "#33cc33";  // greenn
    inUse = false;
    
  }

  // ✅ Handle web requests
  WiFiClient client = server.available();
  if (!client) return;
  while (!client.available()) delay(1);

  String request = client.readStringUntil('\r');
  client.flush();

  // ✅ Webpage
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();
  client.println("<!DOCTYPE html><html><head>");
  client.println("<meta name='viewport' content='width=device-width, initial-scale=1'>");
  client.println("<meta http-equiv='refresh' content='0.5'>");
  client.println("<title>Machine Status</title>");
  client.println("<style>");
  client.println("  body { font-family: 'Segoe UI', sans-serif; background: #f0f0f5; display: flex; flex-direction: column; justify-content: center; align-items: center; height: 100vh; margin: 0; }");
  client.println("  h1 { font-size: 28px; margin-bottom: 20px; }");
  client.println("  .status-box { padding: 30px 60px; font-size: 36px; font-weight: bold; color: white; background-color: " + color + "; border-radius: 15px; box-shadow: 0 4px 15px rgba(0,0,0,0.2); margin-bottom:20px; }");
  client.println("</style>");
  client.println("</head>");
  client.println("<body>");
  client.println("  <h1>WASHING MACHINE STATUS</h1>");
  client.println("  <div class='status-box'>" + message + "</div>");
  client.println("</body></html>");
}