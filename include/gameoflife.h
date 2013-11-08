
#include "leddriver.h"

class GameOfLife 
{
private:
	DisplayUpdater* m_driver;
	int m_previus[LEDDriver::NOROWS][LEDDriver::NOCOLUMS];
	int noNeighbours(int x, int y) {
		return m_previus[(x-1) % LEDDriver::NOROWS][(y-1)%LEDDriver::NOCOLUMS] 
		+ m_previus[(x-1) % LEDDriver::NOROWS][y] 
		+ m_previus[(x-1) % LEDDriver::NOROWS][(y+1)%LEDDriver::NOCOLUMS]
		+ m_previus[x][(y-1)%LEDDriver::NOCOLUMS]
		+ m_previus[x][(y+1)%LEDDriver::NOCOLUMS]
		+ m_previus[(x+1) % LEDDriver::NOROWS][(y-1)%LEDDriver::NOCOLUMS]
		+ m_previus[(x+1) % LEDDriver::NOROWS][y]
		+ m_previus[(x+1) % LEDDriver::NOROWS][(y+1)%LEDDriver::NOCOLUMS];
	}
public:
	GameOfLife(DisplayUpdater* driver, int* seed) : m_driver(driver) {
		memcpy(m_previus, seed, sizeof(m_previus));
	}
	void tick() {
		int result[] = { 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0 };
		for(int x = 0 ; x < LEDDriver::NOROWS; ++x) {
			for(int y = 0; y < LEDDriver::NOCOLUMS; ++y) {
				if( noNeighbours(x,y) == 2 || noNeighbours(x,y) == 3) {
					result[x*LEDDriver::NOCOLUMS + y] = 1;
				}
			}
		}
		m_driver->show(result); 
	}
};