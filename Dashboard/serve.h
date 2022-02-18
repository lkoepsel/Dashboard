/* serve - very simple function which provides a central location 
*  serving cards. For every card on the home page, there needs to 
*  a call to the card in serve. Think of this as the "void loop" in 
*  the Arduino .ino file.
*/

#ifndef SERVE
#define SERVE

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include "home.h"
#include "card_1.h"
#include "card_0.h"
#include "card_2.h"

void serve(AsyncWebServer *server);
#endif