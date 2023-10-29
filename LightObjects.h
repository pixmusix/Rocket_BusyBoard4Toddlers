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
  bool powered;
  float maxSpeed;
  float maxAccel;
  float speedIncr;
  
  Vect location;
  Vect velocity;
  Vect acceleration;

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

  a.fuel = Fueltank(100.0);
  a.powered = false;
  a.location = Vect();
  a.velocity = Vect();
  a.acceleration = Vect();
  a.maxSpeed = 1;
  a.maxAccel = 15.0;
  a.speedIncr = 0.01;

  return a;
}

Rocket updateRocket(Rocket a) {
  a.velocity.add(a.acceleration);
  a.velocity.limit(a.maxSpeed);
  a.location.add(a.velocity);
  return a;
}

struct HUD {
  CRGB pixels[64];
};

HUD initHUD(HUD a) {
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

Space updateSpace(Space) {
  
}

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
        //Convert from 1D to 2D
        int idx = i + (j * ydim);
        //Convert the display index to this LED tile's index. 
        int subidx = abs(idx + 8) % 16;
        subidx = (subidx + idx) / 2.0;
        subidx = (subidx - 4) % 64;
        //Find the subMatrix number and assign it to the right pixel/
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