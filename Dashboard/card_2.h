/* card_d: incorporates an HTML slider to provide values to the ESP32 PWM
*  properties are defined below using "Slider/PWM properties"
*/

#ifndef CARD_2
#define CARD_2

#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include "processor.h"

// setting Slider/PWM properties
#define LED2 33						// GPIO pin to affect
#define FREQUENCY 5000				// frequency of PWM
#define LEDCHANNEL 0				// channel of PWM
#define RESOLUTION 8				// duty cycle range from 0-255
extern const char* slider_input;	// C++ variable to capture slider value
extern String sliderValue;			// JS varible used for slider value

void card_2(AsyncWebServer *server);
#endif
