/* TokyoHackerSpace Robotics Course
 *  By Emery Premeaux
 *  Season 2, Lesson 4
 *  Line sensor demo - as digital inputs
 */
 
// using the analog inputs as digital
const int lineLeft = 14;
const int lineCenter = 15;
const int lineRight = 16;

const int ledPin = 13;

// variables to hold states of the sensors
int lineLeftState = 0;
int lineCenterState = 0;
int lineRightState = 0;



void setup() {
  //setup our pins
  pinMode(lineLeft, INPUT);
  pinMode(lineCenter, INPUT);
  pinMode(lineRight, INPUT);
  pinMode(ledPin, OUTPUT);

  // Serial port for feedback
  Serial.begin(9600);

}

void loop() {
  // Read all the inputs
  lineLeftState = digitalRead(lineLeft);
  lineCenterState = digitalRead(lineCenter);
  lineRightState = digitalRead(lineRight);

  // If centerline is on target, LED on
  if (lineCenterState == HIGH) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  // Serial print all states
  Serial.print(lineLeftState);
  Serial.print("   ");
  Serial.print(lineCenterState);
  Serial.print("   ");
  Serial.println(lineRightState);

  //Delay a bit
  delay(1000);
}
