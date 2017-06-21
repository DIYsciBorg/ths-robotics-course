#define MotR1     9
#define MotR2     10
#define MotL1     11
#define MotL2     12

int LeftPWM = 0;
int RightPWM = 0;  // analogWrite takes value 0 to 255

int LeftSTEP = 5;
int RightSTEP = 5;

boolean LeftDIR = 0;    // rotate opposite directions(?)
boolean RightDIR = 0;


void setup() {
  pinMode(MotR1, OUTPUT);
  pinMode(MotR2, OUTPUT);
  pinMode(MotL1, OUTPUT);
  pinMode(MotL2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (LeftDIR == 1){
      digitalWrite(MotL2, HIGH);
    } else{
      digitalWrite(MotL2, LOW);
    }

    if (RightDIR == 1){
      digitalWrite(MotR2, HIGH);
    } else{
      digitalWrite(MotR2, LOW);
    }

    
  analogWrite(MotL1, LeftPWM);
  analogWrite(MotR1, RightPWM);
  LeftPWM = LeftPWM + LeftSTEP;
  RightPWM = RightPWM + RightSTEP;
  
  if (LeftPWM <= 0 || LeftPWM >= 255) {
    LeftSTEP = -LeftSTEP;
    LeftDIR = !LeftDIR;
  }
  if (RightPWM <= 0 || RightPWM >= 255) {
    RightSTEP = -RightSTEP;
    RightDIR = !RightDIR;
  }
  Serial.print(LeftPWM);
  Serial.print("  ");
  Serial.println(RightPWM);
  delay(500);
  
}
