#define led_pin 2
#include <WiFi.h>
bool led_state = true;

void setup() {
  pinMode(led_pin,OUTPUT);
  WiFiServer server(80);
  

}

void loop() {
  if (led_state == true)
  {
    led_state = false;
  }
  else if(led_state == false)
  {
    led_state = true;
  }
  digitalWrite(led_pin,led_state);

  delay(1000);

}
