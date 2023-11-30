struct DataBuffer {
  size_t len;
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
// below here:
namespace Paths {
constexpr char empty[] = "";
constexpr char index_alias[] = "index.htm";
constexpr char favicon_ico[] = "favicon.ico";
constexpr char index_html[] = "index.html";
constexpr char logo512_png[] = "logo512.png";
constexpr char asset_manifest_json[] = "asset-manifest.json";
constexpr char static_css_main_f855e6bc_css_map[] =
  "static/css/main.f855e6bc.css.map";
constexpr char static_css_main_f855e6bc_css[] = "static/css/main.f855e6bc.css";
constexpr char static_js_main_63bb059d_js_LICENSE_txt[] =
  "static/js/main.63bb059d.js.LICENSE.txt";
constexpr char static_js_main_63bb059d_js_map[] =
  "static/js/main.63bb059d.js.map";
constexpr char static_js_main_63bb059d_js[] = "static/js/main.63bb059d.js";
constexpr char static_media_logo_6ce24c58023cc2f8fd88fe9d219db6c6_svg[] =
  "static/media/logo.6ce24c58023cc2f8fd88fe9d219db6c6.svg";
constexpr char manifest_json[] = "manifest.json";
constexpr char logo192_png[] = "logo192.png";
} // namespace Paths

namespace Contents {
constexpr char index_html[] =
  "<html><head><title>Web Server</title></head><body><h1>Hello "
  "world!</h1></body></html>";
constexpr char manifest_json[] =
  "{\n\"short_name\": \"React App\",\n\"name\": \"Create React App "
  "Sample\",\n\"icons\": [\n{\n\"src\": \"favicon.ico\",\n\"sizes\": \"64x64 "
  "32x32 24x24 16x16\",\n\"type\": \"image/x-icon\"\n},\n{\n\"src\": "
  "\"logo192.png\",\n\"type\": \"image/png\",\n\"sizes\": "
  "\"192x192\"\n},\n{\n\"src\": \"logo512.png\",\n\"type\": "
  "\"image/png\",\n\"sizes\": \"512x512\"\n}\n],\n\"start_url\": "
  "\".\",\n\"display\": \"standalone\",\n\"theme_color\": "
  "\"#000000\",\n\"background_color\": \"#ffffff\"\n}";
} // namespace Contents

constexpr WebMap FileList[] = {
  // Sizes are wrong, but you get the point
  {Mime::html, {10, Paths::index_html}, {51, Contents::index.html}},
  {Mime::html, {0, Paths::empty}, {51, Contents::index.html}},
  {Mime::html, {9, Paths::index_alias}, {51, Contents::index.html}},
  {Mime::json, {10, Paths::manifest_json}, {101, Contents::manifest_json}},
};
