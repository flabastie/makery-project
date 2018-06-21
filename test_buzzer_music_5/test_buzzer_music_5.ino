//*****************************************************************************
//
// Test of playtune library for Arduino NANO
//
// L. Shustek, 31 Jan 2011, initial release.
// L. Shustek, 27 Feb 2011, new score data
// L. Shustek, 6 April 2015; change for compatibility with Arduino IDE v1.6.x
// T. Wasiluk, 28 May 2016; added debug & delay code, moved to examples subdirectory
//
//*****************************************************************************


#include <Playtune.h>

//------------------------------------------------
//   scores are put in program space memory
//------------------------------------------------

const unsigned char PROGMEM score [] = {
0x90,53, 0,253, 0x80, 0,14, 0x90,56, 0,253, 0x80, 0,14, 0x90,60, 0,253, 0x80, 0,14, 0x90,53, 0,253, 0x80, 
0,14, 0x90,56, 0,253, 0x80, 0,14, 0x90,60, 0,253, 0x80, 0,14, 0x90,53, 0,253, 0x80, 0,14, 0x90,56, 0,253, 
0x80, 0,14, 0x90,53, 0,253, 0x80, 0,14, 0x90,56, 0,253, 0x80, 0,14, 0x90,61, 0,253, 0x80, 0,14, 0x90,53, 
0,253, 0x80, 0,14, 0x90,56, 0,253, 0x80, 0,14, 0x90,61, 0,253, 0x80, 0,14, 0x90,53, 0,253, 0x80, 0,14, 
0x90,56, 0,253, 0x80, 0,14, 0x90,51, 0,253, 0x80, 0,14, 0x90,56, 0,253, 0x80, 0,14, 0x90,60, 0,253, 0x80, 
0,14, 0x90,51, 0,253, 0x80, 0,14, 0x90,56, 0,253, 0x80, 0,14, 0x90,60, 0,253, 0x80, 0,14};
// This score contains 3488 bytes, and 6 tone generators are used.

/*const unsigned char PROGMEM score [] = {
0x90,53, 0,253, 0x80, 0,14, 0x90,56, 0,253, 0x80, 0,14, 0x90,60, 0,253, 0x80, 0,14, 0x90,53, 0,253, 0x80, 
0,14, 0x90,56, 0,253, 0x80, 0,14, 0x90,60, 0,253, 0x80, 0,14, 0x90,53, 0,253, 0x80, 0,14, 0x90,56, 0,253, 
0x80, 0,14, 0x90,53, 0,253, 0x80, 0,14, 0x90,56, 0,253, 0x80, 0,14, 0x90,61, 0,253, 0x80, 0,14, 0x90,53, 
0,253, 0x80, 0,14, 0x90,56, 0,253, 0x80, 0,14, 0x90,61, 0,253, 0x80, 0,14, 0x90,53, 0,253, 0x80, 0,14, 
0x90,56, 0,253, 0x80, 0,14, 0x90,51, 0,253, 0x80, 0,14, 0x90,56, 0,253, 0x80, 0,14, 0x90,60, 0,253, 0x80, 
0,14, 0x90,51, 0,253, 0x80, 0,14, 0x90,56, 0,253, 0x80, 0,14, 0x90,60, 0,253, 0x80, 0,14};*/
// This score contains 3488 bytes, and 6 tone generators are used.

Playtune pt;

void setup() {

  // Enable all 3 NANO timers for notes that are output on digital pins 10, 11, and 12.
  // Those pins should be wired to 500-ohm resistors, the other ends of which should be connected together
  // to one terminal of an 8-ohm speaker. The other terminal of the speaker should be connected to ground.
  // No other hardware is needed!

  pt.tune_initchan (5); 
  //pt.tune_initchan (11);
  //pt.tune_initchan (12);

  #define DBUG 0
  #if DBUG
  Serial.begin(9600);
  Serial.println("Debug");
  #endif
  
}

void loop() {

  pt.tune_playscore (score); /* start playing */
  while (pt.tune_playing) ; /* wait here until playing stops */
  pt.tune_delay(1000); /* wait a second */
  
}
