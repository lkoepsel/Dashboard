#include "card_3.h"

extern AsyncWebServer server();

// Json Variable to Hold Sensor Readings
JSONVar readings;

// Get Sensor Readings and return JSON object
String getSensorReadings(){
  // readings["temperature"] = String(bme.readTemperature());
  readings["temperature"] = "30.0";
  // readings["humidity"] =  String(bme.readHumidity());
  readings["humidity"] =  "90.0";
  String jsonString = JSON.stringify(readings);
  return jsonString;
}

void card_3(AsyncWebServer *server) {

    // Send a GET request to /slider?value=<inputMessage>
    // Request for the latest sensor readings
    server->on("/readings", HTTP_GET, [](AsyncWebServerRequest *request){
        String json = getSensorReadings();
        request->send(200, "application/json", json);
        json = String();
    });
}