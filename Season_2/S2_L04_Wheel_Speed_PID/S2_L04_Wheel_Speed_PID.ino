

#include <PID_v1.h>
// define PID variables
double setpointRight, inputRight, outputRight;

// tuning parameters
double Kp = 5, Ki = 1, Kd = 0;

// The PID objects
PID rightPID(&inputRight, &outputRight, &setpointRight, Kp, Ki, Kd, DIRECT);


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

#define MotR1     6
#define MotR2     9
#define MotL1     10
#define MotL2     11


void interruptWheelCounterLeft(){
  WheelCounterLeft++;
}

void interruptWheelCounterRight(){
  WheelCounterRight++;
  digitalWrite(13, !digitalRead(13));
}


void speedCallback(){
  rightPID.Compute();
  analogWrite(MotR1, outputRight);
  
  volatile int leftSpeed = WheelCounterLeft;
  volatile int rightSpeed = WheelCounterRight;
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

  pinMode(13, OUTPUT);

  setpointRight = 3;
  rightPID.SetMode(AUTOMATIC);
  digitalWrite(MotR2, HIGH);  // get the motor started so we have something to work with.
}



void loop() {
  runner.execute();
}
