// My stairway is 14 stairs, 4 LED's each

constexpr int kNumStairs = 14;
constexpr int kLedPerStep = 4;

constexpr uint8_t stair_led[kNumStairs * kLedPerStep] = {
  0,1,2,3,
  4,5,6,7,
  8,9,10,11
  12,13,14,15
  16,17,18,19,
  20,21,22,23,
  24,25,26,27,
  28,29,30,31,
  35,34,33,32,
  36,37,38,39,
  40,41,42,43,
  44,45,46,47,
  48,49,50,51,
  52,53,54,55
};

uint32_t stair_values[kNumStairs * kLedPerStep];

void setStair(uint32_t rgb, uint8_t step) {
  for (int i=0; i<kLedPerStep; ++i) {
    led_set_rgb(stair_led[step*kLedPerStep + i], rgb);
  }
}

void setStair(uint32_t rgba, uint32_t rgbb, uint32_t rgbc, uint32_t rgbd, uint8_t step) {
  led_set_rgb(stair_led[step*kLedPerStep + 0], rgba);
  led_set_rgb(stair_led[step*kLedPerStep + 1], rgbb);
  led_set_rgb(stair_led[step*kLedPerStep + 2], rgbc);
  led_set_rgb(stair_led[step*kLedPerStep + 3], rgbd);
}

void setColumn(uint32_t rgb, uint8_t column) {
  for (int i = 0; i < kNumStairs; ++i) {
    led_set_rgb(stair_led[kLedPerStep * i + column], rgb);
  }
}

void setStairs(uint32_t rgb) {
  for (int i = 0; i < kNumStairs; ++i) {
    setStair(rgb, i);
  }
}

uint32_t colors[] = {
 [0] = 0xFF0000, // Red
 [1] = 0x00FF00, // Green
 [2] = 0x0000FF, // Blue,
 [3] = 0xFFFF00, // Yellow,
 [4] = 0xFF00FF, // Purple,
 [5] = 0x00FFFF, // Cyan,
 [6] = 0xFFFFFF, // White,
 [7] = 0x000000, // Black,
};

// I probably want some HSV values for stuff instead, really
