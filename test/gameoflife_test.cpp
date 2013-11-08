

#include "leddriver.h"
#include "gameoflife.h"
#include "LedDriverMock.h"
#include <gmock/gmock.h>
#include "Arduino.h"

MATCHER_P(CenterPixelIs, value, "")
{ 
	return arg[(LEDDriver::NOROWS/2)*LEDDriver::NOCOLUMS
		+ (LEDDriver::NOCOLUMS/2)] == value;
}

class TestGameOfLife : public ::testing::Test {
protected:
	MockDisplayUpdater mockdriver;
	TestGameOfLife() {
	}
};

TEST_F(TestGameOfLife, ALiveCellWithNoNeightBoursDie)
{
	int startseed[] = {0,0,0,0,0, 0,0,0,0,0, 0,0,1,0,0, 0,0,0,0,0, 0,0,0,0,0};
	EXPECT_CALL(mockdriver, show(CenterPixelIs(0))).Times(1);
	GameOfLife gameoflife(&mockdriver, startseed);
	gameoflife.tick();
}

TEST_F(TestGameOfLife, ALifeCellWithTwoNeighboursStaysAlive)
{
	int startseed[] = {0,0,0,0,0, 0,0,0,0,0, 0,1,1,1,0, 0,0,0,0,0, 0,0,0,0,0};
	EXPECT_CALL(mockdriver, show(CenterPixelIs(1))).Times(1);
	GameOfLife gameoflife(&mockdriver, startseed);
	gameoflife.tick();
}

TEST_F(TestGameOfLife, ALifeCellWithTreeNeighboursStaysAlive)
{
	int startseed[] = {0,0,0,0,0, 0,1,1,0,0, 0,0,1,1,0, 0,0,0,0,0, 0,0,0,0,0};
	EXPECT_CALL(mockdriver, show(CenterPixelIs(1))).Times(1);
	GameOfLife gameoflife(&mockdriver, startseed);
	gameoflife.tick();
}
TEST_F(TestGameOfLife, ADeadCellWithTwoNeighboursIsStillDead)
{
	int startseed[] = {0,0,0,0,0, 0,1,0,1,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0};
	EXPECT_CALL(mockdriver, show(CenterPixelIs(0))).Times(1);
	GameOfLife gameoflife(&mockdriver, startseed);
	gameoflife.tick();
}