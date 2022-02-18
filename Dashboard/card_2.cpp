#include "card_2.h"

extern AsyncWebServer server();

void card_2(AsyncWebServer *server) {

    // Send a GET request to /slider?value=<inputMessage>
    server->on("/slider", HTTP_GET, [] (AsyncWebServerRequest *request) {
      String inputMessage;
      // GET input1 value on /slider?value=<inputMessage>
      if (request->hasParam(slider_input)) {
        inputMessage = request->getParam(slider_input)->value();
        sliderValue = inputMessage;
        ledcWrite(LEDCHANNEL, sliderValue.toInt());
      }
      else {
        inputMessage = "No message sent";
      }
      Serial.println(inputMessage);
      request->send(200, "text/plain", "OK");
    });
}