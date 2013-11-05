
#include "Arduino.h"

class LEDDriver
{
	int m_row0pin;
	int m_colums[5];

public:
	LEDDriver(int row0pin, const int colums[5]) : m_row0pin(row0pin) {
		memcpy(m_colums, colums, sizeof(m_colums));
	}
	void display() {
		digitalWrite(m_row0pin, HIGH);
		digitalWrite(m_colums[0], HIGH);
		digitalWrite(m_colums[1], HIGH);
		digitalWrite(m_colums[2], HIGH);
	}
};