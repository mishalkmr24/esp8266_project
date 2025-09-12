#include <ESP8266WiFi.h>  //it contain all the function like hotspot(AP) and STA

const char* ssid = "zzz";
const char* password = "12345678" ; // must have 8 character or num
    //means fixed cannot be change the variable
    //used for wifi

WiFiServer server(80); //creates a webserver that connect with browser

const int IR = D2; //the pin connection
                   //define//

void setup() {    //any act that work one time
                  // put your setup code here, to run once:
  
  pinMode(IR, INPUT);     //the state of the pin unknown maybe high or low    
                        
  WiFi.SoftAP(ssid,password); //start the hotspot to connect with the psswrd
  server.begin(); //start the web server created just now
}


void loop() {  //has to be many time like changing time to time


  WiFiClient client = server.available();   // Check whether anyone connect the server
  if (!client) return;     //if no one connect, do nothing 

  while(!client.available()) delay(1);      // Wait for the user to press and browser send data to esp
  String request = client.readStringUntil('\r');
  client.flush();     //get the main input and remove the rest
 
 
  int sensorValue = digitalRead(IR_PIN); //read the sensor data//whether detect anything or not/
  

  String message;
  if (sensorValue == LOW) {   //there is object detected
    message = "IN USE";
  } else {                    //no object detected
    message = "AVAILABLE";
  }
  
  
  








}
