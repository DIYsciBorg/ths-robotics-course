#define MotR1     9
#define MotR2     10
#define MotL1     11
#define MotL2     12


void setup() {
  pinMode(MotR1, OUTPUT);
  pinMode(MotR2, OUTPUT);
  pinMode(MotL1, OUTPUT);
  pinMode(MotL2, OUTPUT);
}

void loop() {
  digitalWrite(MotR1, HIGH);
  delay(3000);
  digitalWrite(MotL1, HIGH);
  delay(3000);
  digitalWrite(MotR2, HIGH); // both pins high = break
  delay(50);
  digitalWrite(MotR1, LOW);  // both low = off
  digitalWrite(MotR2, LOW); 
  digitalWrite(MotL1, LOW); // reverse direction on Left
  digitalWrite(MotL2, HIGH);
  delay(3000);
}
