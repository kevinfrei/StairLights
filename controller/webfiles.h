struct WebFile {
  const char *mimeType;
  size_t dataSize;
  const unsigned char *buffer;
};

struct WebMap {
  const unsigned short pathLen;
  const char *path;
  const WebFile *file;
};

namespace Mime {
  constexpr char html[] = "text/html";
}

namespace Path {
  constexpr char index_html1[] = "index.html";
  constexpr char index_html2[] = "";
  constexpr char index_html3[] = "index.htm";
  constexpr char index2_html1[] = "index2.html";
}

namespace Buffer {
  constexpr unsigned char index_html1[] = "<html><head></head><body>Hello, World</body></html>";
  constexpr unsigned char index2_html1[] = "<html><head></head><body>Howdy, World</body></html>";
}

// Web files:
namespace Files {
  constexpr WebFile index_html1 { Mime::html, 51, Buffer::index_html1 };
  constexpr WebFile index2_html1 { Mime::html, 51, Buffer::index2_html1 };
}

constexpr WebMap FileList[] {
  {10, Path::index_html1, &Files::index_html1},
  {0, Path::index_html2, &Files::index_html1},
  {9, Path::index_html3, &Files::index_html1},
  {11, Path::index2_html1, &Files::index2_html1},
};

