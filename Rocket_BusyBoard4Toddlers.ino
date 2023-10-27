#include "Toggle.h"
#include "Led.h"
#include "Slider.h"
#include "SevSegs.h"
#include "Vect.h"
#include "Particle.h"
#include "LightObjects.h"
#include "Globals.h"
#include <FastLED.h>
#include <TM1637Display.h>
#include <Keypad.h>

/* -------------------------------- */
//Objects
Rocket Apollo;
AstroWindow Window;
Space Universe;
QuadMatrix theDisplay;

Switch BallisticSwitch = Switch(ARMINGSWITCH_PIN);
Dial YawDial = Dial(YAWDIAL_PIN);
Button LaunchButton = Button(LAUNCHBUTTON_PIN);
LedStrip<RAINBOW_PIN, LEDRAINBOW_COUNT> Rainbow;
Led LaunchLed = Led(LAUNCHLED_PIN);
Toggle MonitorSwitch = Toggle(MONITORSWITCH_PIN);
Button CtrlKey = Button(CTRLBUTTON_PIN);
Button AltKey = Button(ALTBUTTON_PIN);
Joystick<JOYX_PIN, JOYY_PIN> JoyXY;

/* -------------------------------- */

//Functions;
void flyGirl(Vect vec) {
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

bool evaluateArmed() {
  return BallisticSwitch.isArmed() & YawDial.getValue() > 1000;
}

bool evaluateLaunch() {
  return evaluateArmed() & LaunchButton.isPressed();
}

bool evaluateStall() {
  return Apollo.fuel.getFuelGage() < 0.05 | Apollo.velocity.mag() > 15.0;
}

/* -------------------------------- */

void render() {
  // Handle all three states of LED
  if (evaluateArmed() & !Apollo.inTheSky) {
    LaunchLed.blink();
  } else {
    LaunchLed.off();
  }
  if (Apollo.inTheSky) {
    LaunchLed.on();
  }

  // Draw to the rainbow.

  // Tell the latch we have completed our render.
  digitalWrite(LATCH, HIGH);
  digitalWrite(LATCH, LOW);
}

void setup() { 
  Serial.begin(9600);

  pinMode(INTERRUPT, INPUT_PULLUP);
  pinMode(LATCH, OUTPUT);
  digitalWrite(LATCH, LOW);
  
  attachInterrupt(digitalPinToInterrupt(INTERRUPT), render, RISING);

  Apollo = initRocket(Apollo);
  theDisplay.drawTo(Apollo.getLed256());
}

void loop() {
  Apollo.isArmed = evaluateArmed();
  if (!Apollo.inTheSky) {
    Apollo.inTheSky = evaluateLaunch();
  } else {
    Apollo.inTheSky = evaluateStall();
  }
  // Draw to the display.
  paintTheSky();
}

