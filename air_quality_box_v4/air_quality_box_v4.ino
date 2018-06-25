#include <FastLED.h>

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

// constants won't change. Used here to set a pin number:
const int ledPin =  LED_BUILTIN;// the number of the LED pin

// Variables will change:
int ledState = LOW;             // ledState used to set the LED

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 1000;           // interval at which to blink (milliseconds)


// led rgb
const int pinLed_rgb_blue   = 9;
const int pinLed_rgb_green  = 10;
const int pinLed_rgb_red    = 11;

/*
 * function setup()
 */

void setup() {
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);
  // led rgb
  pinMode(pinLed_rgb_blue, OUTPUT);
  pinMode(pinLed_rgb_green, OUTPUT);
  pinMode(pinLed_rgb_red, OUTPUT); 

  // led circle
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;
}

/*
 * function loop()
 */

void loop() {
  // blink without delay
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
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
  }

    // ledcircle
    ChangePalettePeriodically();
    
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    
    FillLEDsFromPaletteColors( startIndex);
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}








