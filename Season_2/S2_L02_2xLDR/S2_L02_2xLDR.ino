/*
  Tokyo HackerSpace
  Robotics course Season 2, lesson 2
  Modified from AnalogReadSerial
  This sketch should read two Light Dependent Resistors attached to A0 and A1
  and print them to the Serial terminal.
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int LDRLeft = analogRead(A0);
  int LDRRight = analogRead(A1);
  // print out the value you read:
  Serial.print(LDRLeft);
  Serial.print("   ");
  Serial.println(LDRRight);
  delay(100);        // delay in between reads for stability
}
