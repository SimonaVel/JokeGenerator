# A dad joke genereator

## An interactive joke generator with a physical button for going to the next joke.

This project was created in the spring of 2024 for an Interactive Digital systems course at Roskilde university. The aim was to create a project that uses at least 2 novel inputs and/or networking. The program includes both.

### Hardware needed:
1. ESP32 microcontroller
2. USB cable
3. Breadboard
4. Jumper wires
5. LCD
6. Button

## How to set this project up:
### I. Hardware part
    1. Connect the parts as follows:\
    ![image](https://github.com/pren0Sima/JokeGenerator/assets/108150997/96825c4c-3eb1-407b-a098-a7b4e84b0486)

### II. Software part
    1. Download the code\
    2. Create a hotspot\
    3. Change the credentials in the program with yours\
    4. Upload the code onto the ESP23 using an Arduino IDE\
    5. Copy the IP address in the Serial monitor screen and paste it into a browser

### III. Human part
    1. Refresh the page\
    2. Press the button\
    3. Laugh!

### Known issues:
1. The formatting of the jokes is sometimes funny.
2. Unsecure
3. The refresh button has to be pressed every time before pressing the button in order for a joke to be displayed.

### Credits:
This project was made possible with the kind assistance of Keith Lim (keithl@ruc.dk) and the following tutorial websites:
1) https://randomnerdtutorials.com/ 
2) https://learn.hobye.dk/

The jokes are fetched from the following API:
https://v2.jokeapi.dev/joke/Any?safe-mode 
