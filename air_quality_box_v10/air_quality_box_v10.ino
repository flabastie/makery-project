#include <FastLED.h>
#include"AirQuality.h"
#include"Arduino.h"
#include <Wire.h>
#include "rgb_lcd.h"
#include "pitches.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "Timer.h"

// pins
#define PIN_BUZZER 4
#define PIN_LED_CIRCLE 6
#define PIN_RGB_RED 3
#define PIN_RGB_GREEN 5
#define PIN_RGB_BLUE 9
#define PIN_LED_WHITE 8
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define PIN_AIR_QUALITY A0
#define PIN_POTENTIOMETER A1
#define PIN_SOUND A2

#define SEALEVELPRESSURE_HPA (1024.6)
Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

// timer lcd
unsigned long previousMillis = 0;
const long interval = 3000;  
int counter = 1;
#define COUNTER_MAX 3    

// timer sound sensor
unsigned long previousMillisSoundSensor = 0;
Timer t;

// alert
int alert_state = 0;
int alert_air_state = 0;

#define NUM_LEDS 12
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
int pollutionLevelCase = 0;
String air_quality_message_1 = "";
String air_quality_message_2 = "";
#define AIR_LEVEL_01 "Pollution"
#define AIR_LEVEL_02 "Alarmante !"
#define AIR_LEVEL_11 "Forte pollution!"
#define AIR_LEVEL_12 "Danger!"
#define AIR_LEVEL_21 "Faible pollution!"
#define AIR_LEVEL_22 "Attention!"
#define AIR_LEVEL_31 "Air frais"
#define AIR_LEVEL_32 "Respirez ;)"

int sound_level = 0;
int potentiometer_level = 0;
int led_white_state = 0;

/*
 * function setup()
 */

void setup() {
  Serial.begin(9600);
  
  // led rgb
  pinMode(PIN_RGB_BLUE,  OUTPUT);
  pinMode(PIN_RGB_GREEN, OUTPUT);
  pinMode(PIN_RGB_RED,   OUTPUT);
  pinMode(PIN_LED_WHITE, OUTPUT);

  // barometer
  bme.begin();

    lcd.begin(16, 2);
    // couleur fond d'écran
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
    //buzzer_start();
    buzzer_fresh();
}

/*
 * function loop()
 */

void loop()
{

  // update timer
  t.update();

  // air quality sensor
  current_quality=airqualitysensor.slope();

  if (current_quality >= 0)// if a valid data returned.
    {
        // haute pollution alerte
        if (current_quality==0)
        {
          pollutionLevelCase = 0;
          air_quality_message_1 = AIR_LEVEL_01;
          air_quality_message_2 = AIR_LEVEL_02;      
        }
        // haute pollution danger
        else if (current_quality==1)
        {
          pollutionLevelCase = 1;
          air_quality_message_1 = AIR_LEVEL_11;
          air_quality_message_2 = AIR_LEVEL_12;
        }   
        // faible pollution
        else if (current_quality==2){
          pollutionLevelCase = 2;
          air_quality_message_1 = AIR_LEVEL_21;
          air_quality_message_2 = AIR_LEVEL_22;
        }  
        // air frais
        else if (current_quality ==3)
        {  
          pollutionLevelCase = 3;
          air_quality_message_1 = AIR_LEVEL_31;
          air_quality_message_2 = AIR_LEVEL_32;
        }     
    }

    // led circle
    if(pollutionLevelCase == 0 || pollutionLevelCase == 1 || pollutionLevelCase == 2){
      LedCirclePulse();
    }
    else{
      ChangePalettePeriodically();
    }  
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; 
    FillLEDsFromPaletteColors( startIndex);
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);

    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
          previousMillis = currentMillis;
          Serial.println(counter);
          setLCD_color(pollutionLevelCase);

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
          /*Serial.print("Temperature = ");
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
          */
    }

    // sound sensor
    sound_sensor();
}

/*
 * setLCD_color()
 */

void setLCD_color(int pollutionLevelCase){
  switch (pollutionLevelCase){
    case 0:
      //set backlight lcd red
      setColorRGB(255, 0, 0, PIN_RGB_RED, PIN_RGB_GREEN, PIN_RGB_BLUE);
      lcd.setRGB(255, 0, 0);
      buzzer_maxi();
      break;
    case 1:
      //set backlight lcd orange
      setColorRGB(255, 0, 0, PIN_RGB_RED, PIN_RGB_GREEN, PIN_RGB_BLUE);
      lcd.setRGB(255,70,0);
      buzzer_high();
      break;
    case 2:
      //set backlight lcd green
      setColorRGB(0, 255, 0, PIN_RGB_RED, PIN_RGB_GREEN, PIN_RGB_BLUE);
      lcd.setRGB(255, 191, 0);
      buzzer_low();
      break;
    case 3:
      //set backlight lcd blue
      lcd.setRGB(0, 100, 255);
      setColorRGB(0, 0, 255, PIN_RGB_RED, PIN_RGB_GREEN, PIN_RGB_BLUE);
      break;
    default:
      lcd.setRGB(255, 255, 255); 
  }
}
