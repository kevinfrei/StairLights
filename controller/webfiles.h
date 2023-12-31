#if !defined(__WEB_FILES_H)
#define __WEB_FILES_H

#include <stdint.h>

struct DataBuffer {
  uint32_t len;
  const char* data;
};

struct WebFile {
  const char* mimeType;
  const DataBuffer pathname;
  const DataBuffer content;
};

namespace Mime {
constexpr char html[] = "text/html";
constexpr char png[] = "image/png";
constexpr char jpg[] = "image/jpeg";
constexpr char svg[] = "image/svg+xml";
constexpr char css[] = "text/css";
constexpr char js[] = "application/javascript";
constexpr char json[] = "application/json";
constexpr char map[] = "application/json";
constexpr char ico[] = "image/x-icon";
constexpr char txt[] = "text/plain";
} // namespace Mime

// Everything below here should be generated by the script processing web
// content Probably should just #include "webcontent.h" instead of putting it

#include "webcontent.h"

#endif