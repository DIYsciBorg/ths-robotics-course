/*  Sumo bot
 *   Emery Premeaux
 *   THS Robotics Course season 2
 *   
 *   You need to disable the TIMER_ENABLE in the NewPing.h file as per:
 *   https://bitbucket.org/teckel12/arduino-new-ping/wiki/Multiple%20Definition%20of%20%22__vector_7%22%20Error
 *   
 */
  
// ---------------------------------------------------------------------------
// IR Remote receiver for Starting the match
// ---------------------------------------------------------------------------
#include <IRremote.h>
#define RECV_PIN  4
IRrecv irrecv(RECV_PIN);
decode_results results;
#define STARTCODE 16757325

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
int LeftSensorState = 0;
int RightSensorState = 0;

// ---------------------------------------------------------------------------
// H-Bridge Setup
// ---------------------------------------------------------------------------
#define MotR1     9
#define MotR2     10
#define MotL1     11
#define MotL2     12

int LeftPWM = 0;
int RightPWM = 0;  // analogWrite takes value 0 to 255
boolean LeftDIR = 0;    // rotate opposite directions(?)
boolean RightDIR = 0;

// ---------------------------------------------------------------------------
// Setup 
// ---------------------------------------------------------------------------
void setup() {
  // put your setup code here, to run once:
  pinMode(LeftSensor, INPUT);
  pinMode(RightSensor, INPUT);
  irrecv.enableIRIn(); // Start the receiver

  pinMode(MotR1, OUTPUT); // prepare all the H-bridge pins
  pinMode(MotR2, OUTPUT);
  pinMode(MotL1, OUTPUT);
  pinMode(MotL2, OUTPUT);

  Serial.begin(115200);
  Serial.println("Waiting for start...");

 
// Finish up the Setup routine by waiting for the Start Match signal
  do {
    if (irrecv.decode(&results)) {
      if (results.value = STARTCODE) {
          Serial.println("GO!");
        loop();
      }
    }
  } while (results.value != STARTCODE);  // loop until the result matches the start signal
}

// ---------------------------------------------------------------------------
// Main loop
// ---------------------------------------------------------------------------
void loop() {
  LeftSensorState = digitalRead(LeftSensor);
  RightSensorState = digitalRead(RightSensor);
  distance = sonar.ping_cm();
  
  Serial.print(LeftSensorState);
  Serial.print(" ");
  Serial.print(RightSensorState);
  Serial.print(" ");
  Serial.print(distance);
  Serial.print(" ");
  
 
  // Edge Left Detect
  if (LeftSensorState == 0) {
    Serial.println("Edge Detect LEFT");
    LeftMotor(1);
    RightMotor(-1);
    delay(500);
  }
  

  // Edge Right Detect
  if (RightSensorState == 0) {
    Serial.println("Edge Detect RIGHT");
    LeftMotor(-1);
    RightMotor(1);
    delay(500);
  }

  // Seek pattern rotate left
  if (distance > 60) {
    Serial.println("I cant find it!");
    LeftMotor(1);
    RightMotor(-1);
    delay(500);
  }

  // Charge!
  if (distance < 60) {
    Serial.println("Charge!");
    LeftMotor(1);
    RightMotor(1);
  }
  delay(100);
}

// ---------------------------------------------------------------------------
// Motor Commands
// ---------------------------------------------------------------------------
void LeftMotor(char command){
  switch (command) {
    case 1:{
      // set forward motor
      digitalWrite(MotL1, HIGH);
      digitalWrite(MotL2, LOW);
      break;}
    case -1:{
      // set reverse
      digitalWrite(MotL1, LOW);
      digitalWrite(MotL2, HIGH);
      break;}
    case 0:{
      // set stop
      digitalWrite(MotL1, LOW);
      digitalWrite(MotL2, LOW);
      break;}
  }
}

void RightMotor(int command){
  switch (command) {
    case 1:{
      // set forward motor
      digitalWrite(MotR1, LOW);
      digitalWrite(MotR2, HIGH);
      break;}
    case -1:{
      // set reverse
      digitalWrite(MotR1, HIGH);
      digitalWrite(MotR2, LOW);
      break;}
    case 0:{
      // set stop
      digitalWrite(MotR1, LOW);
      digitalWrite(MotR2, LOW);
      break;}
  }
}

