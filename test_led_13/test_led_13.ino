/*
  Blink

  test_led_13
  
*/

const int pinLed = 13;

void setup() {
  // initialize digital pin pinLed as an output.
  pinMode(pinLed, OUTPUT);
}

void loop() {
  digitalWrite(pinLed, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(pinLed, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
