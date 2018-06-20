

// Interruption sur changement d'état de A
void doEncoderA(){
  // debounce
  if ( rotating ) delay (1);  // attendre un petit peut
  rotating = true; //activation de l'anti-rebond
  // Confirmation du changement 
  if( digitalRead(encoderPinA) != A_set ) {
    A_set = !A_set;

    if (B_change) {
      encoderPos += 1;
      B_change = false;
    } else 
      A_change = true;

    rotating = false;  //libération de l'anti-rebond
  }
}

// Interruption sur changement d'etat de B
void doEncoderB(){
  if ( rotating ) delay (1);
  rotating = true;
  if( digitalRead(encoderPinB) != B_set ) {
    B_set = !B_set;

    if (A_change) {
      encoderPos -= 1;
      A_change = false;
    } else 
      B_change = true;

    rotating = false;
  }
}
