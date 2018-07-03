/*
 * sound_sensor
 */

void sound_sensor(){

  unsigned long currentMillisSoundSensor = millis();
  if (currentMillisSoundSensor - previousMillisSoundSensor >= 50) {
    previousMillisSoundSensor = currentMillisSoundSensor;

    sound_level = analogRead (PIN_SOUND);
    sound_level = map (sound_level, 0, 1023, 0, 255);
    potentiometer_level = analogRead (PIN_POTENTIOMETER);
    potentiometer_level = map (potentiometer_level, 0, 1023, 0, 255);
  
    /*
    Serial.print(sound_level);
    Serial.print(" ");
    Serial.println(potentiometer_level);
    */
  
    if( sound_level > potentiometer_level){
      if(led_white_state == 0){
        digitalWrite(PIN_LED_WHITE, HIGH);
        led_white_state = 1;
      }
      else{
        digitalWrite(PIN_LED_WHITE, LOW);
        led_white_state = 0;
      }
      //buzzer_high();
      alert();
    }

  }
  //delay(50);
  
}

