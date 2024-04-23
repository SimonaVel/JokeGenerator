let jokeAPI = "https://v2.jokeapi.dev/joke/Any?safe-mode";
let response;
let jsonData;
let joke;

/*
Important:
if we have a two-part joke => type = twopart
if we have a one-part joke => type = single
*/
async function getDataFromAPI(){
// GET request (?var = ...)
   response = await fetch(jokeAPI);
   jsonData = await response.json();
   if (jsonData.type == "single"){
       console.log(jsonData.joke);
       joke = jsonData.joke;
   }
   else if (jsonData.type == "twopart"){
       console.log(jsonData.setup);
       console.log(jsonData.delivery);
       joke = jsonData.setup + "\n" + jsonData.delivery;
   }
}
function setup() {
   createCanvas(windowWidth, windowHeight);
   getDataFromAPI();
}
function draw() {
  // takes the category of the joke and puts a fitting background from a different API
   background(255, 220, 255);
   textAlign(CENTER, CENTER);
   // the text needs to be allowed to be copied
   text(joke, windowWidth/2, windowHeight/2);
   textFont("Georgia");
   textSize(20);
   // a button - when it's pressed, the joke will be updated
    button = createButton('Next joke?');
    button.style('font-size', '20px');
    button.style('background-color', 'white');
    button.position(windowWidth/2, windowHeight/2 + 100);
    button.mousePressed(getDataFromAPI);
}




