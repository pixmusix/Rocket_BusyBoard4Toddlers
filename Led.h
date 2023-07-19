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

    void update() {
      ledPop();
      delay(100);
    }

    CRGB getPix(int i) {
      if (i < sz) {
        return matrix[i];
      } else {
        return matrix[0];
      }
    }
    
    void setPix(int i, byte r, byte g, byte b) {
      // For a personal project like this, I'm happy to deal with the silent error.
      if (!(i < 0 || i >= sz)) {
        matrix[i].setRGB(r,g ,b);
      }
      ledPop();
    }

    void drawTo(CRGB externalMatrix[]) { 
      for (int i = 0; i < sz; i++) {
        matrix[i] += externalMatrix[i];
      }
      ledPop();
    }

    void setRandomAll() {
      for (int i = 0; i < sz; i++) {
        byte r = random(1,10);
        byte g = random(1,10);
        byte b = random(1,10);
        matrix[i].setRGB(r,g ,b);
      }
      ledPop();
    }

    void clearAll() {
      for (int i = 0; i < sz; i++) {
        matrix[i].setRGB(0,0,0);
      }
      ledPop();
    }
};