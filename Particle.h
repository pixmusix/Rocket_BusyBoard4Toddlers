
#pragma once
#include "PixVector.h"
#include <FastLED.h>
#include "Globals.h"


/* A sizelss, massless single point with basic euclidean movement */
class Particle {

  protected:

    void applyDrag(float drag) {
      velocity.mult(drag);
      acceleration.mult(drag);
    }

    /* Returns a PixVector somewhere within the LED Display. */
    PixVector randVec64() {
      // Currently always returns the same pseudo random number.
      // Must return here to feed in noise.
      int ledsize = LEDMATRIX_COUNT;
      int rx = random(ledsize);
      int ry = random(ledsize);
      return PixVector(rx, ry);
    }

  public:

    byte red;
    byte green;
    byte blue;
    float mass;
    int size;
    PixVector location;
    PixVector velocity;
    PixVector acceleration;

    Particle() {
      red = random(256);
      green = random(256);
      blue = random(256);
      location = randVec64();
      velocity = PixVector(random(1,3),random(1,3));
      acceleration = PixVector();
      mass = 1;
      size = 1;
    }

    void applyForce(PixVector force) {
      force.div(mass);
      acceleration.add(force);
    }

    void update() {
      velocity.add(acceleration);
      location.add(velocity);
      applyDrag(0.99);
    }

    /* Returns an CRGB Array reprosenting the position of this particle*/
    Led256 paint() {
      Led256 grid;
      int ledX = LEDDISPLAY_XDIM;
      int ledY = LEDDISPLAY_YDIM;
      PixVector loc = location;
      loc.wrap(min(ledX, ledY));
      loc.absolute();
      float idx = loc.x + (loc.y * ledY);
      grid.matrix[(int)idx].setRGB(red, green, blue);
      return grid;
    }
};

/* A planet is a particle with size and mass */
class Planet : public Particle {
  
  public:

    Planet() : Particle { } {
      red = random(256);
      green = random(256);
      blue = random(256);
      location = randVec64();
      velocity = PixVector(random(1,3),random(1,3));
      acceleration = PixVector();
      mass = random(20, 40) / 3;
      size = 6;
    }

    /* Return an CRGB Array reprosenting the position of this Planet*/
    Led256 paint() {
      Led256 grid;
      int ledX = LEDDISPLAY_XDIM;
      int ledY = LEDDISPLAY_YDIM;
      for (int j = 0; j < ledX; j++) {
        for (int i = 0; i < ledY; i++) {
          PixVector idx = PixVector(i,j);
          PixVector loc = location;
          loc.wrap(min(ledX, ledY));
          loc.absolute();
          float h = idx.dist(loc);
          if (h < size) {
            int r = red - ceil(h);
            int g = green - ceil(h);
            int b = blue - ceil(h);
            grid.matrix[i + j * ledX].setRGB(r,g,b);
          }
        }
      }
      return grid;
    }
};

/* a moon is just a small planet */
class Moon : public Planet {
  
  public:

    /* Return an CRGB Array reprosenting the position of this Moon*/
    Moon() : Planet { } {
      red = random(256);
      green = random(256);
      blue = random(256);
      location = randVec64();
      velocity = PixVector(random(1,5),random(1,5));
      acceleration = PixVector();
      mass = random(20, 40) / 6;
      size = 3;
    }
};

/* a giant is just a big planet */
class GiantPlanet : public Planet {
  
  public:

    /* Return an CRGB Array reprosenting the position of this Giant*/
    GiantPlanet() : Planet { } {
      red = random(256);
      green = random(256);
      blue = random(256);
      location = randVec64();
      velocity = PixVector(1,1);
      acceleration = PixVector();
      mass = random(30, 50);
      size = 10;
    }
};