/*
 * led_rgb
 */

void setColor(int red, int green, int blue, int pinLed_rgb_red, int pinLed_rgb_green, int pinLed_rgb_blue)
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
