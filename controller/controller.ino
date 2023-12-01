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

#include "webfiles.h"
#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>

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

WiFiServer server(80);

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

bool HandleGet(const String& get, WiFiClient& client) {
  // Get the file name requested from the get line
  Serial.println(get);
  int32_t protocolPos = get.indexOf(" HTTP/");
  int32_t questionPos = get.indexOf('?');
  int32_t pos = std::max(protocolPos, questionPos);
  if (pos < 6) {
    Serial.printf("Nope: %s (%d, %d)\n", get.c_str(), protocolPos, questionPos);
    return false;
  }
  Serial.printf("Searching (pos = %d)!\n", pos);
  for (const WebFile& item : FileList) {
    // Starts with 'GET /': 5 characters, right?

    if (item.pathname.len == pos - 5 && get.indexOf(item.pathname.data) == 5) {
      Serial.printf("Got %s", item.pathname.data);
      // Should I break the files up into pieces to send?
      client.println("HTTP/1.1 200 OK");
      client.printf("Content-type:%s\n", item.mimeType);
      client.println();
      client.write(item.content.data, item.content.len);
      client.println();
      return true;
    }
  }
  Serial.println("Nothing found");
  return false;
}

bool HandlePost(const String& post, WiFiClient& client) {
  // Get the file name requested from the get line
  Serial.println(post);
  int32_t protocolPos = post.indexOf(" HTTP/");
  int32_t questionPos = post.indexOf('?');
  int32_t pos = std::max(protocolPos, questionPos);
  if (pos < 7) {
    Serial.printf(
      "Nope: %s (%d, %d)\n", post.c_str(), protocolPos, questionPos);
    return false;
  }
  if (post.indexOf("api_") == 6) {
    String s = post.substring(6 + 4, pos);
    Serial.printf("API: '%s' (%d)\n", s.c_str(), pos);
    client.println("HTTP/1.1 200 OK");
    client.printf("Content-type:text/plain\n");
    client.println();
    client.write("OK", 3);
    client.println();
    return true;
  }
  Serial.println("Nothing found");
  return false;
}

void loop() {
  WiFiClient client = server.accept(); // listen for incoming clients

  if (client) { // if you get a client,
    Serial.println("New Client"); // print a message out the serial port
    String GET = "";
    String POST = "";
    String currentLine =
      ""; // make a String to hold incoming data from the client
    while (client.connected()) { // loop while the client's connected
      if (client.available()) { // if there's bytes to read from the client,
        char c = client.read(); // read a byte, then
        Serial.write(c); // print it out the serial monitor
        if (c == '\n') { // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a
          // row. that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200
            // OK) and a content-type so the client knows what's coming, then a
            // blank line:
            if (GET.length() != 0) {
              if (!HandleGet(GET, client)) {
                client.println("HTTP/1.1 404 Not Found");
                // The HTTP response ends with another blank line:
                client.println();
              }
              GET = "";
            } else if (POST.length() != 0) {
              if (!HandlePost(POST, client)) {
                client.println("HTTP/1.1 404 Not Found");
                // The HTTP response ends with another blank line:
                client.println();
              }
              POST = "";
            }
            break;
          } else {
            if (currentLine.startsWith("GET /")) {
              GET = currentLine;
            } else if (currentLine.startsWith("POST /")) {
              POST = currentLine;
            }
            currentLine = "";
          }
        } else if (c != '\r') { // if you got anything else but a carriage
                                // return character,
          currentLine += c; // add it to the end of the currentLine
        }

        /*
        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(LED_BUILTIN, HIGH);               // GET /H turns the LED
        on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(LED_BUILTIN, LOW);                // GET /L turns the LED
        off
        }
        */
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
