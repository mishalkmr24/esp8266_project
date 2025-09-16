
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
                        
  WiFi.softAP(ssid,password); //start the hotspot to connect with the psswrd
  server.begin(); //start the web server created just now
}


void loop() {  //has to be many time like changing time to time


  WiFiClient client = server.available();   // Check whether anyone connect the server
  if (!client) return;     //if no one connect, do nothing 

  while(!client.available()) delay(1);      // Wait for the user to press and browser send data to esp
  String request = client.readStringUntil('\r');
  client.flush();     //get the main input and remove the rest
 
 
  int sensorValue = digitalRead(IR); //read the sensor data//whether detect anything or not/
  

  String message;
  String color;


  if (sensorValue == LOW) {   //there is object detected
    message = "IN USE";
    color ="red";
  } else {                    //no object detected
    message = "AVAILABLE";
    color ="green";
}

 client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("Connection: close");
client.println();
client.println("<!DOCTYPE html>");
client.println("<html>");
client.println("<head>");
client.println("<meta name='viewport' content='width=device-width, initial-scale=1'>");
client.println("<meta http-equiv='refresh' content='0.5'>");  // refresh every 1 second
client.println("<title>Machine Status</title>");
client.println("<style>");
client.println("  body { font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; background: #f0f0f5; color: #333; display: flex; flex-direction: column; justify-content: center; align-items: center; height: 100vh; margin: 0; }");
client.println("  h1 { font-size: 28px; margin-bottom: 20px; }");
client.println("  .status-box {");
client.println("    padding: 30px 60px;");
client.println("    font-size: 36px;");
client.println("    font-weight: bold;");
client.println("    color: white;");
client.println("    background-color: " + color + ";");  // dynamic color (red/green etc)
client.println("    border-radius: 15px;");
client.println("    box-shadow: 0 4px 15px rgba(0,0,0,0.2);");
client.println("    user-select: none;");
client.println("    transition: background-color 0.3s ease;");
client.println("  }");
client.println("</style>");
client.println("</head>");
client.println("<body>");
client.println("  <h1>Washing Machine Status</h1>");
client.println("  <div class='status-box'>" + message + "</div>");
client.println("</body>");
client.println("</html>");
}


 //client.println("HTTP/1.1 200 OK");
  //client.println("Content-Type: text/html");
  //client.println("Connection: close");
  //client.println();
  //client.println("<!DOCTYPE HTML>");
  //client.println("<html>");
  //client.println("<head><title>ESP8266 IR</title></head>");
  //client.println("<meta http-equiv='refresh' content='0.5'>"); 
  //client.println("</head>");
  //client.println("<body style='font-family: Arial; text-align:center;'>");
  //client.println("<h1>WASHING MACHINE STATUS</h1>");
  //client.println("<h2>STATUS: " + message + "</h2>");
  //client.println("</body></html>");
