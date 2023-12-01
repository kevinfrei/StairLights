// This handles HTTP POST commands
// It's looks for api_<something> and does various arduino-specific stuff

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
  // Serial.println("Nothing found");
  return false;
}
