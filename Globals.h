#ifndef GLOBALS_H
#define GLOBALS_H

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

float fmap(float x, float a, float b, float c, float d)
{
      float f=x/(b-a)*(d-c)+c;
      return f;
}

#endif /* GLOBALS_H */