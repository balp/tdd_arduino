#include "gmock/gmock.h"
#include "leddriver.h"
#include "LedDriverMock.h"

#include "gameoflife.h"
#include "Arduino.h"
using ::testing::ElementsAreArray;

MATCHER_P( SameArray, array, "" ) {
  if( memcmp(arg, array, sizeof(int)*25) == 0 ) {
    return true;
  }
  *result_listener << " {" ;
  for(int i = 0 ; i < 25 ; ++i) {
    *result_listener << (i ? "," : "") << arg[i];
  }
  *result_listener << "} != {" ;
  for(int i = 0 ; i < 25 ; ++i) {
    *result_listener << (i ? "," : "") << ((int*)array)[i];
  }
  *result_listener << "}" ;

  return false;
}

class TestGameOfLife : public ::testing::Test {
  protected:
    MockMatrixShower mockmatrixshower;
    void runtest( int seed[5][5], int expected[5][5]) {
      EXPECT_CALL(mockmatrixshower, show( SameArray(expected))).Times(1);
      GameOfLife gameOfLife(seed, &mockmatrixshower);
      gameOfLife.tick();
    }
};
 
TEST_F(TestGameOfLife, ALiveCellDies)
{
  int seed[5][5] = {{0,0,0,0,0}, {0,0,0,0,0}, {0,0,1,0,0}, {0,0,0,0,0}, {0,0,0,0,0}};
  int expected[5][5] = {{0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}};
  runtest(seed, expected);
}

TEST_F(TestGameOfLife, ACellWithTwoNeighboursLive)
{
  int seed[5][5] = {{0,0,0,0,0}, {0,0,0,0,0}, {0,1,1,1,0}, {0,0,0,0,0}, {0,0,0,0,0}};
  int expected[5][5] = {{0,0,0,0,0}, {0,0,1,0,0}, {0,0,1,0,0}, {0,0,1,0,0}, {0,0,0,0,0}};
  runtest(seed, expected);
}

TEST_F(TestGameOfLife, ACellWithThreeNeigboursLive)
{
  int seed[5][5] = {{0,0,0,0,0}, {0,0,1,0,0}, {0,1,1,1,0}, {0,0,0,0,0}, {0,0,0,0,0}};
  int expected[5][5] = {{0,0,0,0,0}, {0,1,1,1,0}, {0,1,1,1,0}, {0,0,1,0,0}, {0,0,0,0,0}};
  runtest(seed, expected);
}

TEST_F(TestGameOfLife, ACellWithThreeNeigboursBorns)
{
  int seed[5][5] = {{0,0,0,0,0}, {0,0,1,0,0}, {0,1,1,1,0}, {0,0,0,0,0}, {0,0,0,0,0}};
  int expected[5][5] = {{0,0,0,0,0}, {0,1,1,1,0}, {0,1,1,1,0}, {0,0,1,0,0}, {0,0,0,0,0}};
  runtest(seed, expected);
}

using ::testing::InSequence;

TEST_F(TestGameOfLife, TheBoardIsSavedForNextGeneration)
{
  int g1[5][5] = {{0,0,0,0,0}, {0,0,0,0,0}, {0,1,1,1,0}, {0,0,0,0,0}, {0,0,0,0,0}};
  int g2[5][5] = {{0,0,0,0,0}, {0,0,1,0,0}, {0,0,1,0,0}, {0,0,1,0,0}, {0,0,0,0,0}};
  InSequence s;
  EXPECT_CALL(mockmatrixshower, show( SameArray(g2))).Times(1);
  EXPECT_CALL(mockmatrixshower, show( SameArray(g1))).Times(1);
  GameOfLife gameOfLife(g1, &mockmatrixshower);
  gameOfLife.tick();
  gameOfLife.tick();
}
