#include <FastLED.h>

class Led {

  protected:

    byte pin;
    unsigned int cache;
    
  public:

    Led(byte pin) {
      this->pin = pin;
      pinMode(pin, OUTPUT);
      cache = 0;
      off();
    }

    void on() {
      digitalWrite(pin, HIGH);
    }

    void off() {
      digitalWrite(pin, LOW);
    }

    void blink() {
      cache += 1;
      if (cache%2==0) {on();} else {off();}
    }

};

template<byte pin, int sz> class LedStrip {

  protected:

    CRGB matrix[sz];
    unsigned int cache;
    
    void ledConfig() {
      FastLED.addLeds<WS2812B, pin, GRB>(matrix, sz); 
    }

    CRGB getPix(int i) {
      if (i < sz) {
        return matrix[i];
      } else {
        return matrix[0];
      }
    }

    void setPix(int i, byte r, byte g, byte b) {
      // For a personal project, I'm happy to deal with the silent error.
      if (!(i < 0 || i >= sz)) {
        matrix[i].setRGB(r,g ,b);
      }
    }
    
    void addPix(int i, byte r, byte g, byte b) {
      // For a personal project, I'm happy to deal with the silent error.
      if (!(i < 0 || i >= sz)) {
        CRGB pix;
        pix.setRGB(r,g ,b);
        matrix[i] += pix;
      }
    }

  public:

    LedStrip() {     
      pinMode(pin, OUTPUT);
      cache = 0;
      ledConfig();
    }

    void ledPop() {
      cache += 1;
      FastLED.show();
    }

    void drawTo(CRGB externalMatrix[]) { 
      for (int i = 0; i < sz; i++) {
        matrix[i] += externalMatrix[i];
      }
    }

    void setRandomAll() {
      for (int i = 0; i < sz; i++) {
        byte r = random(1,10);
        byte g = random(1,10);
        byte b = random(1,10);
        matrix[i].setRGB(r,g ,b);
      }
    }

    void meterTo(int k, byte r, byte g, byte b) {
      for (int i = 0; i < k; i++) {
        float m = min(((float)(i + 1) / (float)sz) + 0.01, 1.0);
        setPix(i, r * m, g * m, b * m);
      }
      for (int i = k; i < sz; i++) {
        setPix(i, 0, 0, 0);
      }
    }

    void sweepTo(int k, byte r, byte g, byte b) {
      int upTo = cache % min(sz, k);
      for (int i = 0; i < sz; i++) {
        if (i == upTo) {
          matrix[i].setRGB(r,g,b);
        } else {
          matrix[i].setRGB(0,0,0);
        }
      }
    }

    void multAll(float m) {
      //consider using the native .fadeToBlack() or .setBrightness()
      for (int i = 0; i < sz; i++) {
        CRGB px = getPix(i);
        byte r = (byte)floor(px.r * m);
        byte g = (byte)floor(px.g * m);
        byte b = (byte)floor(px.b * m);
        setPix(i, r, g, b);
      }
    }

    void pulseAll() {
      int k = sin16(cache);
      int n = map(k, -32768, 32767, 0, 255);
      float m = (float)n / 255.0;
      for (int i = 0; i < sz; i++) {
        CRGB px = getPix(i);
        byte r = (byte)floor(px.r * m);
        byte g = (byte)floor(px.g * m);
        byte b = (byte)floor(px.b * m);
        setPix(i, r, g, b);
      }
    }

    void clearAll() {
      for (int i = 0; i < sz; i++) {
        matrix[i].setRGB(0,0,0);
      }
    }
};