#include <SPI.h>
#include "PCD8544_SPI.h"

PCD8544_SPI_FB lcd;

#define UPDATE_PERIOD 100

void setup(void) {
   lcd.begin();
   //Copyright crap...
   lcd.println("Oscilliscope  ");
   lcd.println("By Ben Scholer");
   lcd.renderAll();
   delay(2000);
}

void loop() {
  //Clearing copyright crap or previously drawn 'graph'
  lcd.clear();
  //Drawing 6 ticks, representing 0-5V.
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < PCD8544_Y_PIXELS; j += 9) {
      lcd.setPixel(i, j, 1);
    }
  }
  //Collecting 84 values, 1 for each pixel on the x axis of the Nokia 5110, and drawing them.
  for (int i = 0; i < 84; i++) {
    //The value read from analog pin 5, 0-1023
    float val = analogRead(5);
    //The voltage, calculated from val, given that 0 = 0V, 1023 = 5V.
    float voltage = val * (5.0 / 1023.0);
    //Coeffiecient to multiply the y pixel height to find the placement of the value.
    float co = voltage / 5.0;
    //The y value for the pixel to plot the point.
    uint8_t px = 48 - (co * 48);
    //Drawing the pixel.
    lcd.setPixel(i, px, 1);
  }
  //Rendering ticks and points.
  lcd.renderAll();
  //Delay to allow for more visible lines.
  delay(UPDATE_PERIOD);
}
