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

// Playtune bytestream for file "Sakura_Sakura.mid" created by MIDITONES V1.16 on Thu Jun 21 09:54:40 2018
// command line: ../midiprog/miditones.exe Sakura_Sakura 
const unsigned char PROGMEM score [] = {
0x81, 0,41, 0x83, 0x84, 0,1, 0x91,71, 0x93,95, 3,21, 0x81, 0,41, 0x80, 0x82, 
0x83, 0x85, 0,1, 0x94,76, 0x91,72, 0x90,53, 0x92,41, 0x93,96, 0x95,59, 3,21, 0x81, 0,41, 0x83, 0x84, 0,1, 0x91,71, 
0x93,95, 0x94,77, 1,158, 0x84, 0,1, 0x94,77, 1,117, 0x81, 0,41, 0x80, 0x82, 0x83, 0x84, 0x85, 0,1, 0x91,69, 0x90,57, 
0x92,45, 0x93,93, 0x94,76, 0x95,60, 3,21, 0x81, 0,41, 0x83, 0x84, 0,1, 0x91,71, 0x93,95, 1,138, 0x81, 0,20, 
0x83, 0,1, 0x91,69, 0x93,93, 1,138, 0x81, 0,20, 0x80, 0x82, 0x83, 0x85, 0,1, 0x94,76, 0x90,57, 0x91,65, 0x92,41};
// This score contains 3587 bytes, and 6 tone generators are used.
// 56 notes had to be skipped.


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
