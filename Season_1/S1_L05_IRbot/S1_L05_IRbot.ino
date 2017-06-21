/*
 * IR-bot: (integer version) a simple robot drive example using remote control. 
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * based on IR-Dump by ken Shirrif
 */

// Setup the IR remote library
#include <IRremote.h>
int RECV_PIN = 7; 
IRrecv irrecv(RECV_PIN);
decode_results results;

// Define codes from the remote control to use in our robot
#define IRFORWARD   1888516741
#define IRBACKWARD  1888549381
#define IRLEFT      1888533061
#define IRRIGHT     1888500421
#define IRCANCEL    1888527451

// setup the robot servos
#include <Servo.h> 
Servo leftMotor;
Servo rightMotor;


void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  leftMotor.attach(9);  // attaches the servos
  rightMotor.attach(10);
}


void dump(decode_results *results) {
  // Dumps out the decode_results structure.
  // Call this after IRrecv::decode()
  int count = results->rawlen;
  
  if (results->decode_type == UNKNOWN) {
    Serial.print("Unknown encoding: ");
  }
  else if (results->decode_type == NEC) {
    Serial.print("Decoded NEC: ");

  }
  else if (results->decode_type == SONY) {
    Serial.print("Decoded SONY: ");
  }
  else if (results->decode_type == RC5) {
    Serial.print("Decoded RC5: ");
  }
  else if (results->decode_type == RC6) {
    Serial.print("Decoded RC6: ");
  }
  else if (results->decode_type == PANASONIC) {
    Serial.print("Decoded PANASONIC - Address: ");
    Serial.print(&results->address, HEX);
    Serial.print(" Value: ");
  }
  else if (results->decode_type == LG) {
    Serial.print("Decoded LG: ");
  }
  else if (results->decode_type == JVC) {
    Serial.print("Decoded JVC: ");
  }
  else if (results->decode_type == AIWA_RC_T501) {
    Serial.print("Decoded AIWA RC T501: ");
  }
  else if (results->decode_type == WHYNTER) {
    Serial.print("Decoded Whynter: ");
  }
  Serial.print(results->value, HEX);
  Serial.print(" (");
  Serial.print(results->bits, DEC);
  Serial.println(" bits)");
  Serial.print("Raw (");
  Serial.print(count, DEC);
  Serial.print("): ");

  for (int i = 1; i < count; i++) {
    if (i & 1) {
      Serial.print(results->rawbuf[i]*USECPERTICK, DEC);
    }
    else {
      Serial.write('-');
      Serial.print((unsigned long) results->rawbuf[i]*USECPERTICK, DEC);
    }
    Serial.print(" ");
  }
  Serial.println();
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value);
    
    // take action!
    switch(results.value){
      case IRFORWARD:
        Serial.println(" FORWARD!");
        forward();
        break;
      case IRBACKWARD:
      Serial.println(" BACKWARD!");
        backward();
        break;
      case IRLEFT:
      Serial.println(" TURN LEFT!");
        turnleft();
        break;
      case IRRIGHT:
      Serial.println(" TURN RIGHT!");
        turnright();
        break;
        case IRCANCEL:
      Serial.println(" STOP!");
        robotstop();
        break;
    }

    dump(&results);
    irrecv.resume(); // Receive the next value
  }
}

void forward(){
  leftMotor.write(0);             
  rightMotor.write(180);

}

void backward(){
  leftMotor.write(180);             
  rightMotor.write(0);
}

void turnleft(){
  leftMotor.write(0);             
  rightMotor.write(0);
}

void turnright(){
  leftMotor.write(180);             
  rightMotor.write(180);
}

void robotstop(){
  leftMotor.write(90);             
  rightMotor.write(90);
}

