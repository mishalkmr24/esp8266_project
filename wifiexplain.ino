
#include <ESP8266WiFi.h>  //it contain all the function like hotspot(AP) and STA

const char* ssid = "zzz";
const char* password = "12345678" ; // must have 8 character or num
    //means fixed cannot be change the variable
    //used for wifi

WiFiServer server(80); //creates a webserver that connect with browser
int led = D1;


void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT); 
  digitalWrite(led, LOW); //the state of the pin unknown maybe high or low    
                        // this force the led to remain LOW/off

  WiFi.SoftAP(ssid,password); //start the hotspot to connect with the psswrd
  server.begin(); //start the web server created just now
}


void loop() {


  WiFiClient client = server.available();   // Check whether anyone connect the server
  if (!client) return;     //if no one connect, do nothing 

  while(!client.available()) delay(1);      // Wait for the user to press and browser send data to esp
  String request = client.readStringUntil('\r');
  client.flush();     //get the main input and remove the rest

  // Check if request asks for LED ON
  if (request.indexOf("/LED=ON") != -1) {
    digitalWrite(ledPin, HIGH);   // Turn LED ON
  }
  // Check if request asks for LED OFF
  if (request.indexOf("/LED=OFF") != -1) {
    digitalWrite(ledPin, LOW);    // Turn LED OFF
  }




}
