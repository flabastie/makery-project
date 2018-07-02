/*
 * led_on_sound
 * 
 */

// variables
int sensorValue;  

void setup() {
  Serial.begin (9600); 
}

void loop() {

  // sensor
  sensorValue = analogRead (A2);
  sensorValue = map (sensorValue, 0, 1023, 0, 255); 
  Serial.println(sensorValue);
  delay(50);
    
}
