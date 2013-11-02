#include "leddriver.h"
#include "gmock/gmock.h"
#include "Arduino.h"

class leddriver : public ::testing::Test {
  public:
  ArduinoMock* arduinoMock;
  LedDriver ledDriver;
  leddriver() : arduinoMock(arduinoMockInstance()) {
  }
  virtual ~leddriver() {
    releaseArduinoMock();
  }
};

TEST_F(leddriver, FirstCallToDisplayShouldTurnOnRow0)
{
  EXPECT_CALL(*arduinoMock, digitalWrite(LedDriver::ROW0PIN, HIGH)).Times(1);
  ledDriver.display();
}

TEST_F(leddriver, CallInitShouldSetRow0PinToOutput)
{
  EXPECT_CALL(*arduinoMock, pinMode(LedDriver::ROW0PIN, OUTPUT)).Times(1);
  EXPECT_CALL(*arduinoMock, pinMode(LedDriver::ROW1PIN, OUTPUT)).Times(1);
  EXPECT_CALL(*arduinoMock, pinMode(LedDriver::ROW2PIN, OUTPUT)).Times(1);
  EXPECT_CALL(*arduinoMock, pinMode(LedDriver::ROW3PIN, OUTPUT)).Times(1);
  EXPECT_CALL(*arduinoMock, pinMode(LedDriver::ROW4PIN, OUTPUT)).Times(1);
  ledDriver.init();
}

