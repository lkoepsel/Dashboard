# ESP32 Dashboard
Based the ESP32 SoC using the Arduino Framework, Random Nerd Tutorials and the ESP32 examples from Espressif. The most significant difference in this code and what is seen on RNT is that I have setup the following:
1) Extreme modular approach such that there are a great number of small files, instead of a monolithic approach.
2) This dashboard is setup as a *soft access point* with the ESP32. This means the application will serve up the dashboard locally and doesn't access the internet.
3) Like RNT's example, this dashboard uses the concept of *cards*, with this approach using one card per file (actually two files card_n.h and card_n.cpp).

Additional information for this project will be on my website:
* [wellys.com - ESP32: Automation](https://wellys.com/posts/automation/)
* [wellys.com - ESP32: Using a modular approach](https://wellys.com/posts/esp32_modules/)
* [wellys.com - ESP32: Solving Issues with Arduino Development](https://wellys.com/posts/esp32_issues/)
* [wellys.com - ESP32: Using arduino-cli](https://wellys.com/posts/esp32_cli/)
## Code:
Here is a high level approach to adding to this code. Each new sensor will require a *card*. Cards are sections on the homepage which either report a value or allow a control to make a change on the ESP32 (for example, a slider on a card, dims an LED).
To add a card, you need to do the following:
1) Add card_n.h and card_n.cpp files, typically its best to duplicate an existing card and make changes to it.
2) Add card_n content to index.html, again, duplicate and edit a card section on the index.html
3) Add a call to card_n(server) in serve.cpp, as in "card_n(serve);"
4) Add template processing to processor.cpp. This is a bit more complicated and based on what you want to accomplish. The function processor is used to replace %template% variables with data. More on this later.
### Dashboard
The main code for development. The goal is to have a easy to maintain and easy to expand Access Point web page-based Dashboard. 
### LFS_util
LittleFS utility to print out the bytes used and free. Based on a sketch by [Mischanti Renzo](https://www.mischianti.org/2021/04/01/esp32-integrated-littlefs-filesystem-5/#LittleFS_File_System)
#### Sample Output
```
Initializing FS...done.
File system info:
        Total:    1507328 bytes
        Used:      315392 bytes
        Free:     1191936 bytes

        favicon.png               717
        gauge.min.js.map       229040
        gauge.min.js            44751
        index.html               2547
        lightbulb.svg             547
        script.js                3623
        style.css                1782
        switch-closed.svg         738
        switch-open.svg           858
```
For more information as to why LittleFS, see [joltwallet on Github](https://github.com/joltwallet/esp_littlefs)
### blink:
* basic blink program used to test tool chain, test IDE, test board, just to good to have at my fingertips... :)
## Boards
* [Adafruit Feather ESP32](https://learn.adafruit.com/adafruit-huzzah32-esp32-feather/overview)
* [Dev Board from DOIT] - Identifies as a NodeMCU-32S

## Sources
* [arduino-esp32 examples](https://github.com/espressif/arduino-esp32/tree/master/libraries/WiFi/examples)
* [ESPAsyncWebServer on Github](https://github.com/me-no-dev/ESPAsyncWebServer)
* [Random Nerd Tutorial ESP32 Web Manager](https://randomnerdtutorials.com/esp32-wi-fi-manager-asyncwebserver/)
* [ESP32: integrated LittleFS FileSystem](https://www.mischianti.org/2021/04/01/esp32-integrated-littlefs-filesystem-5/#LittleFS_File_System)

## Notes (YYMMDD)
### 220331: Added Dallas Semi and OneWire to Card 4
I integrated the code from [RNT:DS18B20 Async Web Server](https://randomnerdtutorials.com/guide-for-ds18b20-temperature-sensor-with-arduino/) into Dashboard. This includes changes to:
* Dashboard.ino
* data/index.html
* data/script.js
* processor.cpp
* added card_4.cpp
* added card_4.h
It was difficult to determine where some of the code would reside as there were multiple errors of "...previously defined..." which needed to be resolved. Ultimately, I placed the DallasSemi code in Dashboard.ino to be set up as a global variable. I haven't been able to test the code, not having the right chips.

### 220313: Change to makefile 
Please see this [entry on Wellys](https://wellys.com/posts/automation/) for a full explanation. I changed the build approach from a *custom Sublime Text build*, to a more standardized approach using *make*. What is **NOT** included in this repository is a file called *env.make*:
```make
board = esp32:esp32:featheresp32
port = /dev/cu.usbserial*
build = build
```
The *makefile* in the repository will include this file to capture the local environmental variables.
### 220302: LittleFS Requirements
In order to use LittleFS, you need two things:

1. Arduino IDE tools to upload data:

* In *\~/.arduino15/packages/esp32/tools*, there needs to be *mklittlefs*, this is the tool which will make a littlefs filesystem on the ESP32

* The .jar file in */home/lkoepsel/Arduino/tools/ESP32FS/tool/* must be replaced by the [one on github](https://github.com/lorol/arduino-esp32fs-plugin), otherwise the three options will not appear in the Arduino dropdown Tools -> ESP32 Sketch Data Upload. As both .jar files have the same name, I added *.spiffs* to the end of the old one to remind me.

2. Arduino framework tools to use LittleFS in your code

* The Arduino core package as of v2.00 now contains LittleFS.h as indicated by [this note](https://github.com/lorol/LITTLEFS#ths-library-is-now-part-of-arduino-esp32-core-v2). Make sure your IDE and arduino-cli are both version 2.0 or higher. The one I use is *2.0.2*

* The actual header file required to use LittleFS is located here: */home/lkoepsel/.arduino15/packages/esp32/hardware/esp32/2.0.2/libraries/LittleFS/src*. Make sure it appears there, if not, reload the ESP32 package for the Arduino.
 
Check all four elements and make sure they exist/or are correct.
### 220221: LittleFS Utility added
See sample output above. Use serial monitor to gather information about installed files on the ESP32 via LittleFS.
### 220220: SPIFFS -> LittleFS
Switched from SPIFFS to LittleFS, it [appears that LittleFS is faster (2-3x)](https://github.com/joltwallet/esp_littlefs) and more reliable. Haven't confirmed either, however, no issues after switching.
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
The [canvas-gauges](https://github.com/Mikhus/canvas-gauges) library is great for embedded projects. There are two files which are not in the git folder and are not tracked, *gauge.min.js* and *gauge.min.js.map*. Both of these files are in the root directory of the canvas-gauges release. Download the latest from github, extract the folder and copy the two files in to the data folder.
