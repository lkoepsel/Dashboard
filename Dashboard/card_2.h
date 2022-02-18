#ifndef CARD_2
#define CARD_2

#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include "processor.h"

// setting Slider/PWM properties
#define LED2 33
#define FREQUENCY 5000
#define LEDCHANNEL 0
#define RESOLUTION 8
extern const char* slider_input;
extern String sliderValue;

void card_2(AsyncWebServer *server);
#endif
