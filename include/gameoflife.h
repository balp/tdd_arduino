
#include "leddriver.h"
#include "Arduino.h"


class GameOfLife
{
  private:
    MatrixShower* m_shower;
    int m_result[5][5];
    int neibours(int x,int y) {
      return m_result[(x-1) % 5][(y-1) % 5] +
        m_result[(x-1) % 5][(y+0) % 5] +
        m_result[(x-1) % 5][(y+1) % 5] +
        m_result[(x+1) % 5][(y-1) % 5] +
        m_result[(x+1) % 5][(y+0) % 5] +
        m_result[(x+1) % 5][(y+1) % 5] +
        m_result[(x) % 5][(y-1) % 5] +
        m_result[(x) % 5][(y+1) % 5];
    }
  public:
    class board {
      public:
        int board[5][5];
    };
    GameOfLife( int seed[5][5], MatrixShower* shower ) : m_shower(shower) {
      memcpy(m_result, seed, sizeof(m_result));
    }
    void tick() {
      int result[5][5] = {{0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}};
      for(int x = 0 ; x < 5 ; ++x) {
        for(int y = 0; y < 5 ; ++y) {
          if(m_result[x][y] && (neibours(x,y) == 2 || neibours(x,y) == 3)) {
            result[x][y] = 1;
          } else if((!m_result[x][y]) && neibours(x,y) == 3) {
            result[x][y] = 1;
          } else {
            result[x][y] = 0;
          }
        }
      }
      memcpy(m_result, result, sizeof(m_result));
      m_shower->show( (int*)m_result );
    }
};
