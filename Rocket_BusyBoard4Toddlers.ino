#include "Toggle.h"
#include "Led.h"
#include "Slider.h"
#include "PixVector.h"
#include "Particle.h"
#include "Rocket.h"
#include "Globals.h"
#include <FastLED.h>

const byte DISPLAY_PIN = 1;

void setup() {
  LedStrip<DISPLAY_PIN, LEDMATRIX_COUNT> theDisplay();
}

void loop() {}