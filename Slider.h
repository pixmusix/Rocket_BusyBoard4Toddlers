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