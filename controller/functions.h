#if !defined(__FUNCTIONS_H)
#define __FUNCTIONS_H

// This is where all the functions get called from (inside the Post handler)

void leds_off() {
,  Serial.println("LEDS off");
}

void leds_on() {
  Serial.println("LEDS on");
}

void leds_brightness(int adj) {
  Serial.printf("Brightness %d\n", adj);
}

void leds_hue(int adj) {
  Serial.printf("Hue %d\n", adj);
}

void leds_saturation(int adj) {
  Serial.printf("Saturation %d\n", adj);
}

void leds_hmove(int adj) {
  Serial.printf("Horizontal move %d", adj);
}

void leds_vmove(int adj) {
  Serial.printf("Vertical move %d", adj);
}

void leds_style(const String& s) {
  Serial.printf("Style select: %s\n", s);
}

void leds_palette(const String& s) {
  Serial.printf("Palette select: %s\n", s);
}

bool callFunc(const String& funcName, const String& param) {
  if (funcName.equals("off")) {
    leds_off();
  } else if (funcName.equals("on")) {
    leds_on();
  } else if (funcName.equals("brightness")) {
    leds_brightness(param.toInt());
  } else if (funcName.equals("hue")) {
    leds_hue(param.toInt());
  } else if (funcName.equals("saturation")) {
    leds_saturation(param.toInt());
  } else if (funcName.equals("hmove")) {
    leds_hmove(param.toInt());
  } else if (funcName.equals("vmove")) {
    leds_vmove(param.toInt());
  } else if (funcName.equals("style")) {
    leds_style(param);
  } else if (funcName.equals("palette")) {
    leds_palette(param);
  } else {
    return false;
  }
  return true;
}

#endif