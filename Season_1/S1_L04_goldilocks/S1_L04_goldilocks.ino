#include <Servo.h>
// ---------------------------------------------------------------------------
// First we set up our wheels!
// ---------------------------------------------------------------------------
Servo leftServo;
#define leftServoPin 10
Servo rightServo;
#define rightServoPin 9

#define SERVOSTOP 90

#define LFFAST 180
#define LFSLOW 103
#define LBFAST 0
#define LBSLOW 80

#define RFFAST 0
#define RFSLOW 80
#define RBFAST 180
#define RBSLOW 103

// ---------------------------------------------------------------------------
// Ultrasonic Sensor
// ---------------------------------------------------------------------------
#include <NewPing.h>
#define TRIGGER_PIN 12
#define ECHO_PIN 11
#define MAX_DISTANCE 200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

// ---------------------------------------------------------------------------
// Behaviors
// ---------------------------------------------------------------------------
#define GOLDILOCKS_UPPER 30
#define GOLDILOCKS_LOWER 20

void setup() {
  Serial.begin(57600);
}

void loop() {
//  delay(150);
  int distance = sonar.ping_cm();
  Serial.print("Ping: ");
  Serial.print(distance);
  Serial.print("cm  ");
  if (distance < GOLDILOCKS_LOWER)
  {
    Serial.println("BACK UP!");
    leftServo.attach(leftServoPin);
    rightServo.attach(rightServoPin);
    leftServo.write(LBFAST);
    rightServo.write(RBFAST);
  }
  else if (distance > GOLDILOCKS_UPPER)
  {
    Serial.println("FORWARD!");
    leftServo.attach(leftServoPin);
    rightServo.attach(rightServoPin);
    leftServo.write(LFFAST);
    rightServo.write(RFFAST);
  }
  else
  {
    Serial.println("STOP");
    leftServo.write(SERVOSTOP);
    rightServo.write(SERVOSTOP);
    leftServo.detach();
    rightServo.detach();
  }
  delay(200);
}


