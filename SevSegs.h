#include "Globals.h"
#include <TM1637Display.h>
#include <Keypad.h>

template<byte pin, byte clk> class SevenSegment {

  protected:

    TM1637Display display = TM1637Display(clk, pin);

    void sevsegConfig() {
      display.setBrightness(0x0f);
    }

  public:

    SevenSegment() {     
      pinMode(pin, OUTPUT);
      sevsegConfig();
    }

    void update(byte data[]) {
      display.setSegments(data);
    }

    void displayInt(int i) {
      display.showNumberDec(i, true);
    }

    void on() {
      byte full[] = { 0xff, 0xff, 0xff, 0xff };
      update(full);
    }

    void off() {
      byte blank[] = { 0x00, 0x00, 0x00, 0x00 };
      update(blank);
    }

    void clear() {
      display.clear();
    }

};

// This wrapper for keypad.h simply abstracts the setup for us <3
template<byte startingPin> class NumPad {

  protected:
    char pad[4][3] = {
      {'1','2','3'},
      {'4','5','6'},
      {'7','8','9'},
      {'*','0','#'}
    };

    char cache[4] = {'0', '0', '0', '0'};

    byte pin_rows[4] = {startingPin + 6, startingPin + 5, startingPin + 3, startingPin + 1}; //connect to the row pinouts of the keypad
    byte pin_column[3] = {startingPin + 4, startingPin + 2, startingPin}; //connect to the column pinouts of the keypad

    Keypad keys = Keypad( makeKeymap(pad), pin_rows, pin_column, 4, 3 );

    int toNumeral(char k) {
      switch (k) {
        case '*' :
          return random(10);
        case '#' :
          return random(10);
        default :
          return k - '0';
      }
    }

    void rotateLeft() {
      char first = cache[0];
      for (int i = 0; i < 4; i++) {
        int j = (i + 1) % 4;
        cache[i] = cache[j];
      }
      cache[3] = first;
    }

    void update() {
      char key = keys.getKey();
      rotateLeft();
      cache[3] = key;
    }

  public:

    NumPad() {     
      for (int pin = startingPin; pin < startingPin + 8; pin++) {
        pinMode(pin, OUTPUT);
      }
    }

    int getNum() {
      int number = 0;
      update();
      for (int i = 0; i < 4; i++) {
        number *= 10;
        number += toNumeral(cache[i]);
      }
      return number;
    }

};