/*
Adafruit Arduino - Lesson 3. RGB LED
*/
 
#define PIN_RGB_RED 3
#define PIN_RGB_GREEN 5
#define PIN_RGB_BLUE 9
 
//uncomment this line if using a Common Anode LED
//#define COMMON_ANODE
 
void setup()
{
  pinMode(PIN_RGB_RED, OUTPUT);
  pinMode(PIN_RGB_GREEN, OUTPUT);
  pinMode(PIN_RGB_BLUE, OUTPUT);  
}
 
void loop()
{
  /*setColor(255, 0, 0);  // red
  delay(1000);
  setColor(0, 255, 0);  // green
  delay(1000);
  setColor(0, 0, 255);  // blue
  delay(1000);
  setColor(255, 255, 0);  // yellow
  delay(1000);  
  setColor(80, 0, 80);  // purple
  delay(1000);
  setColor(0, 255, 255);  // aqua
  */
  setColorRGB(0, 0, 255, PIN_RGB_RED, PIN_RGB_GREEN, PIN_RGB_BLUE);
  delay(1000);
}
 
void setColorRGB(int red, int green, int blue, int pinLed_rgb_red, int pinLed_rgb_green, int pinLed_rgb_blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(pinLed_rgb_red, red);
  analogWrite(pinLed_rgb_green, green);
  analogWrite(pinLed_rgb_blue, blue);  
}
