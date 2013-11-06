
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
	int m_data[NOROWS][NOCOLUMS];

public:
	LEDDriver(const int rows[NOROWS], const int colums[NOCOLUMS]) : m_row(-1) {
		memcpy(m_colums, colums, sizeof(m_colums));
		memcpy(m_rows, rows, sizeof(m_rows));
		memset(m_data, 0, sizeof(m_data));
	}
	void show(const int* matrix) {
		memcpy(m_data, matrix, sizeof(m_data));
	}
	void display() {
		if(m_row >= 0) {
			digitalWrite(m_rows[m_row], LOW);
		}
		++m_row;
		for(int i = 0 ; i < NOCOLUMS ; ++i) {
			if(m_data[m_row][i]) {
				digitalWrite(m_colums[i], LOW);
			} else {
				digitalWrite(m_colums[i], HIGH);
			}
		}
		digitalWrite(m_rows[m_row], HIGH);
	}
};