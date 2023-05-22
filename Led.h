#include <FastLED.h>

class Led {

  private:

    void init() {
      pinMode(pin, OUTPUT);
      off();
    }

  protected:

    byte pin;

  public:

    Led(byte pin) {
      this->pin = pin;
      init();
    }

    void on() {
      digitalWrite(pin, HIGH);
    }

    void off() {
      digitalWrite(pin, LOW);
    }

};

template<byte pin, int sz> class LedStrip {

  protected:

    CRGB matrix[sz];
    
    void ledConfig() {
      FastLED.addLeds<WS2812B, pin, GRB>(matrix, sz); 
    }

    void ledPop() {
      FastLED.show();
    }

  public:

    LedStrip() {     
      pinMode(pin, OUTPUT);
      ledConfig();
    }

    CRGB getPix(int i) {
      if (i < sz) {
        return matrix[i];
      } else {
        return matrix[0];
      }
    }

};