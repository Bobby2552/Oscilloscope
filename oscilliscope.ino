#include <SPI.h>
#include "PCD8544_SPI.h"

PCD8544_SPI_FB lcd;

int buttonPin = 0;
int backlightPin = 12;

void setup(void) {
   lcd.begin();
   lcd.println("Oscilliscope  ");
   lcd.println("Ben Scholer,  2015");
   lcd.renderAll();
   delay(1000);
   pinMode(buttonPin, INPUT);
   pinMode(backlightPin, OUTPUT);
}

void loop() {
  
  if (digitalRead(buttonPin) == HIGH) {
    digitalWrite(backlightPin, HIGH);
  }
  
  lcd.clear();
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < PCD8544_Y_PIXELS; j += 9) {
      lcd.setPixel(i, j, 1);
    }
  }
  //uint8_t values[PCD8544_X_PIXELS];
  for (int i = 0; i < 84; i++) {
    float val = analogRead(5);
    float voltage = val * (5.0 / 1023.0);
    float co = voltage / 5.0;
    uint8_t px = 48 - (co * 48);
    
    lcd.setPixel(i, px, 1);
    //delayMicroseconds(25);
  }
  lcd.renderAll();
  delay(100);
}
