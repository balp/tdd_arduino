#include "leddriver.h"
#include "gmock/gmock.h"
#include "Arduino.h"

using ::testing::AnyNumber;
using ::testing::AnyOf;
using ::testing::Mock;
using ::testing::_;

static const int ROW0PIN = 13;
static const int ROW1PIN = 12;
static const int ROW2PIN = 8;
static const int ROW3PIN = 7;
static const int ROW4PIN = 4;
static const int COL0PIN = 5;
static const int COL1PIN = 6;
static const int COL2PIN = 9;
static const int COL3PIN = 10;
static const int COL4PIN = 11;

class TestLedDriver : public ::testing::Test {
  public:
  ArduinoMock* arduinoMock;
  LedDriver ledDriver;
  TestLedDriver() : arduinoMock(arduinoMockInstance()), ledDriver(ROW0PIN,
      ROW1PIN, ROW2PIN, ROW3PIN, ROW4PIN,
      COL0PIN, COL1PIN, COL2PIN, COL3PIN,
      COL4PIN) {
  }
  virtual ~TestLedDriver() {
    releaseArduinoMock();
  }
  void ignoreCols() {
    EXPECT_CALL(*arduinoMock, digitalWrite(AnyOf(COL0PIN,
            COL1PIN, COL2PIN, COL3PIN,
            COL4PIN), _)).Times(AnyNumber());
  }
  void ignoreRows() {
    EXPECT_CALL(*arduinoMock, digitalWrite(AnyOf(ROW0PIN, ROW1PIN, ROW2PIN,
            ROW3PIN, ROW4PIN), _)).Times(AnyNumber());
  }
  void expectCols(int col0, int col1, int col2, int col3, int col4) {
    EXPECT_CALL(*arduinoMock, digitalWrite(COL0PIN, col0)).Times(1);
    EXPECT_CALL(*arduinoMock, digitalWrite(COL1PIN, col1)).Times(1);
    EXPECT_CALL(*arduinoMock, digitalWrite(COL2PIN, col2)).Times(1);
    EXPECT_CALL(*arduinoMock, digitalWrite(COL3PIN, col3)).Times(1);
    EXPECT_CALL(*arduinoMock, digitalWrite(COL4PIN, col4)).Times(1);
  }
};

TEST_F(TestLedDriver, FirstCallToDisplayShouldTurnOnRow0)
{
  EXPECT_CALL(*arduinoMock, digitalWrite(ROW0PIN, HIGH)).Times(1);
  ignoreCols();
  ledDriver.display();
}

TEST_F(TestLedDriver, SecondCallShouldTurnOffRow0AndOnRow1)
{
  EXPECT_CALL(*arduinoMock, digitalWrite(_, _)).Times(AnyNumber());
  ledDriver.display();
  Mock::VerifyAndClearExpectations(arduinoMock);
  EXPECT_CALL(*arduinoMock, digitalWrite(ROW0PIN, LOW)).Times(1);
  EXPECT_CALL(*arduinoMock, digitalWrite(ROW1PIN, HIGH)).Times(1);
  ignoreCols();
  ledDriver.display();
}
TEST_F(TestLedDriver, ThirdCallShoulsTurnOffRow1AndOnRow2)
{
  EXPECT_CALL(*arduinoMock, digitalWrite(_, _)).Times(AnyNumber());
  ledDriver.display();
  ledDriver.display();
  Mock::VerifyAndClearExpectations(arduinoMock);
  EXPECT_CALL(*arduinoMock, digitalWrite(ROW1PIN, LOW)).Times(1);
  EXPECT_CALL(*arduinoMock, digitalWrite(ROW2PIN, HIGH)).Times(1);
  ignoreCols();
  ledDriver.display();
}

TEST_F(TestLedDriver, CallInitShouldSetPinsToOutput)
{
  EXPECT_CALL(*arduinoMock, pinMode(ROW0PIN, OUTPUT)).Times(1);
  EXPECT_CALL(*arduinoMock, pinMode(ROW1PIN, OUTPUT)).Times(1);
  EXPECT_CALL(*arduinoMock, pinMode(ROW2PIN, OUTPUT)).Times(1);
  EXPECT_CALL(*arduinoMock, pinMode(ROW3PIN, OUTPUT)).Times(1);
  EXPECT_CALL(*arduinoMock, pinMode(ROW4PIN, OUTPUT)).Times(1);
  EXPECT_CALL(*arduinoMock, pinMode(COL0PIN, OUTPUT)).Times(1);
  EXPECT_CALL(*arduinoMock, pinMode(COL1PIN, OUTPUT)).Times(1);
  EXPECT_CALL(*arduinoMock, pinMode(COL2PIN, OUTPUT)).Times(1);
  EXPECT_CALL(*arduinoMock, pinMode(COL3PIN, OUTPUT)).Times(1);
  EXPECT_CALL(*arduinoMock, pinMode(COL4PIN, OUTPUT)).Times(1);
  ledDriver.init();
}

TEST_F(TestLedDriver, DefaultShouldFirstColumBeOff)
{
  ignoreRows();
  EXPECT_CALL(*arduinoMock, digitalWrite(COL0PIN, HIGH)).Times(1);
  EXPECT_CALL(*arduinoMock, digitalWrite(AnyOf(COL1PIN, COL2PIN, COL3PIN,
          COL4PIN), _)).Times(AnyNumber());
  ledDriver.display();
}

TEST_F(TestLedDriver, DefaultShouldColumsBeOff)
{
  ignoreRows();
  expectCols(HIGH, HIGH, HIGH, HIGH, HIGH);
  ledDriver.display();
}

TEST_F(TestLedDriver, FirstColumWithOneLit)
{
  int matrix[5][5] = {{0,0,0,0,1}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}};
  ledDriver.show((int*)matrix);
  ignoreRows();
  expectCols(HIGH, HIGH, HIGH, HIGH, LOW);
  ledDriver.display();
}

TEST_F(TestLedDriver, SecondColumnWithOneLit)
{
  int matrix[5][5] = {{0,0,0,0,0}, {0,0,0,1,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}};
  ledDriver.show((int*)matrix);
  EXPECT_CALL(*arduinoMock, digitalWrite(_, _)).Times(AnyNumber());
  ledDriver.display();
  Mock::VerifyAndClearExpectations(arduinoMock);
  ignoreRows();
  expectCols(HIGH, HIGH, HIGH, LOW, HIGH);
  ledDriver.display();
}

TEST_F(TestLedDriver, ThirdRowWithOneLit)
{
  int matrix[5][5] = {{0,0,0,0,0}, {0,0,0,0,0}, {0,0,1,0,0}, {0,0,0,0,0}, {0,0,0,0,0}};
  ledDriver.show((int*)matrix);
  EXPECT_CALL(*arduinoMock, digitalWrite(_, _)).Times(AnyNumber());
  ledDriver.display();
  ledDriver.display();
  Mock::VerifyAndClearExpectations(arduinoMock);
  ignoreRows();
  expectCols(HIGH, HIGH, LOW, HIGH, HIGH);
  ledDriver.display();
}

