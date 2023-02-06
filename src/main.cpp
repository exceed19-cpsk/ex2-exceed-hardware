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

#define light 0

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
  debouncer.update();
  int ch = analogRead(ldr);
  // *** write your code here ***
  // Your can change everything that you want
  if (state == 1)
  {
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
    if(debouncer.fell()){
      state = 2;
    }
    POST_traffic("green");
    GET_traffic();
    // while led GREEN

  }
  else if (state == 2)
  {
    digitalWrite(yellow, HIGH);
    digitalWrite(green, LOW);
    delay(8000);
    state = 3;
    POST_traffic("yellow");
    GET_traffic();
    // while led YELLOW
  }
  else if (state == 3)
  {
    digitalWrite(red, HIGH);
    digitalWrite(yellow, LOW);
    delay(5000);
    Serial.println(ch);
    if(ch < 4095){
      state = 1;
    }
    POST_traffic("red");
    // while led RED
  }
}


void Connect_Wifi()
{
  const char *ssid = "Galaxy A30C9C8";
  const char *password = "himl9080";
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
