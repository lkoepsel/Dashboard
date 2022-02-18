#include "home.h"

extern AsyncWebServer server();

void home(AsyncWebServer *server) {
    // Route for root / web page

    server->on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false);
    });

    // Route to load style.css file
    server->on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
    });

    // Route to load favicon.png file (doesn't appear to work or be invoked)
    server->on("/favicon.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "favicon.png", "image/png");
    });

    // Route to load lightbulb.svg file
    server->on("/lightbulb.svg", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/lightbulb.svg", "image/svg+xml");
    });

    // Route to load switch-closed.svg file
    server->on("/switch-closed.svg", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/switch-closed.svg", "image/svg+xml");
    });

    // Route to load switch-open.svg file
    server->on("/switch-open.svg", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/switch-open.svg", "image/svg+xml");
    });

}