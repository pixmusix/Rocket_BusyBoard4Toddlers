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

    int cache;

    CRGB matrix[sz];
    
    void ledConfig() {
      cache = 0;
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

    void meterTo(int k, byte r, byte g, byte b) {
      for (int i = 0; i < k; i++) {
        float m = min(((float)(i + 1) / (float)sz) + 0.01, 1.0);
        setPix(i, r * m, g * m, b * m);
      }
      for (int i = k; i < sz; i++) {
        matrix[i].setRGB(0,0,0);
      }
      ledPop();
    }

    void sweepTo(int k, byte r, byte g, byte b) {
      for (int i = 0; i < sz; i++) {
        if (i == cache) {
          matrix[i].setRGB(r,g,b);
        } else {
          matrix[i].setRGB(0,0,0);
        }
      }
      ledPop();
      cache = (cache + 1) % min(k, sz);
    }

    void decayAll(float m) {
      for (int i = 0; i < sz; i++) {
        CRGB px = getPix(i);
        byte r = (byte)floor(px.r * m);
        byte g = (byte)floor(px.g * m);
        byte b = (byte)floor(px.b * m);
        setPix(i, r, g, b);
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