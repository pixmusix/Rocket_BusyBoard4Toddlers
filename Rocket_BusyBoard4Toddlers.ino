#include "Toggle.h"
#include "Led.h"
#include "Slider.h"
#include "PixVector.h"
#include "Particle.h"
#include "LightObjects.h"
#include "Globals.h"
#include <FastLED.h>

const byte DISPLAY_PIN = 41;
Rocket Apollo;
AstroWindow window;
Space universe;

void flyGirl(PixVector vec) {
  for (int i = 0; i < universe.particles.getSize(); i++) {
    universe.particles[i].applyForce(vec);
  }
    for (int i = 0; i < universe.moons.getSize(); i++) {
    universe.moons[i].applyForce(vec);
  }
  for (int i = 0; i < universe.planets.getSize(); i++) {
    universe.planets[i].applyForce(vec);
  }
  for (int i = 0; i < universe.giants.getSize(); i++) {
    universe.giants[i].applyForce(vec);
  }
}

void setup() {
  //Init the display
  LedStrip<DISPLAY_PIN, LEDMATRIX_COUNT> theDisplay;
  //Create and init the Rocket
  
  Apollo = initRocket(Apollo); // WHY DOES THIS COMPILE! Isn't Apollo on the stack??
  //Draw the Rocket to the LED
  theDisplay.drawTo(Apollo.pixels);

  //Draw the Crosshair
  theDisplay.clearAll();
  
  window = initAstroWindow(window);
  theDisplay.drawTo(window.pixels);

  universe = letThereBeLight(universe);
}

void loop() {
  PixVector v = PixVector();
  v.randFloat();
  flyGirl(v);
}

