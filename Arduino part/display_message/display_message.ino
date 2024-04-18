/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#include <LiquidCrystal_I2C.h>
// global variables:
// for the button:
int LED_PIN = LED_BUILTIN;  // Use the built-in LED pin
int BUTTON_PIN = 17;         // Define the pin for the pushbutton


void setUpButton(int button_value = 17) {
  BUTTON_PIN = button_value;         // Define the pin for the pushbutton

  pinMode(BUTTON_PIN, INPUT_PULLUP);   // Initialize pushbutton pin as an input with internal pull-up resistor
}

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
  Serial.begin(9600);
  delay(1000);
  Serial.println("Before setting up the display.");

  setUpDisplayMessage();
  Serial.println("Display set up.");

  Serial.println("Setting up the button.");
  setUpButton(17);
}

void loop(){
  int buttonState = HIGH;      // Initialize button state
  int lastButtonState = HIGH;  // Initialize last button state
  // Read the current state of the pushbutton
  buttonState = digitalRead(BUTTON_PIN);
  // if the button is pressed and its previous state was HIGH
  if (buttonState == LOW && lastButtonState == HIGH) {  // Check if the button state has changed from HIGH to LOW (button pressed)
    Serial.println("Button pressed");
    delay(500);
  }
}