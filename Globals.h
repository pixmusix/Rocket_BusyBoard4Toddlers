#ifndef GLOBALS_H
#define GLOBALS_H

const int LEDMATRIX_COUNT = 64;
const int LEDMATRIX_XDIM = 16;
const int LEDMATRIX_YDIM = 16;

struct Led64 {
  CRGB matrix[64] = {};
};

float fmap(float x, float a, float b, float c, float d)
{
      float f=x/(b-a)*(d-c)+c;
      return f;
}

#endif /* GLOBALS_H */