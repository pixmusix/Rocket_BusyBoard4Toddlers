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
HUD HUDWindow;
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
Rocket fly(Rocket a) {
  Vect v = Vect();
  float s = a.speedIncr;
  float m = 0.0;
  m += AltKey.isPressed() ? s : 0.0;
  m -= CtrlKey.isPressed() ? s : 0.0;
  m *= min(LaunchButton.getElapsed(), 50.0);
  v.setHeading(YawDial.getAngle());
  v.setMag(m);
  a.acceleration.add(v);
  return updateRocket(a);
}

void shiftParticles(Vect vec) {
  /* We want the cursor, not the planets, to move with the joystick. 
  Let's make the particles move in the opposite direction.
  The paralax creates the illusion of movement. */
  vec.mult(-1);
  Vect centre = Vect(LEDDISPLAY_XDIM / 2.0, LEDDISPLAY_YDIM / 2.0);

  for (int i = 0; i < Universe.particles.getSize(); i++) {
    Universe.particles[i].applyForce(vec);
    if (Universe.particles[i].location.dist(centre) > sqrt(MAP_SIZE)) {
      Universe.particles.remove(i);
    }
  }
    for (int i = 0; i < Universe.moons.getSize(); i++) {
    Universe.moons[i].applyForce(vec);
    if (Universe.moons[i].location.dist(centre) > sqrt(MAP_SIZE)) {
      Universe.moons.remove(i);
    }
  }
  for (int i = 0; i < Universe.planets.getSize(); i++) {
    Universe.planets[i].applyForce(vec);
    if (Universe.planets[i].location.dist(centre) > sqrt(MAP_SIZE)) {
      Universe.planets.remove(i);
    }
  }
  for (int i = 0; i < Universe.giants.getSize(); i++) {
    Universe.giants[i].applyForce(vec);
    if (Universe.giants[i].location.dist(centre) > sqrt(MAP_SIZE)) {
      Universe.giants.remove(i);
    }
  }
}

void fillTheVoid() {
  unsigned long e = (int)floor(millis() / 1000);
  if (e % 120 == 0 & Universe.giants.getSize() < 5) {
    GiantPlanet g = GiantPlanet();
    Universe.giants.add(g);
  }
  if (e % 50 == 0 & Universe.giants.getSize() < 12) {
    Planet p = Planet();
    Universe.planets.add(p);
  }
  if (e % 10 == 0 & Universe.giants.getSize() < 20) {
    Moon m = Moon();
    Universe.moons.add(m);
  }
  if (e % 1 == 0 & Universe.giants.getSize() < 100) {
    Particle p = Particle();
    Universe.particles.add(p);
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
  bool notArmed = !BallisticSwitch.isArmed();
  bool lowFuel = Apollo.fuel.getFuelGage() < 0.05;
  bool overHeated = Apollo.acceleration.mag() > Apollo.maxAccel;
  return notArmed | lowFuel | overHeated;
}

/* -------------------------------- */

void render() {
  // Handle all three states of LED
  if (evaluateArmed() & !Apollo.powered) {
    LaunchLed.blink();
  } else {
    LaunchLed.off();
  }
  if (Apollo.powered) {
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
  if (!Apollo.powered) {
    Apollo.powered = evaluateLaunch();
  } else {
    Apollo = fly(Apollo);
    Apollo.powered = !evaluateStall();
  }

  // Draw to the display.
  shiftParticles(Apollo.velocity);
  fillTheVoid();
  paintTheSky();
}

