


// On inclut les librairies I2C et LCD
#include <Wire.h>
#include "rgb_lcd.h"

// on déclare notre LCD.
rgb_lcd lcd;

void setup() {
    // On déclare le nombre de colonnes et de lignes
    lcd.begin(16, 2);
    // On choisit une couleur magnifique pour le fond d'écran
    lcd.setRGB(0, 255, 255);    
    
}

void loop() {

    lcd.clear();
    lcd.setRGB(255, 0, 0);
    lcd.setCursor(0,0);
    lcd.print("Pollution"); 
    lcd.setCursor(0,1);
    lcd.print("Alarmante!");  
    delay (3000);
}

