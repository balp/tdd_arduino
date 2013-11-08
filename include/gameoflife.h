
#include "leddriver.h"

class GameOfLife 
{
private:
	DisplayUpdater* m_driver;
	int m_previus[LEDDriver::NOROWS][LEDDriver::NOCOLUMS];
public:
	GameOfLife(DisplayUpdater* driver, int* seed) : m_driver(driver) {
		memcpy(m_previus, seed, sizeof(m_previus));
	}
	void tick() {
		int result[] = { 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0 };
		if( m_previus[2][1] == 1 && 
			m_previus[2][3] == 1) {
				result[2*LEDDriver::NOCOLUMS + 2] = 1;
		}
		m_driver->show(result); 
	}
};