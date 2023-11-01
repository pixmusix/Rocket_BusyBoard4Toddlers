#ifndef GLOBALS_H
#define GLOBALS_H

//Pin Definitions
const byte DISPLAYPIN_NW = 40;
const byte DISPLAYPIN_NE = 42;
const byte DISPLAYPIN_SW = 44;
const byte DISPLAYPIN_SE = 46;

const byte INTERRUPT = 2;
const byte LATCH = 3;

const byte ARMINGSWITCH_PIN = 22;
const byte YAWDIAL_PIN = 23; 
const byte LAUNCHBUTTON_PIN = 24;
const byte RAINBOW_PIN = 25;
const byte LAUNCHLED_PIN = 26;
const byte STRIPLED_PIN = 27;
const byte CTRLBUTTON_PIN = 28;
const byte ALTBUTTON_PIN = 29;
const byte JOYX_PIN = 30;
const byte JOYY_PIN = 31;
const byte SEVSEG_PIN = 32;
const byte SEVSEG_CLK = 33;

//vars for an LED STRIP;
const int LEDSTRIP_COUNT = 8;

// vars for an LED RAINBOW
const int LEDRAINBOW_COUNT = 13;

// vars for an LED MATRIX
const int LEDMATRIX_COUNT = 64;
const int LEDMATRIX_XDIM = 8;
const int LEDMATRIX_YDIM = 8;

// The size of the busy board central display
const int LEDDISPLAY_SIZE = 256;
const int LEDDISPLAY_XDIM = 16;
const int LEDDISPLAY_YDIM = 16;

const int MAP_SIZE = 4096;
const int MAP_XDIM = 64;
const int MAP_YDIM = 64;

struct Led8 {
  CRGB matrix[8] = {};
};

struct Led13 {
  CRGB matrix[13] = {};
};

struct Led64 {
  CRGB matrix[64] = {};
};

struct Led256 {
  CRGB matrix[256] = {};
};

struct Led4096 {
  CRGB matrix[4096] = {};
};

float fmap(float x, float a, float b, float c, float d)
{
      float f=x/(b-a)*(d-c)+c;
      return f;
}

#endif /* GLOBALS_H */