#ifndef CARD_1
#define CARD_1

#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include "processor.h"

// ON1/OFF1 Properties
#define LED1 32

void card_1(AsyncWebServer *server);
#endif
