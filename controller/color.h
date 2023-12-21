// The idea is something like this:
// There's a list of HSV points with "time to next" in 10th's of a second
// The list of color points & times is a "palette":
// So, Red 500, Green 500, Blue 500 will slowing move from R to G to B every 1.5 seconds
// The current position would be an index, and start time (when we hit that index)

struct ColorPoint {
  uint8_t H, S, V;
  uint8_t time;
};

// Time is a fraction of the 'speed', 0 to 255

constexpr ColorPoint Red5 = {0, 0xff, 0xff, 50};
constexpr ColorPoint Grn5 = {60, 0xFF, 0xFF, 50};
constexpr ColorPoint Blu5 = {120, 0xFF, 0xFF, 50};
constexpr ColorPoint Wht5 = {0, 0, 0xFF, 50};
constexpr ColorPoint Blk5 = {0, 0, 0, 50};
// For going between Red & Green, without too much yellow in the middle?
constexpr ColorPoint R2G5 = {30, 0x30, 0xe0, 50};

using Palette = std::vector<ColorPoint>;

// 4 points along the way for christmas?
Palette Christmas{Red5, R2G5, Grn5, R2G5};
// Just 3 for July 4th:
Palette July4th{Red5, Blu5, Wht5};

// PixelPosition is where a given pixel is in the Palette:
struct PixelPosition {
  uint32_t index: 8;
  uint32_t time: 24; // As a fraction of the way through the time
};




