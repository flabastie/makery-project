/*
  AirQuality Demo V1.0.
  connect to A0 to start testing. it will needs about 20s to start 
* By: http://www.seeedstudio.com
*/

// air quality library
#include"AirQuality.h"
#include"Arduino.h"

// On inclut les librairies I2C et LCD
#include <Wire.h>
#include "rgb_lcd.h"

#include <Playtune.h>

//------------------------------------------------
//   scores are put in program space memory
//------------------------------------------------

// Playtune bytestream for file "Truman_Sleeps_-_Philip_Glass.mid" created by MIDITONES V1.16 on Mon Jun 18 23:20:36 2018
// command line: ./miditones.exe Truman_Sleeps_-_Philip_Glass 
const unsigned char PROGMEM score [] = {
0x90,53, 0,253, 0x80, 0,14, 0x90,56, 0,253, 0x80, 0,14, 0x90,60, 0,253, 0x80, 0,14, 0x90,53, 0,253, 0x80, 
0,14, 0x90,56, 0,253, 0x80, 0,14, 0x90,60, 0,253, 0x80, 0,14, 0x90,53, 0,253, 0x80, 0,14, 0x90,56, 0,253, 
0x80, 0,14, 0x90,53, 0,253, 0x80, 0,14, 0x90,56, 0,253, 0x80, 0,14, 0x90,61, 0,253, 0x80, 0,14, 0x90,53, 
0,253, 0x80, 0,14, 0x90,56, 0,253, 0x80, 0,14, 0x90,61, 0,253, 0x80, 0,14, 0x90,53, 0,253, 0x80, 0,14, 
0x90,56, 0,253, 0x80, 0,14, 0x90,51, 0,253, 0x80, 0,14, 0x90,56, 0,253, 0x80, 0,14, 0x90,60, 0,253, 0x80, 
0,14, 0x90,51, 0,253, 0x80, 0,14, 0x90,56, 0,253, 0x80, 0,14, 0x90,60, 0,253, 0x80, 0,14, 0x90,51, 0,253, 
0x80, 0,14, 0x90,56, 0,253, 0x80, 0,14, 0x90,52, 0,253, 0x80, 0,14, 0x90,55, 0,253, 0x80, 0,14, 0x90,60, 
0,253, 0x80, 0,14, 0x90,52, 0,253, 0x80, 0,14, 0x90,55, 0,253, 0x80, 0,14, 0x90,60, 0,253, 0x80, 0,14, 
0x90,52, 0,253, 0x80, 0,14, 0x90,55, 0,253, 0x80, 0,14, 0x90,53, 0,253, 0x80, 0,14, 0x90,56, 0,253, 0x80, 
0,14, 0x90,60, 0,253, 0x80, 0,14, 0x90,53, 0,253, 0x80, 0,14, 0x90,56, 0,253, 0x80, 0,14, 0x90,60, 0,253
};
// This score contains 3488 bytes, and 6 tone generators are used.

// playtune
Playtune pt;

// air qulity sensor
AirQuality airqualitysensor;
int current_quality =-1;

// on déclare notre LCD.
rgb_lcd lcd;

// définition des pin pour le KY040
enum PinAssignments {
  encoderPinA = 2,   // right (DT)
  encoderPinB = 3,   // left (CLK)
  clearButton = 4    // switch (SW)
};

volatile unsigned int encoderPos = 0;  // un compteur
unsigned int lastReportedPos = 1;   // gestion du changement
static boolean rotating=false;      // gestion de l'anti-rebonds

// variable pour les routines d'interruption
boolean A_set = false;              
boolean B_set = false;
boolean A_change = false;
boolean B_change= false;



void setup()
{
    //buzzer_fn();

    pt.tune_initchan (5); 
    pt.tune_initchan (6);
    pt.tune_initchan (7);
  
    // On déclare nombre de colonnes et de lignes
    lcd.begin(16, 2);
    // On choisit couleur fond d'écran
    lcd.setRGB(255, 255, 255); 
    // initialize the serial communications:

    lcd.begin(20,4);
    lcd.clear();
  
    pinMode(encoderPinA, INPUT_PULLUP); // utilisation du pullup
    pinMode(encoderPinB, INPUT_PULLUP); // utilisation du pullup
    pinMode(clearButton, INPUT_PULLUP); // utilisation du pullup
    // activation de l'interruption 0 (pin 2)
    attachInterrupt(0, doEncoderA, CHANGE);
    // activation de l'interruption 1 (pin 3)
    attachInterrupt(1, doEncoderB, CHANGE);

    Serial.begin(9600);
    // air qulity init
    airqualitysensor.init(14);
}

void loop()
{

//  pt.tune_playscore (score); /* start playing */
//  while (pt.tune_playing) ; /* wait here until playing stops */
//  pt.tune_delay(1000); /* wait a second */


  if (lastReportedPos != encoderPos) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Index: ");
    lcd.print(encoderPos, DEC);
    lastReportedPos = encoderPos;
    lcd.setCursor(0,1);
    lcd.print(digitalRead(encoderPinA));
    lcd.print(digitalRead(encoderPinB));
    lcd.print(digitalRead(clearButton));
  }
    lcd.setCursor(0,1);
    lcd.print(digitalRead(encoderPinA));
    lcd.print(digitalRead(encoderPinB));
    lcd.print(digitalRead(clearButton));
    
  if (digitalRead(clearButton) == LOW )  {
    encoderPos = 0;
    A_change = false;
    B_change= false;
    lcd.print(encoderPos);
  }

  delay (100);

  
    // air qulity sensor
 /*   current_quality=airqualitysensor.slope();
    if (current_quality >= 0)// if a valid data returned.
    {
        if (current_quality==0)
        {
          Serial.println("High pollution! Force signal active");
          // message sur LCD
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("High pollution! Force signal active");
        }
        else if (current_quality==1)
        {
          Serial.println("High pollution!");
          // message sur LCD
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("High pollution!");
        }   
        else if (current_quality==2){
          Serial.println("Low pollution!");
          // message sur LCD
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Low pollution!");  
        }  
        else if (current_quality ==3)
        {
          Serial.println("Fresh air");
          // message sur LCD
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Fresh air");  
        }
            
    }*/

}

ISR(TIMER1_OVF_vect)
{
	if(airqualitysensor.counter==61)//set 2 seconds as a detected duty
	{

			airqualitysensor.last_vol=airqualitysensor.first_vol;
			airqualitysensor.first_vol=analogRead(A0);
			airqualitysensor.counter=0;
			airqualitysensor.timer_index=1;
			PORTB=PORTB^0x20;
	}
	else
	{
		airqualitysensor.counter++;
	}
}
