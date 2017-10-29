#include <PID_v1.h>
#include <PID_AutoTune_v0.h>

byte ATuneModeRemember=2;
double input, output, setpoint=4;
double kp = 2 ,ki = 2,kd = 2;        // 2, 0.5, 2

double kpmodel=1.5, taup=100, theta[50];
double outputStart=5;
double aTuneStep=50, aTuneNoise=1, aTuneStartValue=100;
unsigned int aTuneLookBack=20;

boolean tuning = true;
unsigned long  modelTime, serialTime;

PID myPID(&input, &output, &setpoint,kp,ki,kd, DIRECT);
PID_ATune aTune(&input, &output);

//set to false to connect to the real world
boolean useSimulation = false;



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
  input = WheelCounterRight;
  Serial.print("R= ");
  Serial.println(WheelCounterRight);
   WheelCounterLeft = 0;
  WheelCounterRight = 0;
}


void setup()
{
   pinMode (interruptPinLeft, INPUT);
  pinMode (interruptPinRight, INPUT);
  attachInterrupt(0, interruptWheelCounterLeft, RISING);
  attachInterrupt(1, interruptWheelCounterRight, RISING);
  pinMode(MotR1, OUTPUT);
  pinMode(MotR2, OUTPUT);
  pinMode(MotL1, OUTPUT);
  pinMode(MotL2, OUTPUT);

  pinMode(13, OUTPUT);

  if(useSimulation)
  {
    for(byte i=0;i<50;i++)
    {
      theta[i]=outputStart;
    }
    modelTime = 0;
  }
  //Setup the pid 
  myPID.SetMode(AUTOMATIC);

  if(tuning)
  {
    tuning=false;
    changeAutoTune();
    tuning=true;
  }
  
  serialTime = 0;
  Serial.begin(57600);
   runner.init();
  runner.addTask(speedCheck);
  speedCheck.enable();
  digitalWrite(MotR2, HIGH);  // get the motor started so we have something to work with.

}

void loop()
{
  runner.execute();
  unsigned long now = millis();

  
  if(tuning)
  {
    byte val = (aTune.Runtime());
    if (val!=0)
    {
      tuning = false;
    }
    if(!tuning)
    { //we're done, set the tuning parameters
      kp = aTune.GetKp();
      ki = aTune.GetKi();
      kd = aTune.GetKd();
      myPID.SetTunings(kp,ki,kd);
      AutoTuneHelper(false);
    }
  }
  else myPID.Compute();
  
  if(useSimulation)
  {
    theta[30]=output;
    if(now>=modelTime)
    {
      modelTime +=100; 
      DoModel();
    }
  }
  else
  {
     analogWrite(MotR2,output); 
  }
  
  //send-receive with processing if it's time
  if(millis()>serialTime)
  {
    SerialReceive();
    SerialSend();
    serialTime+=500;
  }
}

void changeAutoTune()
{
 if(!tuning)
  {
    //Set the output to the desired starting frequency.
    output=aTuneStartValue;
    aTune.SetNoiseBand(aTuneNoise);
    aTune.SetOutputStep(aTuneStep);
    aTune.SetLookbackSec((int)aTuneLookBack);
    AutoTuneHelper(true);
    tuning = true;
  }
  else
  { //cancel autotune
    aTune.Cancel();
    tuning = false;
    AutoTuneHelper(false);
  }
}

void AutoTuneHelper(boolean start)
{
  if(start)
    ATuneModeRemember = myPID.GetMode();
  else
    myPID.SetMode(ATuneModeRemember);
}


void SerialSend()
{
  Serial.print("setpoint: ");Serial.print(setpoint); Serial.print(" ");
  Serial.print("input: ");Serial.print(input); Serial.print(" ");
  Serial.print("output: ");Serial.print(output); Serial.print(" ");
  if(tuning){
    Serial.println("tuning mode");
  } else {
    Serial.print("kp: ");Serial.print(myPID.GetKp());Serial.print(" ");
    Serial.print("ki: ");Serial.print(myPID.GetKi());Serial.print(" ");
    Serial.print("kd: ");Serial.print(myPID.GetKd());Serial.println();
  }
}

void SerialReceive()
{
  if(Serial.available())
  {
   char b = Serial.read(); 
   Serial.flush(); 
   if((b=='1' && !tuning) || (b!='1' && tuning))changeAutoTune();
  }
}

void DoModel()
{
  //cycle the dead time
  for(byte i=0;i<49;i++)
  {
    theta[i] = theta[i+1];
  }
  //compute the input
  input = (kpmodel / taup) *(theta[0]-outputStart) + input*(1-1/taup) + ((float)random(-10,10))/100;

}
