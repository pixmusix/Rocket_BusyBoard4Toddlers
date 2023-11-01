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
Space Universe;
QuadMatrix theDisplay;

Switch BallisticSwitch = Switch(ARMINGSWITCH_PIN);
Dial YawDial = Dial(YAWDIAL_PIN);
Button LaunchButton = Button(LAUNCHBUTTON_PIN);
LedStrip<RAINBOW_PIN, LEDRAINBOW_COUNT> Rainbow;
Led LaunchLed = Led(LAUNCHLED_PIN);
LedStrip<STRIPLED_PIN, LEDSTRIP_COUNT> FuelStrip;
Button CtrlKey = Button(CTRLBUTTON_PIN);
Button AltKey = Button(ALTBUTTON_PIN);
Joystick<JOYX_PIN, JOYY_PIN> JoyXY;
SevenSegment<SEVSEG_PIN, SEVSEG_CLK> Accelo;

/* -------------------------------- */

//Functions;
Rocket fly(Rocket a) {
  a.fuel.push(0.01);
  Vect v = JoyXY.getVector();
  v.mult(a.speedIncr);
  v.x = 0.0;
  a.acceleration.y += a.fuel.pull(v.y);
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
    Universe.particles[i].location.shiftHeading(YawDial.getAngleChange());
  }
    for (int i = 0; i < Universe.moons.getSize(); i++) {
    Universe.moons[i].applyForce(vec);
    if (Universe.moons[i].location.dist(centre) > sqrt(MAP_SIZE)) {
      Universe.moons.remove(i);
    }
    Universe.moons[i].location.shiftHeading(YawDial.getAngleChange());
  }
  for (int i = 0; i < Universe.planets.getSize(); i++) {
    Universe.planets[i].applyForce(vec);
    if (Universe.planets[i].location.dist(centre) > sqrt(MAP_SIZE)) {
      Universe.planets.remove(i);
    }
    Universe.planets[i].location.shiftHeading(YawDial.getAngleChange());
  }
  for (int i = 0; i < Universe.giants.getSize(); i++) {
    Universe.giants[i].applyForce(vec);
    if (Universe.giants[i].location.dist(centre) > sqrt(MAP_SIZE)) {
      Universe.giants.remove(i);
    }
    Universe.giants[i].location.shiftHeading(YawDial.getAngleChange());
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

  // Handle to the rainbow. It's going to handle our motion feedback.
  Rainbow.clearAll();
  if (AltKey.isPressed() & CtrlKey.isPressed()) {
    /* Random noise to indicate incorrect behaviour */
    Rainbow.setRandomAll();
  } else if (AltKey.isPressed()) {
    /* Display current acceleration.*/
    float m = Apollo.acceleration.mag();
    int c = (int)floor((m/Apollo.maxAccel) * 255.0);
    Rainbow.sweepTo(m, c, 25.0, c);
  } else if (CtrlKey.isPressed()) {
    /* Display current Velocity.*/
    float m = Apollo.velocity.mag();
    int c = (int)floor((m/Apollo.maxSpeed) * 255.0);
    Rainbow.sweepTo(m, 25, c, 40);
  } else {
    /* Put a dot on our current tradjectory.
      Green for forward, blue for backwards. */
    Rainbow.setAll(15,20,15);
    byte tradj_green = min((int)ceil(Apollo.velocity.mag()), 255);
    byte tradj_blue = 255 - min((int)ceil(Apollo.velocity.mag()), 255);
    float tradj = fmap(Apollo.velocity.getHeading(), 0.0, PI, 0.0, 14.0);
    Rainbow.setPix((int)tradj, 0, tradj_green, tradj_blue);
    /* Put red a dot for where our yaw dial is pointing*/
    float yaw = fmap(YawDial.getAngle(), 0.0, TWO_PI, 0.0, 14.0);
    Rainbow.setPix(yaw, 187, 0, 0);
  }
  Rainbow.ledPop();

  // Handle the strip. This is our fuel gage.
  float remainingFuel = fmap(Apollo.fuel.getFuelGage(), 0.0, 100.0, 0.0, 14.0);
  FuelStrip.clearAll();
  FuelStrip.meterTo(int(remainingFuel), 200, 177, 42);
  FuelStrip.ledPop();

  // Draw the rocket and space particles to the display.
  paintTheSky();
  theDisplay.drawTo(Apollo.getLed256());
  theDisplay.pop();

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

  Universe = letThereBeLight(Universe);
  Apollo = initRocket(Apollo);
  
}

void loop() {
  // Write the joystick to accelerometer.
  Vect JoyVector = JoyXY.getVector();
  JoyVector.mult(255.0);
  Accelo.displayVect(JoyVector);

  //Handle Apollos motion.
  if (!Apollo.powered) {
    Apollo.powered = evaluateLaunch();
    Apollo.loadBitMap_Rocket();
  } else {
    Apollo = fly(Apollo);
    Apollo.swapBitMapBySpeed();
    Apollo.powered = !evaluateStall();
  }

  // Handle the universe motion.
  shiftParticles(Apollo.velocity);
  fillTheVoid();
}

