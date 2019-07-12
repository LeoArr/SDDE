#ifndef TICKER
#define TICKER

#include <SDL2/SDL.h>

class Ticker {
 public:
  static Ticker* instance() {
    if (_instance == NULL) {
      _instance = new Ticker();
    }
    return _instance;
  }
  Uint32 ticks() {
    return _ticks;
  }
  void increment() {
    _ticks++;
  }
 private:
 Ticker() : _ticks(0) {};
  static Ticker* _instance;
  Uint32 _ticks;
};

#endif
