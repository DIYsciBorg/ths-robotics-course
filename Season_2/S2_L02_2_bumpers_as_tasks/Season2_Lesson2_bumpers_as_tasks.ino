/***************************************
 * THS Robotics Course
 * Season 2, Lesson 2 : Bumpers as Tasks
 * Emery Premeaux
 * 
 * This recreates the interrupts version of the bumper check code.
 * However, since we are not using hardware interrupts, we must choose a minumum check period.
 * Twice per second seems acceptable response time.
 * Also, since we do not have the advantages of hardware interrupts (such as RISING and FALLING)
 * we have some additional overhead in semaphores to pass back and forth between tasks.
 * 
 * Your homework will be to improve this code, to make it act more like the interrupt example.
 * 
 * WARNING!
 * We have to move the Bumpers from pins 2&3 to pins 4&5 because in the future, we will use
 * hardware interrupts for something that needs a higher speed checking. (Hardware interrupts
 * are valuable! We only have 2.)
 ***************************************/ 
#include <TaskScheduler.h>

// Callback methods prototypes
void tBumpCheck();

//Tasks
Task tBump(500, TASK_FOREVER, &tBumpCheck);
Task tSerialPrint(500, TASK_FOREVER, &tPrintMessages);

Scheduler runner;

// Other Includes

// Hardware & Constants
#define LeftBumpPin 5
#define RightBumpPin 4
#define LED 13

// Variables
volatile byte bumperLeftState = LOW;
volatile byte bumperRightState = LOW;

void tBumpCheck(){
  if (digitalRead(LeftBumpPin) == HIGH){
    bumperLeftState = HIGH;
  }else{
    bumperLeftState = LOW;
  }
  if (digitalRead(RightBumpPin) == HIGH){
    bumperRightState = HIGH;
  }else{
    bumperRightState = LOW;
  }
}

void tPrintMessages(){
  if (bumperLeftState == HIGH){
    Serial.println("Left Bumper!");
  }
  if (bumperRightState == HIGH){
    Serial.println("Right Bumper!");
  }
}

void setup () {
  pinMode (LED, OUTPUT);
  pinMode (LeftBumpPin, INPUT);
  pinMode (RightBumpPin, INPUT);
  
  Serial.begin(9600);
  Serial.println("Robot Baby Buggy Bumpers!");
  
  runner.init();
  Serial.println("Initialized scheduler");
  
  runner.addTask(tBump);
  Serial.println("Added Bumper Check task");
  
  tBump.enable();
  Serial.println("Enabled Bumper Check task");

  runner.addTask(tSerialPrint);
  Serial.println("Added the bump check and print serial task");

  tSerialPrint.enable();
  Serial.println("Enabled the bump check and print serial task. Press a bumper.");
}


void loop () {
  runner.execute();
}
