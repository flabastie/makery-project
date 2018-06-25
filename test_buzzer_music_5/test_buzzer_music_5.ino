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
0x80, 0,14, 0x90,53, 0,253, 0x80, 0,14};
// This score contains 3488 bytes, and 6 tone generators are used.

/*const unsigned char PROGMEM score [] = {
0x90,53, 0,253, 0x80, 0,14, 0x90,56, 0,253, 0x80, 0,14, 0x90,60, 0,253, 0x80, 0,14, 0x90,53, 0,253, 0x80, 
0,14, 0x90,56, 0,253, 0x80, 0,14, 0x90,60, 0,253, 0x80, 0,14, 0x90,53, 0,253, 0x80, 0,14, 0x90,56, 0,253, 
0x80, 0,14, 0x90,53, 0,253, 0x80, 0,14, 0x90,56, 0,253, 0x80, 0,14, 0x90,61, 0,253, 0x80, 0,14, 0x90,53, 
0,253, 0x80, 0,14, 0x90,56, 0,253, 0x80, 0,14, 0x90,61, 0,253, 0x80, 0,14, 0x90,53, 0,253, 0x80, 0,14, 
0x90,56, 0,253, 0x80, 0,14, 0x90,51, 0,253, 0x80, 0,14, 0x90,56, 0,253, 0x80, 0,14, 0x90,60, 0,253, 0x80, 
0,14, 0x90,51, 0,253, 0x80, 0,14, 0x90,56, 0,253, 0x80, 0,14, 0x90,60, 0,253, 0x80, 0,14};*/
// This score contains 3488 bytes, and 6 tone generators are used.

