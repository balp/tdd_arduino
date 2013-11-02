#include "leddriver.h"
#include "gmock/gmock.h"
#include "Arduino.h"

using ::testing::AnyNumber;
using ::testing::AnyOf;
using ::testing::_;

class TestLedDriver : public ::testing::Test {
  public:
  ArduinoMock* arduinoMock;
  LedDriver ledDriver;
  TestLedDriver() : arduinoMock(arduinoMockInstance()) {
  }
  virtual ~TestLedDriver() {
    releaseArduinoMock();
  }
};

TEST_F(TestLedDriver, FirstCallToDisplayShouldTurnOnRow0)
{
  EXPECT_CALL(*arduinoMock, digitalWrite(LedDriver::ROW0PIN, HIGH)).Times(1);
  EXPECT_CALL(*arduinoMock, digitalWrite(AnyOf(LedDriver::COL0PIN,
          LedDriver::COL1PIN, LedDriver::COL2PIN, LedDriver::COL3PIN,
          LedDriver::COL4PIN), _)).Times(AnyNumber());
  ledDriver.display();
}

TEST_F(TestLedDriver, CallInitShouldSetRow0PinToOutput)
{
  EXPECT_CALL(*arduinoMock, pinMode(LedDriver::ROW0PIN, OUTPUT)).Times(1);
  EXPECT_CALL(*arduinoMock, pinMode(LedDriver::ROW1PIN, OUTPUT)).Times(1);
  EXPECT_CALL(*arduinoMock, pinMode(LedDriver::ROW2PIN, OUTPUT)).Times(1);
  EXPECT_CALL(*arduinoMock, pinMode(LedDriver::ROW3PIN, OUTPUT)).Times(1);
  EXPECT_CALL(*arduinoMock, pinMode(LedDriver::ROW4PIN, OUTPUT)).Times(1);
  ledDriver.init();
}

TEST_F(TestLedDriver, DefaultShouldFirstColumBeOff)
{
  EXPECT_CALL(*arduinoMock, digitalWrite(AnyOf(LedDriver::ROW0PIN, LedDriver::ROW1PIN, LedDriver::ROW2PIN,
          LedDriver::ROW3PIN, LedDriver::ROW4PIN), _)).Times(AnyNumber());
  EXPECT_CALL(*arduinoMock, digitalWrite(LedDriver::COL0PIN, HIGH)).Times(1);
  EXPECT_CALL(*arduinoMock, digitalWrite(AnyOf(LedDriver::COL1PIN, LedDriver::COL2PIN, LedDriver::COL3PIN,
          LedDriver::COL4PIN), _)).Times(AnyNumber());
  ledDriver.display();
}

TEST_F(TestLedDriver, DefaultShouldColumsBeOff)
{
  EXPECT_CALL(*arduinoMock, digitalWrite(AnyOf(LedDriver::ROW0PIN, LedDriver::ROW1PIN, LedDriver::ROW2PIN,
          LedDriver::ROW3PIN, LedDriver::ROW4PIN), _)).Times(AnyNumber());
  EXPECT_CALL(*arduinoMock, digitalWrite(LedDriver::COL0PIN, HIGH)).Times(1);
  EXPECT_CALL(*arduinoMock, digitalWrite(LedDriver::COL1PIN, HIGH)).Times(1);
  EXPECT_CALL(*arduinoMock, digitalWrite(LedDriver::COL2PIN, HIGH)).Times(1);
  EXPECT_CALL(*arduinoMock, digitalWrite(LedDriver::COL3PIN, HIGH)).Times(1);
  EXPECT_CALL(*arduinoMock, digitalWrite(LedDriver::COL4PIN, HIGH)).Times(1);
  ledDriver.display();
}
