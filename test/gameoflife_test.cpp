

#include "leddriver.h"
#include "gameoflife.h"
#include "LedDriverMock.h"
#include <gmock/gmock.h>
#include "Arduino.h"

using ::testing::_;
using ::testing::Mock;

MATCHER_P(CenterPixelIs, value, "")
{ 
	return arg[(LEDDriver::NOROWS/2)*LEDDriver::NOCOLUMS
		+ (LEDDriver::NOCOLUMS/2)] == value;
}
MATCHER_P(GameBoardIs, value, "")
{ 
	if( memcmp(arg, value, sizeof(int) * 25) == 0 ) {
		return true;
	}
	*result_listener << " {" ;
	for(int i = 0 ; i < 25 ; ++i) {
		*result_listener << (i ? "," : "") << arg[i];
	}
	*result_listener << "} != {" ;
	for(int i = 0 ; i < 25 ; ++i) {
		*result_listener << (i ? "," : "") << value[i];
	}
	*result_listener << "}" ;
	
	return false;
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
TEST_F(TestGameOfLife, ADeadCellWithThreeNeighboursIsGetsBorn)
{
	int startseed[] = {0,0,0,0,0, 0,0,1,0,0, 0,1,0,1,0, 0,0,0,0,0, 0,0,0,0,0};
	EXPECT_CALL(mockdriver, show(CenterPixelIs(1))).Times(1);
	GameOfLife gameoflife(&mockdriver, startseed);
	gameoflife.tick();
}

TEST_F(TestGameOfLife, TheGameContinuesOnLastGeneration)
{
	int startseed[] = {0,0,0,0,0, 0,0,0,0,0, 0,1,1,1,0, 0,0,0,0,0, 0,0,0,0,0};
	EXPECT_CALL(mockdriver, show(_)).Times(1);
	GameOfLife gameoflife(&mockdriver, startseed);
	gameoflife.tick();
	Mock::VerifyAndClearExpectations(&mockdriver);
	EXPECT_CALL(mockdriver, show(GameBoardIs(startseed))).Times(1);
	gameoflife.tick();
}