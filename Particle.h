#include "PixVector.h"
#include <FastLED.h>

class Particle {

  public:

    CRGB colour;
    float mass;
    int size;
    PixVector location;
    PixVector velocity;
    PixVector acceleration;

    Particle() {
      colour.setRGB(random(255), random(255), random(255));
      location = PVector(random(63),random(63)));
      velocity = PVector(random(1,3),random(1,3)));
      acceleration = PVector();
      mass = 1;
      size = 1;
    }
  

    public void applyForce(PVector force) {
      PVector f = PVector.div(force,mass);
      acceleration.add(f);
    }

    public void update() {
      velocity.add(acceleration);
      location.add(velocity);
      applyDrag(0.99);
    }

    CRGB[] paint() {
      CRGB[64] matrix; 
      matrix[Location.x + location.y * 8] = colour;
      return matrix;
    }

  protected:

    private void applyDrag(float drag) {
      velocity.mult(drag);
      acceleration.mult(drag);
    }
};

class Planet : public Particle {
  
  public:

    Planet() : Particle { } {
      colour.setRGB(random(255), random(255), random(255));
      location = PVector(random(63),random(63)));
      velocity = PVector(random(1,3),random(1,3)));
      acceleration = PVector();
      mass = random(30) / 3;
      size = 3;
    }

    CRGB[] paint() {
      CRGB[64] matrix; 
      matrix[Location.x + location.y * 8] = colour;
      //These needs to draw a circle.... oh boy :/
      return matrix;
    }

};