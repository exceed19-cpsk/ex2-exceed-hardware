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

// #define light <แสดงมันมืด มีค่าเท่าไหร่>

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
  // *** write your code here ***
  // Your can change everything that you want
  debouncer.update();
  if (state == 1)
  {
    // while led GREEN
    if (debouncer.fell()) {
      state = 2;
      digitalWrite(green, LOW);
      digitalWrite(yellow, HIGH);
      POST_traffic("yellow");
    }
  }
  else if (state == 2)
  {
    // while led YELLOW
    delay(8000);
    state = 3;
    digitalWrite(yellow, LOW);
    digitalWrite(red, HIGH);
    POST_traffic("red");
    GET_traffic();
  }
  else if (state == 3)
  {
    // while led RED
    delay(5000);
    while (1) {
      if (analogRead(ldr) < 2500) {
        state = 1;
        digitalWrite(red, LOW);
        digitalWrite(green, HIGH);
        POST_traffic("green");
        GET_traffic();
        break;
      }
    } 
  }
}

void Connect_Wifi()
{
  const char *ssid = "choon";
  const char *password = "12345678";
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