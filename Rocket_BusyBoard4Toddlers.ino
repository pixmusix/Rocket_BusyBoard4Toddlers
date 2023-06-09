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

void setup() {
  Serial.begin(4800);
  delay(1000);
  Serial.println("Hello <3");
}

void loop() {
}

// const byte DISPLAY_PIN = 41;
// LedStrip<DISPLAY_PIN, LEDMATRIX_COUNT> theDisplay;
// Rocket Apollo;
// AstroWindow Window;
// Space Universe;

// void flyGirl(PixVector vec) {
//   /*We don't want the planets to move in the direction of the joystick.
//   Instead we want us, the cursor to move with the joystick. 
//   The simplest way is to make the planets move in the opposite direction.
//   This creates the illusion of movement. */
//   vec.mult(-1);

//   for (int i = 0; i < Universe.particles.getSize(); i++) {
//     Universe.particles[i].applyForce(vec);
//   }
//     for (int i = 0; i < Universe.moons.getSize(); i++) {
//     Universe.moons[i].applyForce(vec);
//   }
//   for (int i = 0; i < Universe.planets.getSize(); i++) {
//     Universe.planets[i].applyForce(vec);
//   }
//   for (int i = 0; i < Universe.giants.getSize(); i++) {
//     Universe.giants[i].applyForce(vec);
//   }
// }

// void paintTheSky() {
//   for (int i = 0; i < Universe.particles.getSize(); i++) {
//     theDisplay.drawTo(Universe.particles[i].paint().matrix);
//   }
//   for (int i = 0; i < Universe.moons.getSize(); i++) {
//     theDisplay.drawTo(Universe.moons[i].paint().matrix);
//   }
//   for (int i = 0; i < Universe.planets.getSize(); i++) {
//     theDisplay.drawTo(Universe.planets[i].paint().matrix);
//   }
//   for (int i = 0; i < Universe.giants.getSize(); i++) {
//     theDisplay.drawTo(Universe.giants[i].paint().matrix);
//   }
// }

// void setup() { 
//   Apollo = initRocket(Apollo);
//   theDisplay.drawTo(Apollo.pixels);

//   theDisplay.clearAll();
  
//   Window = initAstroWindow(Window);
//   theDisplay.drawTo(Window.pixels);

//   Universe = letThereBeLight(Universe);


// }

// void loop() {
//   PixVector v = PixVector();
//   v.randFloat();
//   flyGirl(v);
//   paintTheSky();
// }

