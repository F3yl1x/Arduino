
//Fabios automatische Bewässerung


// Import required libraries
#include "WiFi.h"
#include "ESPAsyncWebServer.h"

// Replace with your network credentials
const char* ssid = "WLAN-PK";
const char* password = "Sonyta+Felixx";

const int humidityPin = 35;
const int PumpenPin = 27;


//Bewässerungsvariablen
const int bewaesserungszeit = 2000;
const int bewaesserungsschwelle = 1000;
const int messintervall = 3000;
const int mittelwertsZeit = 15000;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String readValue()
{
  int value = analogRead(humidityPin);
  return String(value);
}

String readPercent()
{
  int value = analogRead(humidityPin);
  return(String(100-((value*100)/4096)));
}

const char index_html[] PROGMEM = R"rawliteral(

<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .dht-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
  </style>
</head>
<body>
  <h2>ESP32 Automatische Pflanzenbewaesserung</h2>
  <p>
    <i class="fas fa-tint" style="color:#00add6;"></i>  
    <span class="dht-labels">Absolutwert: </span> 
    <span id="value ">%value%</span>
  </p>
  <p>
    <i class="fas fa-tint" style="color:#00add6;"></i> 
    <span class="dht-labels">Feuchtigkeit: </span>
    <span id="percent ">%percent%</span>
    <sup class="units">&percnt;</sup>
  </p>
</body>
</html>

)rawliteral";

// Replaces placeholder with values
String processor(const String& var){
  if(var == "value"){
    return readValue();
  }
  else if(var == "percent"){
    return readPercent();
  }
  return String();
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(9600);
  pinMode(PumpenPin,OUTPUT);
  digitalWrite(PumpenPin,LOW);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/value", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readValue().c_str());
  });
  server.on("/percent", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readPercent().c_str());
  });

  // Start server
  server.begin();
}

//Zeitmerker
unsigned long mittelwertMerker = 0;
unsigned long vergleichMerker = 0;

//Wertmerker
int mittelwert = 0;
 
void loop(){

  if(millis() > mittelwertMerker + messintervall)
  {
    mittelwert = mittelwert + analogRead(humidityPin);
    mittelwertMerker = millis();
  }

  if(millis() > vergleichMerker + mittelwertsZeit)
  {
    if(mittelwert >= (bewaesserungsschwelle * (mittelwertsZeit/messintervall)))
    {
      digitalWrite(PumpenPin,HIGH);
      delay(bewaesserungszeit);
      digitalWrite(PumpenPin,LOW);
    }
    mittelwert = 0;
    vergleichMerker = millis();
  }
}