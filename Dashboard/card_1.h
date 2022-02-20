/* card_0: Simple function to turn a GPIO off/on via a /off or /on url
*  "/on1" - url to turn on
*  "/off1" - url to turn off
*  use define LED1 n to define the GPIO number 
*/
#ifndef CARD_1
#define CARD_1

#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include "processor.h"

// ON1/OFF1 Properties
#define LED1 32

void card_1(AsyncWebServer *server);
#endif
