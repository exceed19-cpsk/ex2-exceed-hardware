// If you want to run in WOKWi
// change pin and wifi
#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Bounce2.h>
#include "traffic.h"

#define BUTTON 27
#define GREEN 33
#define RED 26
#define YELLOW 25
#define LDR 32

int stage = 0;
int lumine = 0;
Bounce debouncer = Bounce();

void Connect_Wifi();

void setup() {
    Serial.begin(115200);
    pinMode(BUTTON, INPUT_PULLUP);
    debouncer.attach(BUTTON);
    debouncer.interval(5);
    pinMode(GREEN, OUTPUT);
    pinMode(YELLOW, OUTPUT);
    pinMode(RED, OUTPUT);
}
void loop(){
    debouncer.update();
    if (debouncer.fell() && stage == 0) { 
      stage = 1;
    }
    if (stage == 0) { //Green
        digitalWrite(GREEN, HIGH);
        digitalWrite(YELLOW, LOW);
        digitalWrite(RED, LOW);
    } 
    else if (stage == 1) { //Yellow
        digitalWrite(GREEN, LOW);
        digitalWrite(YELLOW, HIGH);
        digitalWrite(RED, LOW);
        delay(8000); //wait 8 seconds
        stage = 2; //go to stage 2
    } 
    else if (stage == 2) { //Red
        digitalWrite(GREEN, LOW);
        digitalWrite(YELLOW, LOW);
        digitalWrite(RED, HIGH);
        delay(5000); //wait 5 seconds
        lumine = map(analogRead(LDR),1500,3500,0,255);
        if (lumine < 100) { //if dark go to stage 0
            stage = 0;
        }
    }
    Serial.println(stage); //print stage
}

void Connect_Wifi()
{
  const char *ssid = "vivo 1818";
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