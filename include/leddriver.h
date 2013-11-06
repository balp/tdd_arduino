
#include "Arduino.h"

class LEDDriver
{
public:
	static const int NOCOLUMS = 5;
	static const int NOROWS = 5;
private:
	int m_rows[NOROWS];
	int m_colums[NOCOLUMS];
	int m_row;

public:
	LEDDriver(const int rows[NOROWS], const int colums[NOCOLUMS]) : m_row(-1) {
		memcpy(m_colums, colums, sizeof(m_colums));
		memcpy(m_rows, rows, sizeof(m_rows));
	}
	void display() {
		if(m_row >= 0) {
			digitalWrite(m_rows[m_row], LOW);
		}
		++m_row;
		for(int i = 0 ; i < NOCOLUMS ; ++i) {
			digitalWrite(m_colums[i], HIGH);
		}
		digitalWrite(m_rows[m_row], HIGH);
	}
};