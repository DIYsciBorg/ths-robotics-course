#include <Servo.h> 
 
Servo leftMotor;
Servo rightMotor;
 
int pos = 0;    // variable to store the servo position 
 
void setup() 
{ 
  leftMotor.attach(9);  // attaches the servo on pin 9 to the servo object
  rightMotor.attach(8); 
} 
 
 
void loop() 
{ 
    leftMotor.write(0);             
    rightMotor.write(0);
    delay(1500);
    
    leftMotor.write(90);             
    rightMotor.write(90);
    delay(1500);
    
    leftMotor.write(250);             
    rightMotor.write(250);
    delay(1500);
    
    leftMotor.write(250);             
    rightMotor.write(250);
    delay(1500);
} 
