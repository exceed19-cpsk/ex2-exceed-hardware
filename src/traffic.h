#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Bounce2.h>

const String baseUrl = "https://exceed-hardware-stamp465.koyeb.app";

const String point = "10";
const int nearby_1 = 9;
const int nearby_2 = 11;

void GET_traffic()
{
  DynamicJsonDocument doc(65536);
  HTTPClient http;
  const String url = baseUrl + "/all_traffic";
  http.begin(url);

  Serial.println("Nearby traffic");
  int httpResponseCode = http.GET();
  if (httpResponseCode == 200)
  {
    String payload = http.getString();
    deserializeJson(doc, payload);
    Serial.println("Current traffic");
    Serial.println((const char*)doc["all_traffic"][9]["traffic"]);
    Serial.print("Point 9");
    Serial.println((const char*)doc["all_traffic"][8]["traffic"]);
    Serial.print("Point 11");
    Serial.println((const char*)doc["all_traffic"][10]["traffic"]);
  }
  else
  {
    Serial.print("Error ");
    Serial.println(httpResponseCode);
  }

  Serial.println("----------------------------------");
}

void POST_traffic(String led)
{
  const String url = baseUrl + "/my_traffic?point=" + point;
  String json;
  HTTPClient http;
  http.begin(url);
  http.addHeader("Content-Type", "application/json");

  DynamicJsonDocument doc(2048);
  doc["code"] = "kaej2";
  doc["traffic"] = led;
  serializeJson(doc, json);

  Serial.println("POST " + led);
  int httpResponseCode = http.POST(json);
  if (httpResponseCode == 200)
  {
    Serial.print("Done");
    Serial.println();
    Serial.println(http.getString());
  }
  else
  {
    Serial.print("Error ");
    Serial.println(httpResponseCode);
  }

  Serial.println("----------------------------------");
}