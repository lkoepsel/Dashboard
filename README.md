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

## Notes (YYMMDD)
### 220220: SPIFFS -> LittleFS
Switched from SPIFFS to LittleFS, it appears that LittleFS is faster (2-3x) and more reliable. Haven't confirmed either, however, no issues after switching.
1. The latest 2.0.2 code has LittleFS capabilities, however, it is critical to spell correctly as shown, **LittleFS**. It is not LITTLEFS (all-caps). Replaced (*already performed*) all references from SPIFFS and SPIFFS.h to LittleFS and LittleFS.h.
2. A new tool is required: [Arduino ESP32 filesystem uploader](https://github.com/lorol/arduino-esp32fs-plugin), download the latest, extract and replace esp32fs.jar in the Arduino/tools folder then restart the IDE.
3. Once IDE is restarted, I found I needed to erase all Flash to get things to work. It is in the dropdown shown when *ESP32 Sketch Data Upload* is selected, it is at the very bottom. Perform this step then select *ESP32 Sketch...* and use the LittleFS selection to upload the data folder.
4. This did simplify the serving of files, note the simplification in home.cpp. I removed all the specific file entries to a single *serveStatic* command.
### 220218: Details on adding Cards
Here are the detailed steps to adding a new card to the Website. (*It doesn't include how to solve formatting issues as when one card is much longer to the one beside it in the row.*):
* **server**: add an include to the .h file and a "card_n(server);" to the .cpp file
* **processor**(optional): add an include to the .h file. Adding the *process* will depend on the tpe of processor required, I recommend reviewing the code used in RNT or the example you are emulating then incorporate in a similar fashion in processor.cpp
* **Dashboard.ino**(optional): if there is code required to setup the sensor or dial (such as PinMode or ledCAttachPin) then add that to the Setup() code. If it needs to be performed on a periodic basis, add an event to loop().
* **card_n**: this is the main code for the specific card and provides specifically what code is required for the code to display on index.html. I recommend you look at the existing cards, duplicate one that is closest and go from there. Remember to add the declaration code to *card_n.h*.
* **data/index.html**: each card requires a card section, similar to *card_n*, find one that is similar...
* **data/script.js**(optional): if the sensor or dial requires an event, you will need to add javascript code to manage it in the script.js file. 
### 220217: Using canvas-gauges
The [canvas-gauges](https://github.com/Mikhus/canvas-gauges) library is great for embedded projects. There are two files which are not in the git folder and are not tracked.