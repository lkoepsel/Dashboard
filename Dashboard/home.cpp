#include "home.h"

extern AsyncWebServer server();

void home(AsyncWebServer *server) {
    // Route for root / web page

    server->on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/index.html", "text/html");
    });

    server->serveStatic("/", LittleFS, "/");

    server->onNotFound([](AsyncWebServerRequest *request){
        request->send(404, "text/html", "<h1>The file or content was not found.</h1>");
    });

}