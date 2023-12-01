#include "get-handler.h"
#include "post-handler.h"

WiFiServer server(80);

void ServerLoop() {
  WiFiClient client = server.accept(); // listen for incoming clients

  if (client) { // if you get a client,
    // Serial.println("New Client"); // print a message out the serial port
    String GET = "";
    String POST = "";
    String currentLine =
      ""; // make a String to hold incoming data from the client
    while (client.connected()) { // loop while the client's connected
      if (client.available()) { // if there's bytes to read from the client,
        char c = client.read(); // read a byte, then
        // Serial.write(c); // print it out the serial monitor
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
    // Serial.println("Client Disconnected.");
  }
}
