#include <FastLED.h>

class Led {

  private:

    void init() {
      pinMode(pin, OUTPUT);
      off();
    }

  protected:

    byte pin;
    int size;

  public:

    Led(byte pin) {
      this->pin = pin;
      size = 1;
      init();
    }

    void on() {
      digitalWrite(pin, HIGH);
    }

    void off() {
      digitalWrite(pin, LOW);
    }

};

class LedStrip : public Led {

  private:

    CRGB matrix[8];

  protected:
    void init() {
      pinMode(pin, OUTPUT);
      FastLED.addLeds<WS2812B, pin, GRB>(matrix, size); 
    }

    void ledPop() {
      FastLED.show();
    }

  public:

    LedStrip(byte pin) : Led { pin } {     
      this->pin = pin;
      size = 8;
      init();
    }

    CRGB get(int i) {
      if (i < size) {
        return matrix[i];
      } else {
        return matrix[0];
      }
    }

};

class LedRainbow : public LedStrip {

  private:

    CRGB matrix[13];

  public:

    LedRainbow(byte pin) : LedStrip { pin } {
      size = 13;
      this->pin = pin;
      init();
    }

};

class LedMatrix : public LedStrip {

  private:

    CRGB matrix[64];

  public:

    LedMatrix(byte pin) : LedStrip { pin } {     
      this->pin = pin;
      size = 64;
      init());
    }

    CRGB get(int x, int y) {
      int i = x + y * 8;
      if (i < size) {
        return matrix[i];
      } else {
        return matrix[0];
      }
    }
};