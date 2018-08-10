// Copyright 2018 Hanpil Kang

#ifndef _GETCH_WINDOWS_H_
#define _GETCH_WINDOWS_H_

#include <conio.h>

const int KEY_UP    = 257;
const int KEY_DOWN  = 258;
const int KEY_LEFT  = 259;
const int KEY_RIGHT = 260;
const int KEY_HOME  = 261;
const int KEY_END   = 262;
const int KEY_DEL   = 8;

int GetKeyInput() {
  int v = _getch();
  if (v == 27) {
    v = _getch();
    if (v != 91) return v;
    v = _getch();
    switch (v) {
      case 65: return KEY_UP;
      case 66: return KEY_DOWN;
      case 67: return KEY_RIGHT;
      case 68: return KEY_LEFT;
      case 72: return KEY_HOME;
      case 70: return KEY_END;
      default: return v;
    }
  }
  return v;
}

#endif  // _GETCH_WINDOWS_H_
