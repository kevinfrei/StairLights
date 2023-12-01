/*
  WiFiAccessPoint.ino creates a WiFi access point and provides a web server on
  it.

  Steps:
  1. Connect to the access point "yourAp"
  2. Point your web browser to http://192.168.4.1/H to turn the LED on or
  http://192.168.4.1/L to turn it off OR Run raw TCP "GET /H" and "GET /L" on
  PuTTY terminal with 192.168.4.1 as IP address and 80 as port

  Created for arduino-esp32 on 04 July, 2018
  by Elochukwu Ifediora (fedy0)
*/

#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>

#include "server.h"

#ifndef LED_BUILTIN
#define LED_BUILTIN \
  2 // Set the GPIO pin where you connected your test LED or comment this line
    // out if your dev board has a built-in LED
#endif

// I need a map of paths to 'web files':
// a web file is a mime type and a byte array
// Since it's static, I can generate it from the create-react-app "build" step!

// Set these to your desired credentials.
const char* ssid = "StairwayLights";
const char* password = NULL; // "deadbeef";

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
  // a valid password must have more than 7 characters
  if (!WiFi.softAP(ssid, password)) {
    log_e("Soft AP creation failed.");
    while (1)
      ;
  }
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");
}

void loop() {
  ServerLoop();
}
