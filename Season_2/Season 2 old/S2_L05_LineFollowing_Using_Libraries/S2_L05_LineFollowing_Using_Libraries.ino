/* TokyoHackerSpace Robotics Course
 *  By Emery Premeaux
 *  Season 2, Lesson 5
 *  Line following robot using our new library
 */

#include "LineToDigital.h"
#include <Servo.h>

LineToDigital line(14,15,16, 90, 90, 90); // MUST be analog pins. Remember that on Uno, A0-A5 is 14-19.

Servo leftWheel;
#define pinLeftWheel 10
Servo rightWheel;
#define pinRightWheel 9

/* I am using the analogy of a automotive shifting gear.
 * 0 = stop 
 * 1, 2, 3 equal forward speeds slow, medium, fast
 * -1, -2, -3 equal reverse slow, medium, fast
 * We must remember to constrain our "Gear shift" to this range
 */
int leftWheelGear = 0;
int rightWheelGear = 0;
 
void setup() {
  Serial.begin(19200);
  leftWheel.attach(pinLeftWheel);
  rightWheel.attach(pinRightWheel);
}

void loop() {
  // Read all the inputs
  int LeftSensor = line.LineLeft();
  int CenterSensor = line.LineCenter();
  int RightSensor = line.LineRight();

  Serial.print(LeftSensor);
  Serial.print("   ");
  Serial.print(CenterSensor);
  Serial.print("   ");
  Serial.println(RightSensor);


/* Our basic logic block.
 * Check the sensors, make a decision, and change the left and right gear settings.
 * 
 * REMEMBER:  0 = NO reflection (black)
 */
  if (CenterSensor == 0){
    Serial.println("Somewhere one the line!");
  }

  if (LeftSensor == 0){   // We are on the left sensor, need to turn more left!
    leftWheelGear--;
    rightWheelGear++;
    Serial.println("turn more LEFT");
  }

  if (RightSensor == 0){   // We are on the left sensor, need to turn more left!
    leftWheelGear++;
    rightWheelGear--;
    Serial.println("turn more RIGHT");
  }
/* 
 *  Now constrain the "gears" in case we set on out of bounds
 */
  if (leftWheelGear > 3){
    leftWheelGear = 3;
  }
  if (leftWheelGear < -3){
    leftWheelGear = -3;
  }
  if (rightWheelGear > 3){
    rightWheelGear = 3;
  }
  if (rightWheelGear < -3){
    rightWheelGear = -3;
  }
  // print them out for debug
  Serial.print("left Gear = ");
  Serial.print(leftWheelGear);
  Serial.print("   ");
  Serial.print("right Gear = ");
  Serial.println(rightWheelGear);


/* 
 *  Now convert the "gear" into servo values
 */
  switch (leftWheelGear) {
    case 3:
    leftWheel.write(180);
    break;
    case 2:
    leftWheel.write(150);
    break;
    case 1:
    leftWheel.write(120);
    break;
    case 0:
    leftWheel.write(90);
    break;
    case -1:
    leftWheel.write(60);
    break;
    case -2:
    leftWheel.write(30);
    break;
    case -3:
    leftWheel.write(0);
    break;
    default:
    leftWheelGear = 0;
    break;
  }
  switch (rightWheelGear) {
    case 3:
    rightWheel.write(0);
    break;
    case 2:
    rightWheel.write(30);
    break;
    case 1:
    rightWheel.write(60);
    break;
    case 0:
    rightWheel.write(90);
    break;
    case -1:
    rightWheel.write(120);
    break;
    case -2:
    rightWheel.write(150);
    break;
    case -3:
    rightWheel.write(180);
    break;
    default:
    rightWheelGear = 0;
    break;
  }
 
  //Delay a bit
  delay(1000);
}
