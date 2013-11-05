
#include "Arduino.h"

class LEDDriver
{
	int m_row0pin;
	int m_col0pin;
	int m_col1pin;
	int m_col2pin;

public:
	LEDDriver(int row0pin, int col0pin, int col1pin, int col2pin) : m_row0pin(row0pin), m_col0pin(col0pin), m_col1pin(col1pin), m_col2pin(col2pin) {}
	void display() {
		digitalWrite(m_row0pin, HIGH);
		digitalWrite(m_col0pin, HIGH);
		digitalWrite(m_col1pin, HIGH);
		digitalWrite(m_col2pin, HIGH);
	}
};