
#define _TASK_TIMECRITICAL
#define _TASK_SLEEP_ON_IDLE_RUN
#include <TaskScheduler.h>
// Callback methods prototypes
void speedCallback();
#define speedInterval 1000

//Tasks
Task speedCheck(speedInterval, -1, &speedCallback);

Scheduler runner;


int interruptPinLeft = 2;
int interruptPinRight = 3;
volatile int WheelCounterLeft, WheelCounterRight = 0;
int LED = 13;

#define MotR1     9
#define MotR2     10
#define MotL1     11
#define MotL2     12


void interruptWheelCounterLeft(){
  WheelCounterLeft++;
}

void interruptWheelCounterRight(){
  WheelCounterRight++;
}


void speedCallback(){
  int leftSpeed = WheelCounterLeft;
  int rightSpeed = WheelCounterRight;
  WheelCounterLeft = 0;
  WheelCounterRight = 0;
  Serial.print("L= ");
  Serial.print(leftSpeed);
  Serial.print("  :  ");
  Serial.print("R= ");
  Serial.println(rightSpeed);
}

void setup() {
  Serial.begin(57600);
  runner.init();
  runner.addTask(speedCheck);
  speedCheck.enable();
  
  // put your setup code here, to run once:
  pinMode (interruptPinLeft, INPUT);
  pinMode (interruptPinRight, INPUT);
  attachInterrupt(0, interruptWheelCounterLeft, RISING);
  attachInterrupt(1, interruptWheelCounterRight, RISING);
  pinMode(MotR1, OUTPUT);
  pinMode(MotR2, OUTPUT);
  pinMode(MotL1, OUTPUT);
  pinMode(MotL2, OUTPUT);
}



void loop() {
  runner.execute();
  digitalWrite(MotR1, HIGH);

//  digitalWrite(MotL1, HIGH);
 
}