// Playtune bytestream for file "sakura_gtr.mid" created by MIDITONES V1.16 on Fri Jun 22 16:30:28 2018
// command line: ../midiprog/miditones.exe sakura_gtr 
/*const unsigned char PROGMEM score [] = {
0,9, 0x90,57, 0x91,57, 0x92,45, 0x93,45, 0x94,52, 0x95,52, 4,18, 0x90,57, 0x91,57, 3,152, 0,47, 0,15, 
0x90,59, 0x91,59, 0x82, 0x83, 0x84, 0x85, 0,31, 0x92,50, 0x93,50, 0,47, 0x94,55, 0x95,55, 7,33, 0,39, 0,8, 
0,8, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0,7, 0x90,57, 0x91,57, 0,31, 0x92,48, 0x93,48, 0,47, 0x94,53, 0x95,53, 
3,197, 0x90,57, 0x91,57, 3,150, 0,1, 0,47, 0,15, 0x90,59, 0x91,59, 0x82, 0x83, 0x84, 0x85, 0,31, 0x92,52, 
0x93,52, 0,47, 0x94,56, 0x95,56, 7,89, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0,7, 0x90,57, 0x91,57, 0x92,45, 0x93,45, 
0x94,52, 0x95,52, 4,20, 0x90,59, 0x91,59, 3,152, 0,45, 0x82, 0x83, 0,1, 0x92,45, 0x93,45, 0,15, 0x90,60, 
0x91,60, 0x84, 0x85, 0,31, 0x94,50, 0x95,50, 0,47, 3,135, 0x90,59, 0x91,59, 3,209, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 
0,7, 0x90,57, 0x91,57, 0x92,45, 0x93,45, 0x94,52, 0x95,52, 4,20, 0x90,59, 0x91,59, 2,113, 0x80, 0x81, 0,30, 
0x90,57, 0x91,57, 1,42, 0x80, 0x81, 0,29, 0x90,53, 0x91,53, 0x92,41, 0x93,41, 0x94,47, 0x95,47, 7,168, 0x80, 0x81, 
0x82, 0x83, 0x84, 0x85, 0,7, 0x90,52, 0x91,52, 0x92,43, 0x93,43, 0x94,48, 0x95,48, 4,20, 0x90,48, 0x91,48, 3,216, 
0x90,52, 0x91,52, 0x92,41, 0x93,41, 0x94,48, 0x95,48, 3,214, 0x90,53, 0x91,53, 3,144, 0x82, 0x83, 0,65, 0x80, 0x81, 
0x84, 0x85, 0,7, 0x90,52, 0x91,52, 0x92,43, 0x93,43, 0x94,48, 0x95,48, 4,20, 0x90,52, 0x91,52, 2,113, 0x80, 0x81, 
0,30, 0x90,48, 0x91,48, 1,42, 0x80, 0x81, 0x84, 0x85, 0,29, 0x90,47, 0x91,47, 0x92,44, 0x93,44, 3,214, 0x92,40, 
0x93,40, 3,209, 0x80, 0x81, 0x82, 0x83, 0,7, 0x90,57, 0x91,57, 0x92,45, 0x93,45, 0x94,52, 0x95,52, 4,20, 0x90,59, 
0x91,59, 3,152, 0,45, 0x82, 0x83, 0,1, 0x92,45, 0x93,45, 0,15, 0x90,60, 0x91,60, 0x84, 0x85, 0,31, 0x94,50, 
0x95,50, 0,47, 3,135, 0x90,59, 0x91,59, 3,209, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0,7, 0x90,57, 0x91,57, 0x92,45, 
0x93,45, 0x94,52, 0x95,52, 4,20, 0x90,59, 0x91,59, 2,113, 0x80, 0x81, 0,30, 0x90,57, 0x91,57, 1,42, 0x80, 0x81, 
0,29, 0x90,53, 0x91,53, 0x92,41, 0x93,41, 0x94,47, 0x95,47, 7,151, 0x84, 0x85, 0,17, 0x80, 0x81, 0x82, 0x83, 0,7, 
0x90,52, 0x91,52, 0x92,43, 0x93,43, 0x94,48, 0x95,48, 4,20, 0x90,48, 0x91,48, 3,216, 0x90,52, 0x91,52, 0x92,41, 
0x93,41, 0x94,48, 0x95,48, 3,214, 0x90,53, 0x91,53, 3,209, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0,7, 0x90,52, 0x91,52, 
0x92,43, 0x93,43, 0x94,48, 0x95,48, 4,20, 0x90,52, 0x91,52, 2,113, 0x80, 0x81, 0,30, 0x90,48, 0x91,48, 1,6, 
0x82, 0x83, 0,36, 0x80, 0x81, 0x84, 0x85, 0,29, 0x90,47, 0x91,47, 0x92,44, 0x93,44, 3,214, 0x92,40, 0x93,40, 3,144, 
0x82, 0x83, 0,65, 0x80, 0x81, 0,7, 0x90,57, 0x91,57, 0x92,45, 0x93,45, 0x94,52, 0x95,52, 4,20, 0x90,57, 0x91,57, 
3,152, 0,47, 0,15, 0x90,59, 0x91,59, 0x82, 0x83, 0x84, 0x85, 0,31, 0x92,50, 0x93,50, 0,47, 0x94,55, 0x95,55, 
7,33, 0,39, 0,8, 0,8, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0,7, 0x90,57, 0x91,57, 0,31, 0x92,48, 0x93,48, 
0,47, 0x94,53, 0x95,53, 3,197, 0x90,57, 0x91,57, 3,152, 0,47, 0,15, 0x90,59, 0x91,59, 0x82, 0x83, 0x84, 0x85, 
0,31, 0x92,52, 0x93,52, 0,47, 0x94,56, 0x95,56, 7,89, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0,7, 0x90,45, 0x91,45, 
4,21, 0x92,52, 0x93,52, 3,216, 0x90,53, 0x91,53, 0x92,41, 0x93,41, 0x94,45, 0x95,45, 7,103, 0x82, 0x83, 0,8, 
0x92,41, 0x93,41, 0,39, 0x84, 0x85, 0,8, 0x94,45, 0x95,45, 0,8, 0x80, 0x81, 0,7, 0x90,59, 0x91,59, 0,31, 
0,47, 2,98, 0x80, 0x81, 0,30, 0x90,57, 0x91,57, 1,39, 0x80, 0x81, 0,30, 0x90,53, 0x91,53, 3,216, 0x90,52, 
0x91,52, 0x92,40, 0x93,40, 0x94,45, 0x95,45, 5,241, 0x80, 0x81, 1,183, 0x82, 0x83, 0x84, 0x85, 0xf0};*/
// This score contains 801 bytes, and 6 tone generators are used.
// 36 notes had to be skipped.

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
