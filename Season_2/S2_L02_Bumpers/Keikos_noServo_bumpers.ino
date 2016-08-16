#include <NewPing.h>

//definition
#define TRIGGER_PIN  12 
#define ECHO_PIN     11
#define MAX_DISTANCE 200
#define SERVO_PINL 10
#define SERVO_PINR 9
#define REFRESH_TIME 20   // 20
#define BUMPER_PINR 4
#define BUMPER_PINL 8

//valuable properties
int minPulse = 2500;     // 500
int maxPulse = 500;    // 2500
long addjustedAV = 0;
int pulseL = 0;
int pulseR = 0;
int delayValueMax = 2000;   // 20000
int delayValue = 2000;      // 20000
int lastTime = 0;

boolean flagL = false;
boolean flagR = false;

//Instances
//NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 

void setup() {
  pinMode(13, OUTPUT);
  pinMode (SERVO_PINL, OUTPUT);
  pinMode (SERVO_PINR, OUTPUT);
  pinMode (BUMPER_PINL, OUTPUT);
  pinMode (BUMPER_PINR, OUTPUT);
  pulseL = minPulse;
  pulseR = maxPulse;
  Serial.begin(9600);
}

void loop() {
 // int temp = sonar.ping_cm();
//  addjustedAV = (temp / 10) * 19;

//  pulseL = addjustedAV + minPulse;
//  pulseR = maxPulse - addjustedAV;

  jogging();

  if(millis() - lastTime >= REFRESH_TIME) {

    if(digitalRead(BUMPER_PINL)==LOW){
      flagL = false;
      Serial.println("L_LOW");
    }else{
      flagL = true;
      Serial.println("L_HIGH");
    }if(digitalRead(BUMPER_PINR)==LOW){
      flagR = false;
      Serial.println("R_LOW");
    }else{
      flagR = true;
      Serial.println("R_HIGH");
    }
    lastTime = millis();
  }
}

void jogging () {

  if(flagL || flagR){
    for(int i = 0; i<500; i++){
      digitalWrite(SERVO_PINL, HIGH);
      delayMicroseconds(pulseR);
      digitalWrite(SERVO_PINL, LOW);

      digitalWrite(SERVO_PINR, HIGH);
      delayMicroseconds(pulseL);
      digitalWrite(SERVO_PINR, LOW);
    }
    if(flagL){
      for(int i = 0; i<250; i++){
        digitalWrite(SERVO_PINL, HIGH);
        delayMicroseconds(pulseR);
        digitalWrite(SERVO_PINL, LOW);

        digitalWrite(SERVO_PINR, HIGH);
        delayMicroseconds(pulseR);
        digitalWrite(SERVO_PINR, LOW);
      }
    }
    if(flagR){
      for(int i = 0; i<700; i++){
        digitalWrite(SERVO_PINL, HIGH);
        delayMicroseconds(pulseL);
        digitalWrite(SERVO_PINL, LOW);

        digitalWrite(SERVO_PINR, HIGH);
        delayMicroseconds(pulseL);
        digitalWrite(SERVO_PINR, LOW);
      }
    }
  }else{
    digitalWrite(SERVO_PINL, HIGH);
    delayMicroseconds(pulseL);
    digitalWrite(SERVO_PINL, LOW);

    digitalWrite(SERVO_PINR, HIGH);
    delayMicroseconds(pulseR);
    digitalWrite(SERVO_PINR, LOW);
  }

  delayValue = (delayValueMax - pulseL) - pulseR;
  delayMicroseconds(delayValue);
}
