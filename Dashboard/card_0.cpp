#include "card_0.h"

extern AsyncWebServer server();

void card_0(AsyncWebServer *server) {

    // Route to set GPIO to HIGH
    server->on("/on0", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(LED0, HIGH);    
    request->send(LittleFS, "/index.html", String(), false, processor);
    });

    // Route to set GPIO to LOW
    server->on("/off0", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(LED0, LOW);    
    request->send(LittleFS, "/index.html", String(), false, processor);
    });

}