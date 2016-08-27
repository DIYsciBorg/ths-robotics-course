#include <TimerOne.h>
int textcounter = 0;
int textinterval = 10;
 
void setup() 
{
  // Initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards
  pinMode(13, OUTPUT);    
  
  Timer1.initialize(10000); // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
  Timer1.attachInterrupt( timerIsr ); // attach the service routine here
  Serial.begin(9600);
}
 
void loop()
{
  // Main code loop
  // TODO: Put your regular (non-ISR) logic here
  if (textcounter >= textinterval){
    Serial.println("That was 10 times!");
    textcounter = 0;
  } 
}
 
/// --------------------------
/// Custom ISR Timer Routine
/// --------------------------
void timerIsr()
{
    // Toggle LED
    digitalWrite( 13, digitalRead( 13 ) ^ 1 );
    Serial.println("1 count");
    textcounter++;
}
