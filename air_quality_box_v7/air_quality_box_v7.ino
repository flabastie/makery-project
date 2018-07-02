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
#define PIN_BUZZER 4
#define PIN_LED_CIRCLE 6
// led RGB
const int pinLed_rgb_red    = 3;
const int pinLed_rgb_green  = 5;
const int pinLed_rgb_blue   = 9;
// led white
#define PIN_LED_WHITE 8

// timer
unsigned long previousMillis = 0;
const long interval = 3000;  
int counter = 1;
#define COUNTER_MAX 3    

#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[12];
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

// variables air quality display
String air_quality_message_1 = "";
String air_quality_message_2 = "";
#define AIR_LEVEL_01 "Pollution Maximale!"
#define AIR_LEVEL_02 "Alerte!"
#define AIR_LEVEL_11 "Haute pollution!"
#define AIR_LEVEL_12 "Danger!"
#define AIR_LEVEL_21 "Basse pollution!"
#define AIR_LEVEL_22 "Attention!"
#define AIR_LEVEL_31 "Air frais"
#define AIR_LEVEL_32 "Respirez ;)"

/*
 * function setup()
 */

void setup() {
  Serial.begin(9600);
  
  // led rgb
  pinMode(pinLed_rgb_blue,  OUTPUT);
  pinMode(pinLed_rgb_green, OUTPUT);
  pinMode(pinLed_rgb_red,   OUTPUT);
  pinMode(PIN_LED_WHITE,    OUTPUT);

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
    airqualitysensor.init(14);
  
    delay( 2000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, PIN_LED_CIRCLE, COLOR_ORDER>(leds, 12).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;

    // air quality sensor
    current_quality=airqualitysensor.slope();

    // end init air sensor
    //buzzer_fn();
}

/*
 * function loop()
 */

void loop()
{

  // air sensor

  // air quality sensor
  current_quality=airqualitysensor.slope();

  lcd.setRGB(0, 0, 255);

  if (current_quality >= 0)// if a valid data returned.
    {
        // air frais
        if (current_quality==0)
        {
          // set backlight lcd blue
          lcd.setRGB(0, 0, 255);
          air_quality_message_1 = AIR_LEVEL_01;
          air_quality_message_2 = AIR_LEVEL_02;
          analogWrite(pinLed_rgb_red, 255);
        }
        // basse pollution
        else if (current_quality==1)
        {
          // set backlight lcd green
          lcd.setRGB(255, 191, 0);
          air_quality_message_1 = AIR_LEVEL_11;
          air_quality_message_2 = AIR_LEVEL_12;
          analogWrite(pinLed_rgb_red, 255);
          buzzer_mission_fn();
        }   
        // haute pollution danger
        else if (current_quality==2){
          // set backlight lcd orange
          lcd.setRGB(255,165,0);
          air_quality_message_1 = AIR_LEVEL_21;
          air_quality_message_2 = AIR_LEVEL_22;
          analogWrite(pinLed_rgb_green, 255);
          buzzer_mission_fn();
        }  
        // haute pollution alerte
        else if (current_quality ==3)
        {  
          // set backlight lcd red
          lcd.setRGB(255, 0, 0);
          air_quality_message_1 = AIR_LEVEL_31;
          air_quality_message_2 = AIR_LEVEL_32;
          analogWrite(pinLed_rgb_red, 255);
          buzzer_mission_fn();
        }     
    }

    // led circle
    ChangePalettePeriodically();
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; 
    FillLEDsFromPaletteColors( startIndex);
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);

    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
          previousMillis = currentMillis;
          Serial.println(counter);

          switch(counter){
            case 1:
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print(bme.readTemperature());  
              lcd.print(" deg"); 
              lcd.setCursor(0,1);
              lcd.print(bme.readPressure() / 100.0F);
              lcd.print(" hPa");
              break;
            case 2:
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print(bme.readAltitude(SEALEVELPRESSURE_HPA));  
              lcd.print(" m"); 
              lcd.setCursor(0,1);
              lcd.print(bme.readHumidity());
              lcd.print(" %");
              break;
            case 3:
              lcd.clear();
              lcd.setCursor(0,0);  
              lcd.print(air_quality_message_1); 
              lcd.setCursor(0,1);
              lcd.print(air_quality_message_2);
              break;
            default:
              Serial.println("Error !");
          }

          // set counter
          counter++;
          if(counter > COUNTER_MAX){
            counter = 1;
          }

          // Serial display
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
          Serial.println(air_quality_message_1);
          Serial.println(air_quality_message_2);
          
    }
    
}


