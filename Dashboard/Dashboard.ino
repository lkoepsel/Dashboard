/*
  Dashboard.ino creates a WiFi access point and starts the Asynch Server
  If you are adding code here, you are probably doing something wrong.
*/

#include <WiFi.h>
#include <WiFiAP.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include "arduino_secrets.h"
#include "serve.h"
#include "card_0.h"
#include "card_1.h"
#include "card_2.h"

// Serial Port Constants and Variables
#define SERIAL_BAUD 921600

// Access Point Constants and Variables
const char *ssid = SECRET_AP;
const char *password = SECRET_PASS;


// Create AsyncWebServer 
#define WEB_PORT 80
AsyncWebServer server(WEB_PORT);

void setup() {
    // Serial port for debugging purposes
    Serial.begin(SERIAL_BAUD);

    // Initialize SPIFFS
    if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
    }
    // Card 1: configure LED ON/OFF properties
    pinMode(LED0, OUTPUT);
    pinMode(LED1, OUTPUT);

    // Card 2: configure GPIO PWM properties
    ledcSetup(LEDCHANNEL, FREQUENCY, RESOLUTION);
    ledcAttachPin(LED2, LEDCHANNEL);
    ledcWrite(LEDCHANNEL, sliderValue.toInt());

    Serial.begin(921600);
    Serial.println();
    Serial.println("Configuring access point...");

    WiFi.softAP(ssid, password);
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);

    Serial.println("Server started");
    serve(&server);
    server.begin();

}

void loop() {

}