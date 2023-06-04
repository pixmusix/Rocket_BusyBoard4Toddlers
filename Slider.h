#include "PixVector.h"

/* Abstracts a variable resistor with non-binary state. */
class Slider {
  
  protected:
    byte pin;
    byte val;

    void update() {
      val = analogRead(pin);
    }
  
  public:

    Slider(byte pin) {
      this->pin = pin;
      pinMode(pin, INPUT);
      update();
    }

    byte getValue() {
      update();
      return val;
    }

};

/* A dial is just a slider where angle matters. */
class Dial : public Slider {
  
  public:

    Dial(byte pin) : Slider { pin } {
      this->pin = pin;
      pinMode(pin, INPUT);
      update();
    }

    float getAngle() {
      update();
      float rad = map(val, 0, 255, 0, TWO_PI);
      return rad;
    }

};

/* A joystick is really just two perpendicular variable resistors.
  This can be abstracted as two sliders. */
template<byte pinX, byte pinY> class Joystick {

  private:

    Slider axisX = Slider(pinX);
    Slider axisY = Slider(pinY);

  public:

    Joystick() {}

    PixVector getVector() {
      float x = map(axisX.getValue(), 0, 1023, 0., 1.);
      float y = map(axisY.getValue(), 0, 1023, 0., 1.);
      PixVector vec = PixVector(x,y);
      return vec;
    }
};
