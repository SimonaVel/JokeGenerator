#include <LiquidCrystal_I2C.h>
// Load Wi-Fi library for the web server
#include <WiFi.h>
// for the API
#include <HTTPClient.h>

// GLOBAL VARIABLES:
// for the button:
int BUTTON_PIN = 17;         // Define the pin for the pushbutton
// for the jokes
char* jokeAPI = "https://v2.jokeapi.dev/joke/Any?safe-mode";

// for the web server
WiFiServer server(80);
// stores the HTTP request
String header;
// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;
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
// extracts the joke from the json file
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
void loadBlankPage(WiFiClient client) {
  client.println("<!DOCTYPE html><html data-bs-theme=\"light\" lang=\"en\">");
  client.println("<head><meta charset=\"utf-8\">");
  client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, shrink-to-fit=no\">");
  client.println("<title>Joke generator!</title></head>");
  client.println("<body style=\"background: #bbdaff;\"><p style=\"font-size: 20px;\">");
  client.println("</p></body></html>");
  client.println();
}
void formHeader(WiFiClient client) {
  // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
  client.println("HTTP/1.1 200 OK");
  // and a content-type so the client knows what's coming, then a blank line:
  client.println("Content-type:text/html");
  client.println("Connection: close");
  client.println();
}
void loadPage(WiFiClient client, String joke) {
  client.println("<!DOCTYPE html><html data-bs-theme=\"light\" lang=\"en\">");
  client.println("<head><meta charset=\"utf-8\">");
  client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, shrink-to-fit=no\">");
  client.println("<title>Joke generator!</title></head>");
  client.println("<body style=\"background: #bbdaff;\"><p style=\"font-size: 20px; font-family: 'Courier New', monospace; font-weight: bold; color: #660033; text-align: center;\">");
  client.println(joke);
  client.println("</p></body></html>");
  client.println();
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
  if (buttonState == LOW && lastButtonState == HIGH) {  // Check if the button state has changed from HIGH to LOW (button pressed)
    WiFiClient client = server.available();   // Listen for incoming clients
    // if there's a setup websocket, display the joke on the browser
    if (client) {                             // If a new client connects,
      Serial.println("New Client.");          // print a message out in the serial port
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        formHeader(client);
        Serial.println("Button pressed and now fetching joke...");
        delay(250);
        String joke = extractJoke(getDataFromAPI(jokeAPI));
        Serial.println(joke);
        loadPage(client, joke);
      }
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
    }
  }
}
