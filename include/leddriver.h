
#include "Arduino.h"

class LEDDriver
{
public:
	static const int NOCOLUMS = 5;
private:
	int m_row0pin;
	int m_colums[NOCOLUMS];

public:
	LEDDriver(int row0pin, const int colums[NOCOLUMS]) : m_row0pin(row0pin) {
		memcpy(m_colums, colums, sizeof(m_colums));
	}
	void display() {
		digitalWrite(m_row0pin, HIGH);
		for(int i = 0 ; i < NOCOLUMS ; ++i) {
			digitalWrite(m_colums[i], HIGH);
		}
	}
};