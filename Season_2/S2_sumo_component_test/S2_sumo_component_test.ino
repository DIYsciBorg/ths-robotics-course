/*  Sumo bot testing  
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

// ---------------------------------------------------------------------------
// H-Bridge
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
// Task Scheduling
// ---------------------------------------------------------------------------
#include <TaskScheduler.h>
// Callback methods prototypes
void t1Callback();
void t2Callback();
//void t3Callback();
void t4Callback();
//Tasks

Task t1(500, TASK_FOREVER, &t1Callback);
Task t2(5000, TASK_FOREVER, &t2Callback);
//Task t3(5000, TASK_FOREVER, &t3Callback);
Task t4(200, TASK_FOREVER, &t4Callback);
Scheduler runner;

void t1Callback() {
  distance = sonar.ping_cm();
}

void t2Callback() {
  if (LeftDIR == 0){
      digitalWrite(MotL2, HIGH);
    } else{digitalWrite(MotL2, LOW); }
    if (RightDIR == 0){
      digitalWrite(MotR2, HIGH);
    } else{digitalWrite(MotR2, LOW); }
  analogWrite(MotL1, 255);
  analogWrite(MotR1, 255);
}

void t3Callback() {
}

void t4Callback() {
  distance = sonar.ping_cm();
  int temp = digitalRead(LeftSensor);
  Serial.print(temp);
  Serial.print(" ");
  temp = digitalRead(RightSensor);
  Serial.print(temp);
  Serial.print(" ");  
  Serial.print(distance);
  Serial.println(" cm");
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LeftSensor, INPUT);
  pinMode(RightSensor, INPUT);
  irrecv.enableIRIn(); // Start the receiver
  runner.init();
  runner.addTask(t1);
//  runner.addTask(t2);
//  runner.addTask(t3);
  runner.addTask(t4);
  t1.enable();
  t2.enable();
//  t3.enable();
  t4.enable();

  pinMode(MotR1, OUTPUT); // prepare all the H-bridge pins
  pinMode(MotR2, OUTPUT);
  pinMode(MotL1, OUTPUT);
  pinMode(MotL2, OUTPUT);

  Serial.begin(115200);

 
// Finish up the Setup routine by waiting for the Start Match signal
  do {
    if (irrecv.decode(&results)) {
      if (results.value = STARTCODE) {
        loop();
      }
    }
  } while (results.value != STARTCODE);  // loop until the result matches the start signal
}

void loop() {
  // put your main code here, to run repeatedly:
  runner.execute();
   digitalWrite(MotL1, HIGH);
  digitalWrite(MotR1, HIGH);
  analogWrite(MotL2, 100);
  analogWrite(MotR2, 100);

}
