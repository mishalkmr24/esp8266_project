
#include  <SoftwareSerial.h>

SoftwareSerial BTSerial(1,0);
int ENB = 10;
int IN3 = 4;
int IN4 = 2;
int ENA = 9;
int IN1 = 8;
int IN2 = 7;




void setup() {
  // put your setup code here, to run once:
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN1, OUTPUT);
  BTSerial.begin(9600);
}

void loop() {
 
  if (BTSerial.available()) {
    char c = BTSerial.read();

    if (c == '1') {
      digitalWrite(IN3,HIGH);
      digitalWrite(IN4,LOW);
      digitalWrite(IN2,HIGH);
      digitalWrite(IN1,LOW);
      analogWrite(ENB,255);
      analogWrite(ENA,255);
      BTSerial.println("ON");
    }
    
    else if (c == '0') {
       
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, LOW);
       digitalWrite(IN2, LOW);
       digitalWrite(IN1, LOW);
       BTSerial.println("OFF");
     }
  }

}
