
#include "Arduino.h"

class LEDDriver
{
	int m_row0pin;
public:
	LEDDriver(int row0pin) : m_row0pin(row0pin) {}
	void display() {
		digitalWrite(m_row0pin, HIGH);
	}
};