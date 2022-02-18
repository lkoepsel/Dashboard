#ifndef CARD_0
#define CARD_0

#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include "processor.h"

// ON0/OFF0 Properties
#define LED0 LED_BUILTIN

void card_0(AsyncWebServer *server);
#endif
