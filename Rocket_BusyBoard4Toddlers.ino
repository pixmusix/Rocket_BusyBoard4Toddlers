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
const byte DISPLAYPIN_NW = 22;
const byte DISPLAYPIN_NE = 24;
const byte DISPLAYPIN_SW = 26;
const byte DISPLAYPIN_SE = 28;

const byte RB_IN = 52;
const byte RB_OUT = 50;
const byte DIAL_IN = A0;
const byte BTN_IN = 41;

int phasor = 0;

/* -------------------------------- */

//Objects
struct QuadMatrix {
  LedStrip<DISPLAYPIN_NW, LEDMATRIX_COUNT> NW;
  LedStrip<DISPLAYPIN_NE, LEDMATRIX_COUNT> NE;
  LedStrip<DISPLAYPIN_SW, LEDMATRIX_COUNT> SW;
  LedStrip<DISPLAYPIN_SE, LEDMATRIX_COUNT> SE;

  void drawTo(Led256 px) {
    /* This func splits the 256 element array into 4 64 element arrays.
    It devides the 16x16 square into 4 quadrents of 8x8: NW,NE,SW,SE Quadrants. 
    p and q allows us to clarify which array we need to push to.
    The link below demonstrates the equation that converts the idecies correctly. https://www.desmos.com/calculator/4a8hztwpvy */
    int xdim = LEDDISPLAY_XDIM;
    int ydim = LEDDISPLAY_YDIM;
    Led64 subMatrix[4] = {};
    for (int j = 0; j < ydim; j++) {
      for (int i = 0; i < xdim; i++) {
        int idx = i + (j * ydim);
        int subidx = (int)floor((((idx - 8) % 16) + idx) / 2) % 64;
        int p = floor(i / 8);
        int q = (floor(j / 8) + 1) * 2;
        subMatrix[q + p - 2].matrix[subidx] = px.matrix[idx];
      }
    }
    NW.drawTo(subMatrix[0].matrix);
    NE.drawTo(subMatrix[1].matrix);
    SW.drawTo(subMatrix[2].matrix);
    SE.drawTo(subMatrix[3].matrix);
  }
}; 

Rocket Apollo;
AstroWindow Window;
Space Universe;
QuadMatrix theDisplay;

Dial RedDial = Dial(DIAL_IN); 
LedStrip<RB_OUT, LEDRAINBOW_COUNT> LaunchRainbow;
Button LaunchButton = Button(BTN_IN);

/* -------------------------------- */

//Functions;
void flyGirl(PixVector vec) {
  /* We want the cursor, not the planets, to move with the joystick. 
  Let's make the particles move in the opposite direction.
  The paralax creates the illusion of movement. */
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

/* -------------------------------- */

void setup() { 
  Serial.begin(9600);
  delay(2500);
  Serial.println("Hello <3");

  pinMode(RB_IN, INPUT);
  pinMode(RB_OUT, OUTPUT);
}

void loop() {
  float redDial_Angle = RedDial.getAngle();
  int rb_val = (int)floor(fmap(redDial_Angle, 0.0, TWO_PI, 13.0, 0.0)) + 1;
  if (LaunchButton.isPressed()) {
    LaunchRainbow.sweepTo(rb_val, 200, 6, 15);
  } else {
    LaunchRainbow.meterTo(rb_val, 200, 6, 15);
  }
  delay(33);
  phasor += 1;
}

