/* card_0: Simple function to turn the built-in LED off/on via a /off or /on url
*  "/on0" - url to turn on
*  "/off0" - url to turn off
*/

#ifndef CARD_0
#define CARD_0

#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include "processor.h"

// ON0/OFF0 Properties
#define LED0 LED_BUILTIN

void card_0(AsyncWebServer *server);
#endif
