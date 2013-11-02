#include "Arduino.h"

class LedDriver {
  public:
    static const int ROW0PIN = 13;
    static const int ROW1PIN = 12;
    static const int ROW2PIN = 8;
    static const int ROW3PIN = 7;
    static const int ROW4PIN = 4;
    static const int COL0PIN = 5;
    static const int COL1PIN = 6;
    static const int COL2PIN = 9;
    static const int COL3PIN = 10;
    static const int COL4PIN = 11;
    void init() {
      pinMode(ROW0PIN, OUTPUT);
      pinMode(ROW1PIN, OUTPUT);
      pinMode(ROW2PIN, OUTPUT);
      pinMode(ROW3PIN, OUTPUT);
      pinMode(ROW4PIN, OUTPUT);
    }
    void display() {
      digitalWrite(ROW0PIN, HIGH);
      digitalWrite(COL0PIN, HIGH);
      digitalWrite(COL1PIN, HIGH);
      digitalWrite(COL2PIN, HIGH);
      digitalWrite(COL3PIN, HIGH);
      digitalWrite(COL4PIN, HIGH);
    }
};

