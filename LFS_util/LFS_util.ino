/*
 *  ESP32 Get LittleFS system information 
 *  Adapted from a version by Mischianti Renzo <https://www.mischianti.org>
 *
 *  https://www.mischianti.org/2021/04/01/esp32-integrated-littlefs-filesystem-5/#LittleFS_File_System
 *
 */
 
#include "Arduino.h"
#include "FS.h"
#include <LittleFS.h>

// Serial Port Constants and Variables
#define SERIAL_BAUD 921600

const int buf_size = 32; 
char s[buf_size];

void printDirectory(File dir, int numTabs = 1);
 
void setup()
{
    Serial.begin(SERIAL_BAUD);
 
    delay(500);
 
    Serial.print(F("Initializing FS..."));
    if (LittleFS.begin()){
        Serial.println(F("done."));
    }else{
        Serial.println(F("fail."));
    }
 
    // To format all space in LittleFS
    // LittleFS.format()
 
    // Get all information of your LittleFS
 
    unsigned int totalBytes = LittleFS.totalBytes();
    unsigned int usedBytes = LittleFS.usedBytes();
    unsigned int freeBytes;
 
    Serial.println("File system info:");

    snprintf(s, buf_size, "\tTotal: %10d bytes", totalBytes);
    puts(s);
 
    snprintf(s, buf_size, "\tUsed: %11d bytes", usedBytes);
    puts(s);

    freeBytes = totalBytes - usedBytes;
    snprintf(s, buf_size, "\tFree: %11d bytes", freeBytes);
    puts(s);
 
    Serial.println();
 
    // Open dir folder
    File dir = LittleFS.open("/");
    // Cycle all the content
    printfiles(dir);
}
 
void loop()
{
 
}

void printfiles(File dir) {
    while (true) {
        File entry = dir.openNextFile();
        if (! entry) {
            // no more files
            break;
        }
        if (entry.isDirectory()) {
            snprintf(s, buf_size, "\tDir: %-20s", entry.name());
        }
        else {
            snprintf(s, buf_size, "\t%-20s %8i", entry.name(), entry.size());
        }
        puts(s);
        entry.close();
    }
}
