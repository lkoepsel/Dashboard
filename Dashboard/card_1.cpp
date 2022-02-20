#include "card_1.h"

extern AsyncWebServer server();

void card_1(AsyncWebServer *server) {

    // Route to set GPIO to HIGH
    server->on("/on1", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(LED1, HIGH);    
    request->send(LittleFS, "/index.html", String(), false, processor);
    });

    // Route to set GPIO to LOW
    server->on("/off1", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(LED1, LOW);    
    request->send(LittleFS, "/index.html", String(), false, processor);
    });

}