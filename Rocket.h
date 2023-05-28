#include "Globals.h"
#include "rocketRGB.h"
#include <FastLED.h>

struct Rocket {
  CRGB pixels[rocketRGBDataSize];
  char fuel;
  bool armed;
};

Rocket initRocket(Rocket a) {
  // Set RBG Pixel Values
  for (int j = 0; j < rocketRGBDataNumRows; j++) {
    for (int i = 0; i < rocketRGBDataNumCols; i++) {
      a.pixels[i+j*rocketRGBDataNumCols].setRGB(
        rocketRGBData[i][j][0], 
        rocketRGBData[i][j][1], 
        rocketRGBData[i][j][2]
      );
    }
  }

  // New Rocket; Needs Fuel
  a.fuel = 0.0;

  // Not armed yet
  a.armed = false;
}