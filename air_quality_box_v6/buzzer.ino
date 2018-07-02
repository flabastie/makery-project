int melody[] = {
  NOTE_D3, NOTE_F3, NOTE_G3, NOTE_D3, NOTE_F3, NOTE_G3, NOTE_D3, NOTE_F3
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
/*int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};*/

int noteDurations[] = {
  4, 4, 4, 4, 4, 4, 4, 2
};

void buzzer_fn() {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(pinBuzzer, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(pinBuzzer);
  }
}
  
  
  
  void buzzer_mission_fn(){
   
    tone(pinBuzzer,146.83,400);//D
      delay(400);
    
    tone(pinBuzzer,146.83,400);//D
       delay(400);
    
    tone(pinBuzzer,146.83,250);//D
       delay(250);
    
    tone(pinBuzzer,174.61,250);//F
       delay(250);
    
    tone(pinBuzzer,196.00,350);//G
       delay(400);
    
    tone(pinBuzzer,146.83,350);//D
      delay(400);
    
    tone(pinBuzzer,146.83,200);//D
       delay(250);
    
    tone(pinBuzzer,146.83,200);//D
       delay(250);
    
     tone(pinBuzzer,130.81,400);//C
       delay(450);
    
     tone(pinBuzzer,130.81,400);//C
       delay(450);
    
    tone(pinBuzzer,146.83,400);//D
       delay(450);
    
    tone(pinBuzzer,146.83,400);//D
       delay(450);
    
     tone(pinBuzzer,146.83,400);//D
       delay(450);
    
    tone(pinBuzzer,174.61,400);//F
       delay(300);
    
    tone(pinBuzzer,196.00,400);//G
       delay(450);
    
     tone(pinBuzzer,146.83,400);//D
       delay(450);
    
    tone(pinBuzzer,146.83,400);//D
       delay(450);
    
     tone(pinBuzzer,146.83,400);//D
       delay(450);
    
    tone(pinBuzzer,130.81,400);//C
       delay(300);
    
     tone(pinBuzzer,130.81,400);//C
       delay(300);
    
    tone(pinBuzzer,130.81,400);//C
       delay(450);
    
  }
