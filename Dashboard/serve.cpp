#include "serve.h"

extern AsyncWebServer server();

// Note the server is a pointer when entering serve(),
// it doesn't need to be dereferenced again.
void serve(AsyncWebServer *server) {
    //****** Home Page with style, icon files ******
    home(server);

    //****** Card 0: Built-in LED Pin On/OFF ******
    // Route to set Built-in LED to HIGH
    card_0(server);

    //****** Card 1: GPIO Pin On/OFF ******
    // Route to set GPIO to HIGH
    card_1(server);

    //****** Card 2: GPIO/PWM Slider ******
    // Send a GET request to /slider?value=<inputMessage>
    card_2(server);
}