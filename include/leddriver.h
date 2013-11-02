#include "Arduino.h"

class LedDriver {
  public:
    static const int ROW0PIN = 13;
    static const int ROW1PIN = 12;
    static const int ROW2PIN = 8;
    static const int ROW3PIN = 7;
    static const int ROW4PIN = 4;
    void init() {
      pinMode(ROW0PIN, OUTPUT);
      pinMode(ROW1PIN, OUTPUT);
      pinMode(ROW2PIN, OUTPUT);
      pinMode(ROW3PIN, OUTPUT);
      pinMode(ROW4PIN, OUTPUT);
    }
    void display() {
      digitalWrite(ROW0PIN, HIGH);
    }
};

