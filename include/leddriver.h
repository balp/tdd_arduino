#include "Arduino.h"

class LedDriver {
  private:
    int activeRow;
    int m_matrix[5][5];
    int m_rows[5];
    int m_cols[5];
  public:
    LedDriver( int row0pin, int row1pin, int row2pin, int row3pin, int row4pin, int col0pin,
        int col1pin, int col2pin, int col3pin, int col4pin) : activeRow(-1) {
      memset(m_matrix, 0, sizeof(m_matrix));
      m_rows[0] = row0pin;
      m_rows[1] = row1pin;
      m_rows[2] = row2pin;
      m_rows[3] = row3pin;
      m_rows[4] = row4pin;
      m_cols[0] = col0pin;
      m_cols[1] = col1pin;
      m_cols[2] = col2pin;
      m_cols[3] = col3pin;
      m_cols[4] = col4pin;

    }
    void init() {
      for(int i = 0 ; i < 5 ; ++i) {
        pinMode(m_rows[i], OUTPUT);
        pinMode(m_cols[i], OUTPUT);
      }
    }
    void display() {
      if(activeRow >= 0) {
        digitalWrite(m_rows[activeRow], LOW);
      }
      activeRow = activeRow + 1 % 5;
      for(int i = 0 ; i < 5 ; ++i) {
        digitalWrite(m_cols[i], m_matrix[activeRow][i] ? LOW : HIGH);
      }
      digitalWrite(m_rows[activeRow], HIGH);
    }
    void show(int matrix[5][5]) {
      memcpy(m_matrix, matrix, sizeof(m_matrix));
    }
};

