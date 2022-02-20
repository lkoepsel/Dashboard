# ESP32 Dashboard
Based the ESP32 SoC using the Arduino Framework, Random Nerd Tutorials and the ESP32 examples from Espressif. The most significant difference in this code and what is seen on RNT is that I have setup the following:
1) Extreme modular approach such that there are a great number of small files, instead of a monolithic approach.
2) This dashboard is setup as a *soft access point* with the ESP32. This means the application will serve up the dashboard locally and doesn't access the internet.
3) Like RNT's example, this dashboard uses the concept of *cards*, with this approach using one card per file (actually two files card_n.h and card_n.cpp).

Most of the documentation will be on my website:
* [wellys.com](https://wellys.com/posts/esp32_modules/)

## Code:
Here is a high level approach to adding to this code. Each new sensor will require a *card*. Cards are sections on the homepage which either report a value or allow a control to make a change on the ESP32 (for example, a slider on a card, dims an LED).
To add a card, you need to do the following:
1) Add card_n.h and card_n.cpp files, typically its best to duplicate an existing card and make changes to it.
2) Add card_n content to index.html, again, duplicate and edit a card section on the index.html
3) Add a call to card_n(server) in serve.cpp, as in "card_n(serve);"
4) Add template processing to processor.cpp. This is a bit more complicated and based on what you want to accomplish. The function processor is used to replace %template% variables with data. More on this later.
### blink:
* basic blink program used to test tool chain, test IDE, test board, just to good to have at my fingertips... :)
### Dashboard
The main code for development. The goal is to have a easy to maintain and easy to expand Access Point web page-based Dashboard. 

## Boards
* [Adafruit Feather ESP32](https://learn.adafruit.com/adafruit-huzzah32-esp32-feather/overview)
* [Dev Board from DOIT] - Identifies as a NodeMCU-32S

## Sources
* [arduino-esp32 examples](https://github.com/espressif/arduino-esp32/tree/master/libraries/WiFi/examples)
* [ESPAsyncWebServer on Github](https://github.com/me-no-dev/ESPAsyncWebServer)
* [Random Nerd Tutorial ESP32 Web Manager](https://randomnerdtutorials.com/esp32-wi-fi-manager-asyncwebserver/)
