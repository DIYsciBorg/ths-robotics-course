/*  Sumo Start match code
 *  Emery Premeaux
 *  THS Robotics Course Season 2
 *  
 *  A simple demo to show how to receive the start match command from IR remote
 */
// ---------------------------------------------------------------------------
// IR Remote receiver for Starting the match
// ---------------------------------------------------------------------------
#include <IRremote.h>
#define RECV_PIN  4
IRrecv irrecv(RECV_PIN);
decode_results results;
#define STARTCODE 16757325

void setup() {
  // put your setup code here, to run once:
  // do all your stuff first, then enter the wait routine...
  // Remove all the serial debug stuff for the real contest!

  Serial.begin(115200);
  Serial.println("Waiting for start...");
  do {
    if (irrecv.decode(&results)) {
      if (results.value = STARTCODE) {
          Serial.println("GO!");
        loop();
      }
    }
  } while (results.value != STARTCODE);  // loop until the result matches the start signal
}

void loop() {
  // put your main code here, to run repeatedly:
  // Remove the demo code below and replace with your sumo code
  Serial.println("Robot fighting time!");
  delay(500);
}
