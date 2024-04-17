/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#include <LiquidCrystal_I2C.h>

void setUpDisplayMessage() {
  // set the LCD number of columns and rows
  int lcdColumns = 16;
  int lcdRows = 2;
  // set LCD address, number of columns and rows
  // if you don't know your display address, run an I2C scanner sketch
  LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  
  // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
  // set cursor to first column, first row
  lcd.setCursor(0, 0);
  // print message
  lcd.print("Another joke?");
  lcd.setCursor(0, 1);
  lcd.print("Press the button");
}


void setup(){
  setUpDisplayMessage();
}

void loop(){
  
}