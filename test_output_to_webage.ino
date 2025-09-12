#include <ESP8266WiFi.h>

// Hotspot credentials
const char* ssid = "zzz";
const char* password = "12345678";

WiFiServer server(80);

// ESP8266 built-in button pin (FLASH button on NodeMCU is GPIO0 = D3)
const int BUTTON_PIN = D3;

void setup() {
  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT_PULLUP); 
  // Button is usually "active LOW" → pressed = 0, released = 1

  // Start Wi-Fi in AP mode
  WiFi.softAP(ssid, password);
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client) return;

  while (!client.available()) {
    delay(1);
  }

  String request = client.readStringUntil('\r');
  client.flush();

  // Read button state
  int buttonState = digitalRead(BUTTON_PIN);
  String message;
  if (buttonState == LOW) {
    message = "Button Pressed!";
  } else {
    message = "Button Released!";
  }

  // Send HTML response
  //client.println("HTTP/1.1 200 OK");
  //client.println("Content-Type: text/html");
  //client.println("Connection: close");
  //client.println();
  //client.println("<!DOCTYPE HTML>");
  //client.println("<html>");
 // client.println("<head><title>ESP8266 Button Test</title></head>");
 // client.println("<meta http-equiv='refresh' content='0.5'>"); 
  //client.println("</head>");
  //client.println("<body style='font-family: Arial; text-align:center;'>");
 // client.println("<h1>ESP8266 Button Status</h1>");
 // client.println("<h2>Status: " + message + "</h2>");
 // client.println("</body></html>");
}



