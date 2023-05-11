class Led {

  protected:

    byte pin;
    int numLed;

    void init() {
      pinMode(pin, OUTPUT);
      off();
    }

  public:

    Led(byte pin) {
      this->pin = pin;
      numLed = 1;
      init();
    }

    void on() {
      digitalWrite(pin, HIGH);
    }

    void off() {
      digitalWrite(pin, LOW);
    }

};

// class LedMatrix : public Led {

//   private:
//     void ledPop() {
//       FastLED.show();
//       delay(20);
//     }

//     init() {

//     }

//   public:

//     LedStrip(byte pin, int count) : Led { pin, count } {
//       CGRB leds[NUM_LEDS];
//       this->pin = pin;
//       numLed = count;
//       FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, numLed); 
//       matrix = 
//       init();
//     }

// }