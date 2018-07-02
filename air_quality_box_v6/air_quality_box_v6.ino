#include <FastLED.h>
#include"AirQuality.h"
#include"Arduino.h"
#include <Wire.h>
#include "rgb_lcd.h"
#include "pitches.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1024.6)

Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

// pins
const int pinBuzzer         = 4;
const int pinLed_circle     = 6;
const int pinLed_rgb_blue   = 9;
const int pinLed_rgb_green  = 5;
const int pinLed_rgb_red    = 3;
//const int pinLed_white      = 13;

// timer
int ledState = LOW;
unsigned long previousMillis = 0;
unsigned long previousMillis2 = 0;
const long interval = 1000;   
const long interval2 = 2000;         

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

// variables barometre
float temperature;
float pressure;
float altitude;
float humidity;


/*
 * function setup()
 */

void setup() {
  // led rgb
  pinMode(pinLed_rgb_blue, OUTPUT);
  pinMode(pinLed_rgb_green, OUTPUT);
  pinMode(pinLed_rgb_red, OUTPUT);
  //pinMode(pinLed_white, OUTPUT);

  //digitalWrite(pinLed_white, LOW);
  //analogWrite(pinLed_rgb_blue, 255);

  // barometer
  bme.begin();

    lcd.begin(16, 2);
    // ouleur fond d'écran
    lcd.setRGB(255, 255, 255); 
    Serial.begin(9600);
    // affichage starting
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Starting ...");
    // air qulity init
    //airqualitysensor.init(14);
  
    delay( 2000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, pinLed_circle, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;

    // air quality sensor
    //current_quality=airqualitysensor.slope();

  // air sensor

  /*if (current_quality >= 0)// if a valid data returned.
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
    */

    // end air sensor
    buzzer_fn();
    //analogWrite(pinLed_rgb_blue, 0);

}

/*
 * function loop()
 */

void loop()
{

    ChangePalettePeriodically();
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; 
    FillLEDsFromPaletteColors( startIndex);
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);

    // 
    temperature = bme.readTemperature();
    pressure = bme.readPressure() / 100.0F;
    altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
    humidity = bme.readHumidity();

    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
          previousMillis = currentMillis;
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print(bme.readTemperature());  
          lcd.print(" deg"); 
          lcd.setCursor(0,1);
          lcd.print(bme.readPressure() / 100.0F);
          lcd.print(" hPa");
    }

/*
    if (currentMillis - previousMillis2 >= interval2) {
          previousMillis2 = currentMillis;
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print(bme.readAltitude(SEALEVELPRESSURE_HPA));  
          lcd.print(" m"); 
          lcd.setCursor(0,1);
          lcd.print(bme.readHumidity());
          lcd.print(" %");
    }
*/
/*
    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" *C");

    Serial.print("Pression = ");

    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Altitude = ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");

    Serial.print("Humidite = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");

    Serial.println();

    delay (1000);
*/
  analogWrite(pinLed_rgb_red, 255);
}


