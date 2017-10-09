/***************************************
 * THS Robotics Course
 * Season 2, Lesson 3 : Bumpers using interrupts
 * Emery Premeaux
 * 
 * Arduino UNO has 2 hardware interrupts, they are:
 *    Digital pin 2 = Interrupt 0
 *    Digital pin 3 = Interrupt 1
 *    
 *    To control WHEN interrupts are allowed, refer to https://www.arduino.cc/en/Reference/Interrupts
 *    To attach and configure hardware interrupts, refer to https://www.arduino.cc/en/Reference/Interrupts
 ***************************************/

int interruptPinLeft = 2;
int interruptPinRight = 3;
int LED = 13;

volatile byte bumperLeftState = LOW;
volatile byte bumperRightState = LOW;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode (LED, OUTPUT);
  
  pinMode (interruptPinLeft, INPUT_PULLUP);
  pinMode (interruptPinRight, INPUT_PULLUP);
  attachInterrupt(0, interruptBumperLeft, FALLING);
  attachInterrupt(1, interruptBumperRight, FALLING);
}

void interruptBumperLeft() {
  bumperLeftState = HIGH;
}

void interruptBumperRight() {
  bumperRightState = HIGH;
}

void loop() {
  digitalWrite(LED, LOW);

  if(bumperLeftState == HIGH){
    digitalWrite(LED, HIGH);
    Serial.println("LEFT BUMPER HIT!");
    bumperLeftState = LOW;
  }

  if(bumperRightState == HIGH){
    digitalWrite(LED, HIGH);
    Serial.println("RIGHT BUMPER HIT!");
    bumperRightState = LOW;
  }
  delay(500);
}
