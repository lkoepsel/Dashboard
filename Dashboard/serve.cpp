#include "serve.h"

extern AsyncWebServer server();

// Card 2: setting Slider/PWM properties
const char* slider_input = "value";
String sliderValue = "0";

// Card 1 and Card 2: processor()
// Replaces placeholder with LED state value and 
// sends slider value to PWM
String processor(const String& var){
    String ledState1;

    Serial.println(var);

    // Card 1 Processing
    if(var == "STATE1"){
        if(digitalRead(LED1)){
          ledState1 = "ON";
        }
        else{
          ledState1 = "OFF";
        }
        Serial.print(ledState1);
        return ledState1;
    }

    // Card 2 Processing
    if (var == "SLIDERVALUE"){
      return sliderValue;
    }
    return String();
}


void serve(AsyncWebServer *server) {
    //****** Home Page with style, icon files ******
    // Route for root / web page
    server->on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
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
    //******End of Home Page with style, icon files ******

    //****** Card 1: GPIO Pin On/OFF ******
    // Route to set GPIO to HIGH
    server->on("/on1", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(LED1, HIGH);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
    });

    // Route to set GPIO to LOW
    server->on("/off1", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(LED1, LOW);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
    });
    //******End of Card 1: GPIO Pin On/OFF ******

    //****** Card 2: GPIO/PWM Slider ******
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
    //****** End of Card 2: GPIO/PWM Slider ******    
}