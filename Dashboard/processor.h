/* processor is the centralized function for handling templates
*  because the logic and template are interwoven, its difficult
*  separate them out as in serve/cards. All templates must have logic
*  in processor to define the template value.
*/
#ifndef PROCESSOR
#define PROCESSOR

#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include "card_0.h"
#include "card_1.h"
#include "card_2.h"

// Card processor
String processor(const String& var);

#endif
