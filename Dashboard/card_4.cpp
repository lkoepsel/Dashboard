#include "card_4.h"

extern AsyncWebServer server();

void card_4(AsyncWebServer *server) {

    // Send a GET request to /slider?value=<inputMessage>
    // Request for the latest sensor readings
    server->on("/temperaturef", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send_P(200, "text/plain", temperatureF.c_str());
    });
}