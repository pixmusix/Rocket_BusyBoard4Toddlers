#include "Vect.h"
#include "Globals.h"

/* Abstracts a variable resistor with non-binary state. */
class Slider {
  
  protected:
    byte pin;
    int val;

    void update() {
      val = analogRead(pin);
    }
  
  public:

    Slider() {}

    Slider(byte pin) {
      this->pin = pin;
    }

    int getValue() {
      update();
      return val;
    }

};

/* A dial is just a slider where angle matters. */
class Dial : public Slider {
  
  public:

    Dial(byte pin) : Slider { pin } {
      this->pin = pin;
    }

    float getAngle() {
      update();
      float rad = (val / 1023.0) * TWO_PI;
      return rad;
    }

};

/* A joystick is really just two perpendicular variable resistors.
  This can be abstracted as two sliders. */
template<byte pinX, byte pinY> class Joystick {

  private:

    Slider axisX;
    Slider axisY;

  public:

    Joystick() : axisX(pinX), axisY(pinY) {}

    Vect getVector() {
      float x = fmap(axisX.getValue(), 0, 1023, -1., 1.);
      float y = fmap(axisY.getValue(), 0, 1023, -1., 1.);
      Serial.print(x);
      Serial.print("  ");
      Serial.println(y);
      Vect vec = Vect(x,y);
      return vec;
    }

    float getMag() {
      Vect pixV = getVector();
      pixV.absolute();
      return min(pixV.mag(), 1.);
    }
};
