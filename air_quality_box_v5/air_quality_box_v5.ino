#include <FastLED.h>
#include"AirQuality.h"
#include"Arduino.h"
#include <Wire.h>
#include "rgb_lcd.h"
#include "pitches.h"

// led rgb
const int pinLed_rgb_blue   = 9;
const int pinLed_rgb_green  = 10;
const int pinLed_rgb_red    = 11;

// timer
int ledState = LOW;
unsigned long previousMillis = 0;
const long interval = 1000;           

#define LED_PIN     6
#define NUM_LEDS    12
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

// air qulity sensor
AirQuality airqualitysensor;
int current_quality =-1;

// LCD.
rgb_lcd lcd;

// led rgb
int brightness = 0;
int fadeAmount = 5;

// buzzer
const int pinBuzzer = 5;

/*
 * function setup()
 */

void setup() {
  // led rgb
  pinMode(pinLed_rgb_blue, OUTPUT);
  pinMode(pinLed_rgb_green, OUTPUT);
  pinMode(pinLed_rgb_red, OUTPUT);

  analogWrite(pinLed_rgb_blue, 255);

  // buzzer
  //pt.tune_initchan (pinBuzzer); 

    lcd.begin(16, 2);
    // ouleur fond d'écran
    lcd.setRGB(255, 255, 255); 
    Serial.begin(9600);
    // affichage starting
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Starting ...");
    // air qulity init
    airqualitysensor.init(14);
  
    delay( 2000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;

    // air quality sensor
    current_quality=airqualitysensor.slope();

  // air sensor

  if (current_quality >= 0)// if a valid data returned.
    {
        if (current_quality==0)
        {
          Serial.println("High pollution! Force signal active");
          // message sur LCD
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Haute pollution!");
          lcd.setCursor(0,1);
          lcd.print("Alerte!"); 
        }
        else if (current_quality==1)
        {
          Serial.println("High pollution!");
          // message sur LCD
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Haute pollution!");
          lcd.setCursor(0,1);
          lcd.print("Danger!");
        }   
        else if (current_quality==2){
          Serial.println("Low pollution!");
          // message sur LCD
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Basse pollution!");  
          lcd.setCursor(0,1);
          lcd.print("Attention!");
        }  
        else if (current_quality ==3)
        {
          Serial.println("Fresh air");
          // message sur LCD
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Air frais");  
          lcd.setCursor(0,1);
          lcd.print("Respirez ;)");  
        }
            
    }

    // end air sensor
    buzzer_fn();
    analogWrite(pinLed_rgb_blue, 0);

}

/*
 * function loop()
 */

void loop()
{

  // blink without delay
  //unsigned long currentMillis = millis();

 /* if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
      setColor(255, 0, 0, pinLed_rgb_red, pinLed_rgb_green, pinLed_rgb_blue);  // red
    } else {
      ledState = LOW;
      setColor(0, 0, 255, pinLed_rgb_red, pinLed_rgb_green, pinLed_rgb_blue);  // blue
    }

    // set the LED with the ledState of the variable:
    //digitalWrite(ledPin, ledState);
  }*/
  // end blink without delay


    ChangePalettePeriodically();
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; 
    FillLEDsFromPaletteColors( startIndex);
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
  

  // led

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);

  // set the brightness of pin 9:
  analogWrite(pinLed_rgb_red, brightness);

  // end led
 
}


