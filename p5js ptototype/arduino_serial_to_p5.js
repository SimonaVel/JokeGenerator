let serialAvaliable = false;

let serialInput = "";



function setup() {

  createCanvas(400, 400);

  print("press c to connect")

}



function keyPressed() {

  if (key == "c") {

    serialConnect();

  }

}



var timer = 0;

function draw() {

  background(220);



  // prints the serial input buffer when the serialAvaliable flag is true

  if (serialAvaliable) {

    serialAvaliable = false;

    print(serialInput);

    serialInput = "";

  }

  

  //Send a hello to the arduino every 3 seconds 

  //- if it shows up in the console it means that the arduino returned it



  if (millis() - timer > 3000) {

    timer = millis();

    serialWrite("hello from p5");

  }

}







// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

// SERIAL COMMUNICATION FUNCTIONS BELOW

// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

let port;

let reader;

let inputDone;

let outputDone;

let inputStream;

let outputStream;

let portIsOpen = false;



async function serialListen() {

  if (portIsOpen) {

    while (true) {

      const { value, done } = await reader.read();



      if (value) {

        serialAvaliable = true;

        serialInput = serialInput + value;

      }

      if (done) {

        console.log("[readLoop] DONE", done);

        reader.releaseLock();

        break;

      }

    }

  }

}

async function serialConnect() {

  if (navigator.serial) {

    port = await navigator.serial.requestPort();

    await port.open({ baudRate: 9600 });



    const decoder = new TextDecoderStream();

    inputStream = decoder.readable;

    inputDone = port.readable.pipeTo(decoder.writable);

    reader = inputStream.getReader();



    const encoder = new TextEncoderStream();

    outputDone = encoder.readable.pipeTo(port.writable);

    outputStream = encoder.writable;



    portIsOpen = true;

    print("Port is open");

    serialListen();

  } else {

    print("Serial not compatible with the browser you are using :/");

  }

}



function serialWrite(line) {

  if (portIsOpen) {

    // CODELAB: Write to output stream

    const writer = outputStream.getWriter();



    writer.write(line);



    writer.releaseLock();

  }

}