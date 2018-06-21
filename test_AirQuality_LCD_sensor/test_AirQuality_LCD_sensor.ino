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

// air qulity sensor
AirQuality airqualitysensor;
int current_quality =-1;

// on déclare notre LCD.
rgb_lcd lcd;

void setup()
{
    // On déclare nombre de colonnes et de lignes
    lcd.begin(16, 2);
    // On choisit couleur fond d'écran
    lcd.setRGB(255, 255, 255); 
    // initialize the serial communications:
    Serial.begin(9600);
    // affichage starting
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Starting ...");
    // air qulity init
    airqualitysensor.init(14);
}

void loop()
{
    // air qulity sensor
    current_quality=airqualitysensor.slope();
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
            
    }

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
