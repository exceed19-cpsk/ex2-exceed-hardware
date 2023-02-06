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
#define ldr 34
#define button 27

#define light 1700

int state = 1;
int count = 0;
Bounce debouncer = Bounce();

void Connect_Wifi()
{
  const char *ssid = "Prae";
  const char *password = "prae0000";
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
  start LED with GREEN and POST to database
  digitalWrite(green, HIGH);
}

void loop()
{
 
    debouncer.update();
  if (state == 1)
  {
    POST_traffic("green");
    GET_traffic();
    if ( debouncer.fell() )
    {
      digitalWrite(green, LOW);
      state = 2;
    }
  }
  else if (state == 2)
  {
      POST_traffic("yellow");
      digitalWrite(yellow,HIGH);
      delay(8000);
      state = 3;

  }
  else if (state == 3)
  {
    POST_traffic("red");
    GET_traffic();
    digitalWrite(yellow,LOW);
    digitalWrite(red,HIGH);
    if (analogRead(ldr)==light)
    {
      digitalWrite(red,LOW);
      digitalWrite(green, HIGH);
      state = 1;
    }
  }
}

