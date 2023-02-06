#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Bounce2.h>

const String baseUrl = "https://exceed-hardware-stamp465.koyeb.app";

const String point = "9";
const int nearby_1 = 8;
const int nearby_2 = 10;

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

    // *** write your code here ***
    JsonArray traffics = doc["all_traffic"].as<JsonArray>();
    for (JsonObject traffic : traffics)
    {
      String point = traffic["point"].as<String>();
      if (point.toInt() >= nearby_1 && point.toInt() <= nearby_2)
      {
        String led = traffic["traffic"].as<String>();
        Serial.print("point: ");
        Serial.print(point);
        Serial.print(" traffic: ");
        Serial.println(led);
      }
    }
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
  
  doc["code"] = "c8vmo";
  doc["traffic"] = led;
  
  serializeJson(doc, json);

  Serial.println("POST " + led);
  int httpResponseCode = http.POST(json);
  if (httpResponseCode == 200)
  {
    Serial.print("Done");
    Serial.println();
  }
  else
  {
    Serial.print("Error ");
    Serial.println(httpResponseCode);
  }

  Serial.println("----------------------------------");
}