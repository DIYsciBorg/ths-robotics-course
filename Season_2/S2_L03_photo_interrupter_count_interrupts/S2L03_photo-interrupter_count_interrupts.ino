/*
  photo-interruptor counter take 2
  Now we apply interrupts to the problem, and should be able to
  successfully count every pulse.

  By Emery Premeaux
 */

// constants won't change. They're used here to
// set pin numbers:
const int photoswitch = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
volatile byte switchstate = LOW;
int counter = 0;
int interval = 0;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);

  // prepare the photoswitch as an interrupt
  pinMode(photoswitch, INPUT);
  attachInterrupt(0, interrupt_photoswitch, FALLING);
  Serial.begin(9600);
}

void interrupt_photoswitch(){
    counter++;
    interval++;
    if (interval == 10){
      Serial.println(counter);
      interval = 0;
    }
    // Toggle the LED
    digitalWrite(ledPin, !digitalRead(ledPin));
}

void loop() {
  // We have nothing to do while waiting for the interrupt to happen.
  // Normally, other robot code might go here.
}
