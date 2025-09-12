#include <ESP8266WiFi.h>

const char* ssid = "zzz";      // Wi-Fi hotspot name
const char* password = "12345678";     // Password (at least 8 chars)

WiFiServer server(80);   // Web server on port 80
const int ledPin = D1;   // LED connected to D1 (GPIO5)

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Start LED OFF

  WiFi.softAP(ssid, password);
  // Start web server
  server.begin();
}

void loop() {


WiFiClient client = server.available();   // Check for incoming clients
  if (!client) return;

  while(!client.available()) delay(1);      // Wait for client data
  String request = client.readStringUntil('\r');
  client.flush();

  // Check if request asks for LED ON
  if (request.indexOf("/LED=ON") != -1) {
    digitalWrite(ledPin, HIGH);   // Turn LED ON
  }
  // Check if request asks for LED OFF
  if (request.indexOf("/LED=OFF") != -1) {
    digitalWrite(ledPin, LOW);    // Turn LED OFF
  }


  // Send webpage (GUI)
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println();
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<h1>ESP8266 LED Control</h1>");
  client.println("<p><a href=\"/LED=ON\"><button>ON</button></a></p>");
  client.println("<p><a href=\"/LED=OFF\"><button>OFF</button></a></p>");
  client.println("</html>");
}