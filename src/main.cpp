// If you want to run in WOKWi
// change pin and wifi
#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Bounce2.h>
//#include "traffic.h"

#define red 26
#define yellow 25
#define green 33
#define ldr 32
#define button 27
#define light 2550

int state = 1;
int count = 0;
Bounce debouncer = Bounce();

//void Connect_Wifi();

void setup()
{
  Serial.begin(115200);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(ldr, INPUT);
  debouncer.attach(button, INPUT_PULLUP);
  debouncer.interval(25);
  //Connect_Wifi();

  delay(200);
  // start LED with GREEN and POST to database
  digitalWrite(green, HIGH);
  //POST_traffic("green");
}

void loop()
{
  // *** write your code here ***
  // Your can change everything that you want
  if (state == 1)
  {
    digitalWrite(green, HIGH);
    debouncer.update();
    if (debouncer.fell()) { 
      Serial.println("ima here");
      digitalWrite(green, LOW);
      state = 2;      
    }
  }
  else if (state == 2)
  {
    digitalWrite(yellow, HIGH);
    delay(8000);
    digitalWrite(yellow, LOW);
    state = 3;
  }
  else if (state == 3)
  {
    Serial.println(analogRead(ldr));
    digitalWrite(red, HIGH);
    //delay(5000);
    if(analogRead(ldr) <= light)
    {
      digitalWrite(red, LOW);
      state = 1;
    }
  }
}

void Connect_Wifi()
{
  const char *ssid = "POCOPHONE";
  const char *password = "a1b2c3d4";
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