
#include "Arduino.h"

class LEDDriver
{
	int m_row0pin;
	int m_col0pin;
public:
	LEDDriver(int row0pin, int col0pin) : m_row0pin(row0pin), m_col0pin(col0pin) {}
	void display() {
		digitalWrite(m_row0pin, HIGH);
		digitalWrite(m_col0pin, HIGH);
	}
};