#include "rocketRGB.h"
#include <FastLED.h>

struct Rocket {
  CRGB pixels[64];
  char fuel;
  bool armed;
};

Rocket initRocket(Rocket a) {
  // Set RBG Pixel Values
  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 8; i++) {
      a.pixels[i+j*8].setRGB(rocketRGBData[i][j][0], rocketRGBData[i][j][1], rocketRGBData[i][j][2]);
    }
  }

  // New Rocket; Needs Fuel
  a.fuel = 0.0;

  // Not armed yet
  a.armed = false;
}