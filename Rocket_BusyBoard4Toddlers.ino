#include "Toggle.h"
#include "Led.h"
#include "Slider.h"
#include "SevSegs.h"
#include "PixVector.h"
#include "Particle.h"
#include "LightObjects.h"
#include "Globals.h"
#include <FastLED.h>
#include <TM1637Display.h>
#include <Keypad.h>

//Pin Definitions
const int DISPLAYPIN_NW = 22;
const int DISPLAYPIN_NE = 24;
const int DISPLAYPIN_SW = 26;
const int DISPLAYPIN_SE = 28;

//Objects
struct QuadMatrix {
  LedStrip<DISPLAYPIN_NW, LEDMATRIX_COUNT> NW;
  LedStrip<DISPLAYPIN_NE, LEDMATRIX_COUNT> NE;
  LedStrip<DISPLAYPIN_SW, LEDMATRIX_COUNT> SW;
  LedStrip<DISPLAYPIN_SE, LEDMATRIX_COUNT> SE;

  void drawTo(Led256) {
    //Logic to draw to display (unwrapping the matrix)
  }
};

Rocket Apollo;
AstroWindow Window;
Space Universe;
QuadMatrix theDisplay;


//Functions;
void flyGirl(PixVector vec) {
  /*We don't want the planets to move in the direction of the joystick.
  Instead we want us, the cursor to move with the joystick. 
  The simplest way is to make the planets move in the opposite direction.
  This creates the illusion of movement. */
  vec.mult(-1);

  for (int i = 0; i < Universe.particles.getSize(); i++) {
    Universe.particles[i].applyForce(vec);
  }
    for (int i = 0; i < Universe.moons.getSize(); i++) {
    Universe.moons[i].applyForce(vec);
  }
  for (int i = 0; i < Universe.planets.getSize(); i++) {
    Universe.planets[i].applyForce(vec);
  }
  for (int i = 0; i < Universe.giants.getSize(); i++) {
    Universe.giants[i].applyForce(vec);
  }
}

void paintTheSky() {
  for (int i = 0; i < Universe.particles.getSize(); i++) {
    theDisplay.drawTo(Universe.particles[i].paint());
  }
  for (int i = 0; i < Universe.moons.getSize(); i++) {
    theDisplay.drawTo(Universe.moons[i].paint());
  }
  for (int i = 0; i < Universe.planets.getSize(); i++) {
    theDisplay.drawTo(Universe.planets[i].paint());
  }
  for (int i = 0; i < Universe.giants.getSize(); i++) {
    theDisplay.drawTo(Universe.giants[i].paint());
  }
}

void setup() { 
  Serial.begin(4800);
  Serial.println("Hello <3");
}

void loop() {
}

