/* home - provides the home page and additional icon/style files
*  add to home when there is a new icon or image to be displayed
*/

#ifndef HOME
#define HOME

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>


void home(AsyncWebServer *server);
#endif
