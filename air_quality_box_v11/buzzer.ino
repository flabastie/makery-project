/*
 * buzzer
 */

int melody[] = {
  NOTE_D3, NOTE_F3, NOTE_G3, NOTE_D3, NOTE_F3, NOTE_G3, NOTE_D3, NOTE_F3
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:

int noteDurations[] = {
  4, 4, 4, 4, 4, 4, 4, 2
};

/*
 * buzzer_fn
 */

void buzzer_fn() {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(PIN_BUZZER, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(PIN_BUZZER);
  }
}
  
/*
 * Fresh Air
 */

int melody_fresh[] = {
    NOTE_F4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F3, NOTE_C4, NOTE_F4

};

int noteDurations_fresh[] = {
4, 4, 4, 4, 1, 4, 2, 4, 2
};

void buzzer_fresh() {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 1000 / noteDurations_fresh[thisNote];
    tone(PIN_BUZZER, melody_fresh[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(PIN_BUZZER);
  }
}

/*
 * Low pollution
 */

int melody_low[] = {
        NOTE_F4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_G4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_C4
};


int noteDurations_low[] = {
   2, 8, 1, 4, 2, 8, 4, 1, 2
};

void buzzer_low() {
  if(alert_air_state == 0){
    alert_air_state = 1;
    int afterEvent = t.after(TEMPO_AFTER_ALERT, doAfterAirAlert);
      // iterate over the notes of the melody:
      for (int thisNote = 0; thisNote < 8; thisNote++) {
        int noteDuration = 1000 / noteDurations_low[thisNote];
        tone(PIN_BUZZER, melody_low[thisNote], noteDuration);
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        // stop the tone playing:
        noTone(PIN_BUZZER);
      }
    }
}

/*
 * High pollution
 */

int melody_high[] = {
    NOTE_C5, NOTE_B5, NOTE_F5, NOTE_G4, NOTE_A4, NOTE_F4, NOTE_C5, NOTE_C5, NOTE_F5
};

// note durations: 4 = quarter note, 9 = eighth note, etc.:
int noteDurations_high[] = {
  2, 8, 1, 4, 8, 4, 8, 4, 1
};

void buzzer_high() {
  if(alert_air_state == 0){
    alert_air_state = 1;
    int afterEvent = t.after(TEMPO_AFTER_ALERT, doAfterAirAlert);
    // iterate over the notes of the melody:
    for (int thisNote = 0; thisNote < 8; thisNote++) {
      int noteDuration = 1000 / noteDurations_high[thisNote];
      tone(PIN_BUZZER, melody_high[thisNote], noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      // stop the tone playing:
      noTone(PIN_BUZZER);
    }
  }
}

/*
 * Maxi pollution
 */

int melody_maxi[] = {
    NOTE_C5, NOTE_B2, NOTE_C5, NOTE_B4, NOTE_C5, NOTE_B2, NOTE_C5, NOTE_C5
};

int noteDurations_maxi[] = {
  2, 8, 1, 4, 2, 8, 1, 4, 1
};

void buzzer_maxi() {
  if(alert_air_state == 0){
    alert_air_state = 1;
    int afterEvent = t.after(TEMPO_AFTER_ALERT, doAfterAirAlert);
    // iterate over the notes of the melody:
    for (int thisNote = 0; thisNote < 8; thisNote++) {
      int noteDuration = 1000 / noteDurations_maxi[thisNote];
      tone(PIN_BUZZER, melody_maxi[thisNote], noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      // stop the tone playing:
      noTone(PIN_BUZZER);
    }
  }
}

/*
 * Start
 */
/*
int melody_start[] = {
      NOTE_F4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_F4, NOTE_F4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4
};

int noteDurations_start[] = {
4, 4, 4, 4, 1, 4, 4, 4, 4, 1
};

void buzzer_start() {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 10; thisNote++) {
    int noteDuration = 1000 / noteDurations_start[thisNote];
    tone(PIN_BUZZER, melody_start[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(PIN_BUZZER);
  }
}
*/


int melody_start[] = {
      NOTE_F4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_F4
};

int noteDurations_start[] = {
4, 4, 4, 4, 1
};

void buzzer_start() {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 5; thisNote++) {
    int noteDuration = 1000 / noteDurations_start[thisNote];
    tone(PIN_BUZZER, melody_start[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(PIN_BUZZER);
  }
}

/*
 * doAfterAirAlert() 
 */

void doAfterAirAlert()
{
  alert_air_state = 0;
}
