// ---------------------------------------------------------------------------
// Ultrasonic Sensor
// ---------------------------------------------------------------------------
#include <NewPing.h>
#define TRIGGER_PIN 7
#define ECHO_PIN 6
#define MAX_DISTANCE 200
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
int distance = 0;

// ---------------------------------------------------------------------------
// Line sensors
// ---------------------------------------------------------------------------
#define LeftSensor      3
#define RightSensor     2

void setup() {
  // put your setup code here, to run once:
  pinMode(LeftSensor, INPUT);
  pinMode(RightSensor, INPUT);
  Serial.begin(115200);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  // int distance = sonar.ping_cm();
  int temp = digitalRead(LeftSensor);
  Serial.print(temp);
  Serial.print(" ");
  temp = digitalRead(RightSensor);
  Serial.print(temp);
  Serial.print(" ");
  Serial.println(sonar.ping_cm());
  delay(500);
}
