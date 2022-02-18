#ifndef SERVE
#define SERVE

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

// ON1/OFF1 Properties
#define LED1 32

// setting Slider/PWM properties
#define LED2 33
#define FREQUENCY 5000
#define LEDCHANNEL 0
#define RESOLUTION 8
extern const char* slider_input;
extern String sliderValue;

// Card 1 and Card 2 processor
String processor(const String& var);

void serve(AsyncWebServer *server);
#endif