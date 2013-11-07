
#include "leddriver.h"

class GameOfLife 
{
private:
	DisplayUpdater* m_driver;
public:
	GameOfLife(DisplayUpdater* driver, int* seed) : m_driver(driver) {}
	void tick() {
		int result[] = { 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0 };
		m_driver->show(result); 
	}
};