/*
  Tokyo HackerSpace
  Robotics course Season 2, lesson 2
  Photovore:
  This sketch puts together the H-bridge control and LDR
  The robot should seek out the brightest space in the room.
*/
#define MotR1       6
#define MotR2       9
#define MotL1       10
#define MotL2       11
#define StopThresh  10
#define Converge    50

int LeftSpeed, RightSpeed = 0;
boolean LeftDir, RightDir  = 0;
int State = 0;


void setup() {
  pinMode(MotR1, OUTPUT);
  pinMode(MotR2, OUTPUT);
  pinMode(MotL1, OUTPUT);
  pinMode(MotL2, OUTPUT);

  // in this sketch, we only need to go forward.
  digitalWrite(MotL1, LOW);
  digitalWrite(MotL2, LOW);
  
  Serial.begin(9600);
}


void loop() {
  int LDRLeft = analogRead(A0);
  int LDRRight = analogRead(A1);
  Serial.print(LDRLeft-LDRRight);
  Serial.print("   ");
  
  if (LDRLeft>LDRRight){
    State = 1;
  }
  if (LDRLeft<LDRRight){
    State = -1;
  }
  /* Though one of the first two checks will be true, we still
   * want to catch the case that the robot is under the light.
   * Because program code is sequential, we can still change
   * the State one last time, if the absolute value is within
   * the set threshold.
   */
  if (abs(LDRLeft-LDRRight)<=StopThresh){
    State = 0;
  }
  
  /* State Machine
   *  A state machine defines the actions our robot can take
   *  based on a set of inputs.
   *  In this case, our inputs are the LDR (or more precisely,
   *  which is greater?
   *  
   *  We want three states:
   *  0: Stop (LDR readings are equal, or close to equal. We found the light)
   *  1: Turn left (the left side sees more light)
   *  -1: Turn right (the right side sees more light)
   *  For now, we will ignore attempting to back up.
   */
   switch (State) {
    case 0:       // under the light
      analogWrite(MotR2, 0);
      analogWrite(MotL2, 0);
      Serial.println("Ahh!  Happy light. Let's rest.");
      break;

    case 1:       // light is to the left, make right go faster
      if ((LDRLeft-LDRRight) > Converge){
        analogWrite(MotL2, 0);
        analogWrite(MotR2, 255);
      } else {
        analogWrite(MotL2, 150);
        analogWrite(MotR2, 255);
      }
      Serial.println("Ohh Over there! Turn left!");
      break;

    case -1:      // light is to the right, make left go faster
       if ((LDRRight-LDRLeft) > Converge){
        analogWrite(MotL2, 255);
        analogWrite(MotR2, 0);
      } else {
        analogWrite(MotL2, 255);
        analogWrite(MotR2, 150);
      }
      Serial.println("By golly, turn right!");
      break;
      
    default:      // some strange error!
      Serial.println("Whoa horsey! You aint supposed to be here!");
      break;
   }
   delay (500);
}

