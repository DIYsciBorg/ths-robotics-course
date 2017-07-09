#define MotR1     6
#define MotR2     9
#define MotL1     10
#define MotL2     11

void setup() {
  pinMode(MotR1, OUTPUT);
  pinMode(MotR2, OUTPUT);
  pinMode(MotL1, OUTPUT);
  pinMode(MotL2, OUTPUT);
  Serial.begin(9600);
}
/*
 * MY control table (Mode 1)
 * Left Motor Phase L1: LOW = forward, HIGH = rev
 * Left Motor PWM L2
 * 
 * Right Motor Phase R1: LOW = forward, HIGH = rev
 * Right Motor PWM R2
 * 
 * To correct these, just flip the wires of the motor going backwards
 */
void loop() {
  // Left motor forward:
  digitalWrite(MotL1, LOW);
  analogWrite(MotL2, 255);

  // Right motor forward:
  digitalWrite(MotR1, LOW);
  analogWrite(MotR2, 255);

  delay(5000); 

  // Left motor reverse:
  digitalWrite(MotL1, HIGH);
  analogWrite(MotL2, 255);

  // Right motor reverse:
  digitalWrite(MotR1, HIGH);
  analogWrite(MotR2, 255);

  delay(5000);

}
