/* TokyoHackerSpace Robotics Course
 *  By Emery Premeaux
 *  Season 2, Lesson 5
 *  Line sensor building libraries: Check
 */

#include "LineToDigital.h"

LineToDigital line(14,15,16, 100, 100, 100); // MUST be analog pins. Remember that on Uno, A0-A5 is 14-19.
 
void setup() {
  Serial.begin(19200);
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
  
  //Delay a bit
  delay(500);
}
