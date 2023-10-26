/* This header file contains objects representing pixel collections for rendering on our LEDs. */

#include "Globals.h"
#include "RGBData.h"
#include "Particle.h"
#include <FastLED.h>
#include <List.hpp>

Led256 getLEDDisplayTestImg() {
  Led256 displayTestImg;
  for (int i = 0; i < 256; i++) {
    CRGB pix;
    int m = 40;
    int v = map(i, 0, 255, 0, m);
    pix.setRGB(v, 0, m - v);
    displayTestImg.matrix[i] = pix;
  }
  return displayTestImg;
}

class Fueltank {

  private:
    float capacity;
    float fuel;
  
  public:
    bool empty;
    
    Fueltank(float cap) {
      capacity = cap;
      push(cap);
    }

    Fueltank() {
      capacity = 0.0;
      fuel = 0.0;
      empty = true;
    }

    float getFuelVal() {
      return fuel;
    }

    float getFuelGage() {
      return (fuel / capacity) * 100.0;
    }

    float pull(float f) {
      fuel -= f;
      empty = (fuel <= 0.0);
      return empty ? f - fuel : f;
    }

    void push(float f) {
      fuel += min(f, capacity);
      empty = (fuel <= 0.0);
    }
};

struct Rocket {
  CRGB pixels[256];
  Fueltank fuel;
  bool isArmed;
  bool inTheSky;
  
  Vect location;
  Vect velocity;
  Vect acceleraton;

  Led256 getLed256() {
    Led256 leds;
    for (int i = 0; i < 256; i++) {
      leds.matrix[i] = pixels[i];
    }
    return leds;
  }
};

/* Populate a Rocket with Default Values */
Rocket initRocket(Rocket a) {
  // Set RBG Pixel Values
  for (int j = 0; j < LEDDISPLAY_YDIM; j++) {
    for (int i = 0; i < LEDDISPLAY_XDIM; i++) {
      a.pixels[i+j*LEDDISPLAY_YDIM].setRGB(
        rocketRGBData[i][j][0], 
        rocketRGBData[i][j][1], 
        rocketRGBData[i][j][2]
      );
    }
  }

  // New Rocket; Needs Fuel
  a.fuel = Fueltank(100.0);
  // Not armed yet
  a.isArmed = false;
  // Nor flying
  a.inTheSky = false;
  a.location = Vect();
  a.velocity = Vect();
  a.acceleraton = Vect();

  return a;
}

struct AstroWindow {
  CRGB pixels[64];
};

AstroWindow initAstroWindow(AstroWindow a) {
  // Set RBG Pixel Values
  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 8; i++) {
      a.pixels[i+j*8].setRGB(
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