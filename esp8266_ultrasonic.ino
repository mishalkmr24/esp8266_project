
#define TRIG D5  // GPIO14
#define ECHO D6  // GPIO12

long duration;
int distance;

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop() {
  // Clear the trigger
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  // Send a 10us HIGH pulse
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  // Measure the echo pulse
  duration = pulseIn(ECHO, HIGH);

  // Convert to centimeters
  distance = duration * 0.0343 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(500);
}