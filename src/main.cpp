// If you want to run in WOKWi
// change pin and wifi
#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Bounce2.h>
#include "traffic.h"

#define red 26
#define yellow 25
#define green 33
#define ldr 32
#define button 27

int state = 1;
int count = 0;
Bounce debouncer = Bounce();

void Connect_Wifi();

void setup()
{
  Serial.begin(115200);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(ldr, INPUT);
  debouncer.attach(button, INPUT_PULLUP);
  debouncer.interval(25);
  Connect_Wifi();

  delay(200);
  // start LED with GREEN and POST to database
  digitalWrite(green, HIGH);
  POST_traffic("green");
}

void loop()
{
  int Light = map(analogRead(ldr),0,4095,0,255);
  debouncer.update();
  // *** write your code here ***
  // Your can change everything that you want
  if (debouncer.fell()){
    state=2;
  }
  if (state == 1)
  {
    // while led GREEN
    POST_traffic("green");
    digitalWrite(red, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(green, HIGH);
    GET_traffic();
  }
  else if (state == 2)
  {
    // while led YELLOW
    POST_traffic("yellow");
    digitalWrite(green, LOW);
    digitalWrite(yellow, HIGH);
    delay(8000);
    state=3;
  }
  else if (state == 3){
    POST_traffic("red");
    digitalWrite(yellow, LOW);
    digitalWrite(red, HIGH);
    GET_traffic();
    if(Light<=110){
      state=1;
    }
  }
  Serial.println(state);
  delay(100);
}

void Connect_Wifi()
{
  const char *ssid = "TAGCH";
  const char *password = "025123301";
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.print("OK! IP=");
  Serial.println(WiFi.localIP());
  Serial.println("----------------------------------");
}
