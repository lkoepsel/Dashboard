#include "processor.h"

const char* slider_input = "value";
String sliderValue = "0";

// Card processor()
// Replaces template placeholders with values 
String processor(const String& var){
    // processor local variables, add them here and not in
    // card sections 
    String ledState0;
    String ledState1;

    //debug* Serial.println(var);

    // Card 0 Processing
    if(var == "STATE0"){
        if(digitalRead(LED0)){
          ledState0 = "ON";
        }
        else{
          ledState0 = "OFF";
        }
        Serial.print(ledState0);
        return ledState0;
    }

    // Card 1 Processing
    if(var == "STATE1"){
        if(digitalRead(LED1)){
          ledState1 = "ON";
        }
        else{
          ledState1 = "OFF";
        }
        Serial.print(ledState1);
        return ledState1;
    }

    // Card 2 Processing
    if (var == "SLIDERVALUE"){
      return sliderValue;
    }

    return String();
}
