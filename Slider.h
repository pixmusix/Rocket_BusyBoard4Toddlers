#include "Vect.h"
#include "Globals.h"

/* Abstracts a variable resistor with non-binary state. */
class Slider {
  
  protected:
    byte pin;
    int val;
    int cache;

    void update() {
      val = analogRead(pin);
    }
  
  public:

    Slider() {}

    Slider(byte pin) {
      this->pin = pin;
      cache = 0;
    }

    int getValue() {
      update();
      return val;
    }

    int getChange() {
      int k = cache - getValue();
      if (k != 0) {
        cache = getValue();
        return k;
      }
    }

};

/* A dial is just a slider where angle matters. */
class Dial : public Slider {

  private:
    float toRadians(int i) {
      return (i / 1023.0) * TWO_PI;
    }
  
  public:

    Dial(byte pin) : Slider { pin } {
      this->pin = pin;
    }

    float getAngle() {
      update();
      return toRadians(val);
    }

    float getAngleChange() {
      int k = cache - getValue();
      if (k != 0) {
        cache = getValue();
        return toRadians(k);
      }
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
      Vect vec = Vect(x,y);
      return vec;
    }

    float getMag() {
      Vect pixV = getVector();
      pixV.absolute();
      return min(pixV.mag(), 1.);
    }
};
