let cryptoCurrenciesAPI = "https://api.coinlore.net/api/tickers/";
let cryptoCurrencyAPI = "https://api.coinlore.net/api/ticker/";
let response;
let wholeJsonData;
let singularJsonData;
let priceUSD;
let currencyName = "Ethereum";

async function getDataFromAPI(){
  response = await fetch(cryptoCurrenciesAPI);
  wholeJsonData = await response.json();
  console.log(wholeJsonData);
  
  // get specific one
  wholeJsonData.data.forEach((obj) => {
     if(obj.name == currencyName){
       singularJsonData = obj;
       console.log("Currency name:", obj.name);
       console.log("Price in USD:", obj.price_usd);
     }
 });
}

function setup() {
  console.log("Programme is running.");

  createCanvas(400, 400);
  console.log(exampleObj.number);
  console.log(exampleObj.arrayURL[1]);
  
  getDataFromAPI();
  
}

function draw() {
  background(220);
  text("syncronous", 50, 10);
  text(currencyName, 50, 200);
  text(priceUSD, 50, 250);
}

