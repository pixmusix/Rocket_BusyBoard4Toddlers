
#pragma once
#include "Vect.h"
#include <FastLED.h>
#include "Globals.h"


/* A sizelss, massless single point with basic euclidean movement */
class Particle {

  protected:

    void applyDrag(float drag) {
      velocity.mult(drag);
      acceleration.mult(drag);
    }

    /* Returns a Vect somewhere within the LED Display. */
    Vect randVec64() {
      // Currently always returns the same pseudo random number.
      // Must return here to feed in noise.
      int ledsize = LEDMATRIX_COUNT;
      int rx = random(ledsize);
      int ry = random(ledsize);
      return Vect(rx, ry);
    }

    /* Get a loctation (but it can't be in the DISPLAY or out of MAP) */
    Vect spawn() {
      location = randVec64();
      // Force it to be on the map
      location.wrap(MAP_XDIM);
      // check if it's too close to the display
      if (location.dist(Vect(8.5,8.5)) < 16) {
        // lol...
        return spawn()
      }
      return location;
    }

  public:

    byte red;
    byte green;
    byte blue;
    float mass;
    int size;
    Vect location;
    Vect velocity;
    Vect acceleration;

    Particle() {
      red = random(256);
      green = random(256);
      blue = random(256);
      location = spawn();
      velocity = Vect(random(1,3),random(1,3));
      acceleration = Vect();
      mass = 1;
      size = 1;
    }

    void applyForce(Vect force) {
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
      // First we draw it to the map.
      Led4096 canvas;
      float idx = location.x + (location.y * MAP_XDIM);
      canvas.matrix[(int)idx].setRGB(red, green, blue);
      
      // Then we take only the subset of that that corresponds to the display
      Led256 grid;
      // These offsets shift the display NW by half it's width
      int offsetY = (int)floor(LEDDISPLAY_YDIM / 2);
      int offsetX = (int)floor(LEDDISPLAY_XDIM / 2);
      for (int j = offsetY * -1; j < LEDDISPLAY_YDIM * MAP_YDIM - offsetY; j = j + MAP_YDIM) {
        for (int i = offsetX * -1; i < offsetX; i++) {
          grid.matrix[i,j/MAP_YDIM] = canvas[i,j]
        }
      }
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
      location = spawn();
      velocity = Vect(random(1,3),random(1,3));
      acceleration = Vect();
      mass = random(20, 40) / 3;
      size = 6;
    }

    /* Return an CRGB Array reprosenting the position of this Planet*/
    Led256 paint() {
      // We draw the plannet for indexes within our size_range of the IDX
      Led4096 canvas;
      for (int j = 0; j < MAP_YDIM; j++) {
        for (int i = 0; i < MAP_XDIM; i++) {
          Vect idx = Vect(i,j);
          float hypo = location.dist(idx);
          if (h < size) {
            int r = red - ceil(hypo);
            int g = green - ceil(hypo);
            int b = blue - ceil(hypo);
            grid.matrix[i + j * ledX].setRGB(r,g,b);
          }
        }
      }

      // Then we take only the subset of that that corresponds to the display
      Led256 grid;
      // These offsets shift the display NW by half it's width
      int offsetY = (int)floor(LEDDISPLAY_YDIM / 2);
      int offsetX = (int)floor(LEDDISPLAY_XDIM / 2);
      for (int j = offsetY * -1; j < LEDDISPLAY_YDIM * MAP_YDIM - offsetY; j = j + MAP_YDIM) {
        for (int i = offsetX * -1; i < offsetX; i++) {
          grid.matrix[i,j/MAP_YDIM] = canvas[i,j]
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
      location = spawn();
      velocity = Vect(random(1,5),random(1,5));
      acceleration = Vect();
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
      location = spawn();
      velocity = Vect(1,1);
      acceleration = Vect();
      mass = random(30, 50);
      size = 10;
    }
};