#ifndef GLOBALS_H
#define GLOBALS_H

#define LEDMATRIX_COUNT 64;
#define LEDMATRIX_XDIM 16;
#define LEDMATRIX_YDIM 16;

struct Led64 {
  CRGB matrix[64] = {};
};

#endif /* GLOBALS_H */