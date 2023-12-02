#if !defined(__GET_HANDLER_H)
#define __GET_HANDLER_H
#include "webfiles.h"
#include <Arduino.h>

class WiFiClient;

bool HandleGet(const String& get, WiFiClient& client);

#endif