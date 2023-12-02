#include <Arduino.h>
#include <WiFiClient.h>

#include "post-handler.h"

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
  if (post.indexOf("api/") == 6) {
    String func = post.substring(6 + 4, pos);
    int32_t funcEnd = func.indexOf("/");
    String param = "";
    if (funcEnd >= 0) {
      param = func.substring(funcEnd + 1);
      func = func.substring(0, funcEnd);
    }
    Serial.printf("Calling: '%s(%s)'\n", func.c_str(), param.c_str());
    String res = callFunc(func, param);
    client.println("HTTP/1.1 200 OK");
    client.printf("Content-type:text/plain\n");
    client.println();
    client.println(res);
    return true;
  }
  return false;
}