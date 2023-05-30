#include "Globals.h"
#include "RGBData.h"
#include "Particle.h"
#include <FastLED.h>
#include <List.hpp>

struct Rocket {
  CRGB pixels[64];
  char fuel;
  bool armed;
};

/* Populate a Rocket with Default Values */
Rocket initRocket(Rocket a) {
  // Set RBG Pixel Values
  for (int j = 0; j < 16; j++) {
    for (int i = 0; i < 16; i++) {
      a.pixels[i+j*16].setRGB(
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

  return a;
}

struct AstroWindow {
  CRGB pixels[64];
};

AstroWindow initAstroWindow(AstroWindow a) {
  // Set RBG Pixel Values
  for (int j = 0; j < 16; j++) {
    for (int i = 0; i < 16; i++) {
      a.pixels[i+j*16].setRGB(
        crosshairRGBData[i][j][0], 
        crosshairRGBData[i][j][1], 
        crosshairRGBData[i][j][2]
      );
    }
  }

  return a;
}

struct Space {
  List<Particle> particles;
  List<Planet> planets;
  List<Moon> moons;
  List<GiantPlanet> giants;
};

Space letThereBeLight(Space a) {
  //Am I creating 5 different particles or 1 particle in 3 memory locations?
  for (int i = 0; i < 5; i++) {
    Particle p = Particle();  
    a.particles.addLast(p);
  }
  for (int i = 0; i < 3; i++) {
    Moon m = Moon();  
    a.moons.addLast(m);
  }
  for (int i = 0; i < 2; i++) {
    Planet p = Planet();  
    a.planets.addLast(p);
  }
  for (int i = 0; i < 1; i++) {
    GiantPlanet g = GiantPlanet();  
    a.giants.addLast(g);
  }
}