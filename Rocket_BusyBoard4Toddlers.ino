#include "Toggle.h"
#include "Led.h"
#include "Slider.h"
#include "PixVector.h"
#include "Particle.h"
#include "Rocket.h"
#include "Globals.h"
#include <FastLED.h>

const byte DISPLAY_PIN = 41;

/* I wan't some function where I pass in a pointer to LEDStrip and Apollo and merge them*/
// void draw() {
//   for (int i = 0; i < LEDMATRIX_COUNT; i++) {

//   }
// } 

vo/id setup() {
  LedStrip<DISPLAY_PIN, LEDMATRIX_COUNT> theDisplay();
  Rocket Apollo;
  Apollo = initRocket(Apollo); // WHY DOES THIS COMPILE! Isn't Apollo on the stack?? 
}

void loop() {}