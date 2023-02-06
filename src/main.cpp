// If you want to run in WOKWi
// change pin and wifi
#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Bounce2.h>
#include "traffic.h"

#define RED 26
#define YELLOW 25
#define GREEN 33
#define LDR 34
#define BUTTON 27
#define LIGHT analogread(LDR)
int cnt = 1;
int state = 1;
int count = 0;
Bounce debouncer = Bounce();
void Connect_Wifi();

void setup()
{
  Serial.begin(115200);
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(LDR, INPUT);
  debouncer.attach(BUTTON, INPUT_PULLUP);
  debouncer.interval(25);
  Connect_Wifi();

  delay(200);
  // start LED with GREEN and POST to database
  digitalWrite(GREEN, 1);
  POST_traffic("GREEN");
}

void loop()
{
  // *** write your code here ***
  // Your can change everything that you want
  if (state == 1)
  {
    // while led GREEN
  }
  else if (state == 2)
  {
    // while led YELLOW
  }
  else if (state == 3)
  {
    // while led RED
  }
}

void Connect_Wifi()
{
  const char *ssid = "nitro 5";
  const char *password = "12345687";
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