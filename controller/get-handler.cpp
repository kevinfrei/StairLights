#include <Arduino.h>
#include <WiFiClient.h>

#include "get-handler.h"

// This guy serves up static content, encoded by the node script
bool HandleGet(const String& get, WiFiClient& client) {
  // Get the file name requested from the get line
  Serial.println(get);
  int32_t protocolPos = get.indexOf(" HTTP/");
  int32_t questionPos = get.indexOf('?');
  int32_t pos = std::max(protocolPos, questionPos);
  if (pos < 5) {
    Serial.printf("Nope: %s (%d, %d)\n", get.c_str(), protocolPos, questionPos);
    return false;
  }
  Serial.printf("Searching (pos = %d)!\n", pos);
  for (const WebFile& item : FileList) {
    // Starts with 'GET /': 5 characters, right?

    if (item.pathname.len == pos - 5 &&
        (get.indexOf(item.pathname.data) == 5 ||
         (item.pathname.len == 0 && protocolPos == 5))) {
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
  // Serial.println("Nothing found");
  return false;
}