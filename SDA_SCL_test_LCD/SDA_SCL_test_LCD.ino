


// On inclut les librairies I2C et LCD
#include <Wire.h>
#include "rgb_lcd.h"

// on déclare notre LCD.
rgb_lcd lcd;

void setup() {
    // On déclare le nombre de colonnes et de lignes
    lcd.begin(16, 2);
    // On choisit une couleur magnifique pour le fond d'écran
    lcd.setRGB(255, 255, 255);    
    
}

void loop() {
    // on place le curseur en haut à gauche
    lcd.setCursor(0,0);
    // on écrit un message
    lcd.print("un super texte");
    // on attend un peu
    delay (3000);
    
    // on "nettoie" l'écran
    lcd.clear();

    // et on écrit un autre message
    lcd.print("un autre texte");
    delay (3000);
    lcd.clear();
   
}

