/*
  Dashboard.ino creates a WiFi access point and starts the Asynch Server
  If you are adding code here, you are probably doing something wrong.
*/

#include <WiFi.h>
#include <WiFiAP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <Arduino_JSON.h>
#include <OneWire.h>
#include <DallasTemperature.h>


#include "arduino_secrets.h"
#include "serve.h"
#include "card_0.h"
#include "card_1.h"
#include "card_2.h"
#include "card_3.h"
#include "card_4.h"

// switch from SPIFFS to LittleFS

// Serial Port Constants and Variables
#define SERIAL_BAUD 921600

// Access Point Constants and Variables
const char *ssid = SECRET_AP;
const char *password = SECRET_PASS;

// Create AsyncWebServer 
#define WEB_PORT 80
AsyncWebServer server(WEB_PORT);

// Create an Event Source on /events
AsyncEventSource events("/events");

// Global variables for temp measurement
// Data wire is connected to GPIO 4
#define ONE_WIRE_BUS 4
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);
// Variables to store temperature values
String temperatureF;

String readDSTemperatureF() {
  // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
  sensors.requestTemperatures(); 
  float tempF = sensors.getTempFByIndex(0);

  if(int(tempF) == -196){
    Serial.println("Failed to read from DS18B20 sensor");
    return "--";
  } else {
    Serial.print("Temperature Fahrenheit: ");
    Serial.println(tempF);
  }
  return String(tempF);
}

// Timer variables for void Loop
unsigned long lastTime = 0;
unsigned long timerDelay = 10000;

void setup() {
    // Serial port for debugging purposes
    Serial.begin(SERIAL_BAUD);

    // Initialize SPIFFS
    if(!LittleFS.begin(true)){
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
    }
    // Card 1: configure LED ON/OFF properties
    pinMode(LED0, OUTPUT);
    pinMode(LED1, OUTPUT);

    // Card 2: configure GPIO PWM properties
    ledcSetup(LEDCHANNEL, FREQUENCY, RESOLUTION);
    ledcAttachPin(LED2, LEDCHANNEL);
    ledcWrite(LEDCHANNEL, sliderValue.toInt());

    // Card 4: Start up DS18B20 and read initial temps
    sensors.begin();
    // extern String temperatureF = readDSTemperatureF();

    Serial.begin(921600);
    Serial.println();
    Serial.println("Configuring wireless...");

    WiFi.softAP(ssid, password);
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);

    events.onConnect([](AsyncEventSourceClient *client){
      if(client->lastId()){
        Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
      }
      // send event with message "hello!", id current millis
      // and set reconnect delay to 1 second
      client->send("hello!", NULL, millis(), 10000);
    });
    server.addHandler(&events);

    Serial.println("Server started");
    serve(&server);
    server.begin();

}

void loop() {
    if ((millis() - lastTime) > timerDelay) {
      // Card 3 Sensor Readings
      // Send Events to the client with the Sensor Readings Every 10 seconds
      events.send("ping",NULL,millis());
      events.send(getSensorReadings().c_str(),"new_readings" ,millis());

      // Card 4 temperature measurement
      temperatureF = readDSTemperatureF();

      lastTime = millis();
    }
}