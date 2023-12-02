#if !defined(__POST_HANDLER_H)
#define __POST_HANDLER_H

class String;
class WiFiClient;

String callFunc(const String& funcName, const String& param);
// This handles HTTP POST commands
// It's looks for api_<something> and does various arduino-specific stuff

bool HandlePost(const String& post, WiFiClient& client);

#endif