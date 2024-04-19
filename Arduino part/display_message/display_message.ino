#include <LiquidCrystal_I2C.h>
// Load Wi-Fi library
#include <WiFi.h>
// for the API
#include <HTTPClient.h>

// GLOBAL VARIABLES:
// for the button:
int BUTTON_PIN = 17;         // Define the pin for the pushbutton
// for the Wi-Fi
// Set web server port number to 80
WiFiServer server(80);
// for the jokes
char* jokeAPI = "https://v2.jokeapi.dev/joke/Any?safe-mode";


// It sets up a button on the breadboard
void setUpButton(int button_value = 17) {
  BUTTON_PIN = button_value;         // Define the pin for the pushbutton
  pinMode(BUTTON_PIN, INPUT_PULLUP);   // Initialize pushbutton pin as an input with internal pull-up resistor
}
// displays a message on a LCD
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
  lcd.print("Press the button");
  lcd.setCursor(0, 1);
  lcd.print("   for a joke");
}

// Connects to Wi-Fi network with SSID and password
void connectToWifi(char* name, char* pass) {
  Serial.print("Connecting to ");
  Serial.println(name);
  WiFi.begin(name, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("Connecting to Wi-Fi.");
  }
  Serial.println("\nConnected to Wi-Fi");
   // Print local IP address and start web server
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

// Fetches json data from an API
String getDataFromAPI(char* jokeAPI) {
  HTTPClient http;
  Serial.print("Sending HTTP GET request to API: ");
  Serial.println(jokeAPI);

  if (http.begin(jokeAPI)) {
    int httpCode = http.GET();
    if (httpCode > 0) {
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        // Parse JSON response
        // Example: Assuming the JSON response is {"type": "single", "joke": "This is a joke"}
        // You need to parse this JSON and extract the relevant data
        // Then, print or do whatever you want with the joke data
        // Serial.println(payload);
        return payload;
      }
    } else {
      Serial.printf("HTTP GET failed, error: %s\n", http.errorToString(httpCode).c_str());
      return "";
    }
    http.end();
  } else {
    Serial.println("Unable to connect to server");
    return "";
  }
}

String extractJoke(String json) {
  int start;
  int end;
  String extractedJoke;
  if((start = json.indexOf("\"type\": \"twopart\"")) != -1) {
    start = json.indexOf("\"setup\": \"") + 10;
    end = json.indexOf("\"flags\": {") - 7;
    extractedJoke = json.substring(start, end);
    extractedJoke.replace("    \"delivery\": \"", "");
    extractedJoke.replace("\",", "");
    return extractedJoke;
  }
  else if(json.indexOf("\"type\": \"single\"") != -1) {
    start = json.indexOf("\"joke\": \"") + 9;
    end = json.indexOf("\"flags\"") - 7;
    return json.substring(start, end);
  }
  else return json;
}

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("Before setting up the display.");
  setUpDisplayMessage();
  Serial.println("Display set up.");
  Serial.println("Setting up the button.");
  setUpButton(17);
  connectToWifi("Simona's Galaxy A51", "nnal8860");
}


void loop() {
  int buttonState = HIGH;      // Initialize button state
  int lastButtonState = HIGH;  // Initialize last button state
  // Read the current state of the pushbutton
  buttonState = digitalRead(BUTTON_PIN);
  // if the button is pressed and its previous state was HIGH
  if (buttonState == LOW && lastButtonState == HIGH) {  // Check if the button state has changed from HIGH to LOW (button pressed)
    Serial.println("Button pressed and now fetching joke...");
    delay(500);
    Serial.println(extractJoke(getDataFromAPI(jokeAPI)));
  }
}