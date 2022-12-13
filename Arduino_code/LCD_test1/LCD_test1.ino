// Last Update: the display is working with A4 and A5. Iterating display works and clearning only a single line works.

#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int i = 0;

// lcd initialization
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
//  lcd.begin(16, 02);
  lcd.init();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.setBacklight(HIGH);
  lcd.print("Testing:");
}

void loop() {
  clearLine(1);
  lcd.setCursor(0,1);
  i = i + 1;
  lcd.print(i);
  delay(500);
}

void clearLine(int l){
  lcd.setCursor(0,l);
  for (int i=0;i<16;i++){
    lcd.print(" ");
  }
}
