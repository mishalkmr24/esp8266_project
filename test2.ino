#include <ESP8266WiFi.h>

const char* ssid = "zzz";     // Wi-Fi hotspot name
const char* password = "12345678";   // Wi-Fi hotspot password

WiFiServer server(80);

const int IR_PIN = D2;                   //#define IR_PIN D2   // IR sensor connected to D2

void setup() {
  pinMode(IR_PIN, INPUT);

  // Start Wi-Fi in Access Point mode
  WiFi.softAP(ssid, password);

  // Start server
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client) return;

  // Wait until client sends data
  while (!client.available()) {
    delay(1);
  }

  String request = client.readStringUntil('\r');
  client.flush();

  // Read IR sensor
  int sensorValue = digitalRead(IR_PIN);
  String message;
  if (sensorValue == LOW) {
    message = "Object Detected!";
  } else {
    message = "No Object.";
  }

  // Send webpage
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head><title>ESP8266 IR Sensor</title></head>");
  client.println("<body style='font-family: Arial; text-align: center;'>");
  client.println("<h1>ESP8266 IR Sensor</h1>");
  client.println("<h2>Status: " + message + "</h2>");
  client.println("</body></html>");
}