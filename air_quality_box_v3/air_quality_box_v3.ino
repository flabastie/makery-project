/*
  Blink

  test_led_13
  
*/
#include <FastLED.h>
const int pinLed = 13;

void setup() {
  // initialize digital pin pinLed as an output.
  pinMode(pinLed, OUTPUT);

  // ledcircle
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;
}

void loop() {
  digitalWrite(pinLed, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(pinLed, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second

  // ledcircle
    ChangePalettePeriodically();
    
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    
    FillLEDsFromPaletteColors( startIndex);
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}
