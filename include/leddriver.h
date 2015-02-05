#ifndef LEDDRIVER_H
#define LEDDRIVER_H
#include "Arduino.h"

class LEDDriver {
    private:
        int m_row1pin;
        int m_col1pin;
    public:
        LEDDriver(const int row1pin, const int col1pin) : m_row1pin(row1pin), m_col1pin(col1pin) {}
        void display() {
            digitalWrite(m_row1pin, HIGH);
            digitalWrite(m_col1pin, HIGH);
        }

};
#endif // LEDDRIVER_H
