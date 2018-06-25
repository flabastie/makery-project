/*
  air_quality_box_v2
  
*/

#include "Arduino.h"
#include <FastLED.h>
#include "led_rgb.cpp"

#define LED_PIN     6
#define NUM_LEDS    12
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB

#define UPDATES_PER_SECOND 100

CRGB leds[NUM_LEDS];
CRGBPalette16 currentPalette;
TBlendType    currentBlending;
extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

#include "led_circle.cpp"

const int pinLed = 13;

// led rgb
int pinLed_rgb_blue   = 9;
int pinLed_rgb_green  = 10;
int pinLed_rgb_red    = 11;

void setup() {
  // initialize digital pin pinLed as an output.
  pinMode(pinLed_rgb_blue, OUTPUT);
  pinMode(pinLed_rgb_green, OUTPUT);
  pinMode(pinLed_rgb_red, OUTPUT); 
  pinMode(pinLed, OUTPUT);
}

void loop() {
  digitalWrite(pinLed, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(pinLed, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second

/*
  setColor(255, 0, 0, pinLed_rgb_blue, pinLed_rgb_green, pinLed_rgb_red);  // red
  delay(1000);
  setColor(0, 255, 0, pinLed_rgb_blue, pinLed_rgb_green, pinLed_rgb_red);  // green
  delay(1000);
  setColor(0, 0, 255, pinLed_rgb_blue, pinLed_rgb_green, pinLed_rgb_red);  // blue
  delay(1000);
  setColor(255, 255, 0, pinLed_rgb_blue, pinLed_rgb_green, pinLed_rgb_red);  // yellow
  delay(1000);  
  setColor(80, 0, 80, pinLed_rgb_blue, pinLed_rgb_green, pinLed_rgb_red);  // purple
  delay(1000);
  setColor(0, 255, 255, pinLed_rgb_blue, pinLed_rgb_green, pinLed_rgb_red);  // aqua
  delay(1000);
*/
}
