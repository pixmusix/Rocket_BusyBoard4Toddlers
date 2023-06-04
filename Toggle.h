
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
    unsigned long lastDebounceTime = 0;
    unsigned long debounceDelay = 50;

    void update() {
      byte newReading = digitalRead(pin);
      
      if (newReading != lastReading) {
        lastDebounceTime = millis();
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