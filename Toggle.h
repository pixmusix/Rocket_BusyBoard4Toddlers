
/* Abstraction of any object with a binary state. */
class Toggle {
  
  protected:
    byte pin;
    byte state;

  private:
    void update() {
      state = digitalRead(pin);
    }
  
  public:

    Toggle(byte pin) {
      this->pin = pin;
      pinMode(pin, INPUT);
      update();
    }

    byte getState() {
      update();
      return state;
    }

};

class Button : public Toggle {
  
  private:

    byte lastReading;
    unsigned long timeDown = 0;
    unsigned long lastDebounceTime = 0;
    unsigned long debounceDelay = 50;

    void update() {
      byte newReading = digitalRead(pin);
      
      if (newReading != lastReading) {
        timeDown = 0;
        lastDebounceTime = millis();
      } else {
        timeDown += 0.01;
      }
      if (millis() - lastDebounceTime > debounceDelay) {
        state = newReading;
      }

      lastReading = newReading;
    }
  
  public:

    Button(byte pin) : Toggle { pin } {
      this->pin = pin;
      pinMode(pin, INPUT);
      lastReading = LOW;
      update();
    }

    bool isPressed() {
      return (getState() == HIGH);
    }

    float getElapsed() {
      float elap = (float)timeDown;
      return abs(elap);
    }

};

class Switch : public Toggle {

  private:

    void update() {
      state = digitalRead(pin);
    }
  
  public:

    Switch(byte pin) : Toggle { pin } {
      this->pin = pin;
      pinMode(pin, INPUT);
      update();
    }

    bool isArmed() {
      return (getState() == HIGH);
    }

};