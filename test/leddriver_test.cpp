
#include <gmock/gmock.h>
#include "leddriver.h"
#include "Arduino.h"

static const int ROW0PIN = 13;
static const int COL0PIN = 5;
static const int COL1PIN = 6;

using ::testing::AnyNumber;
using ::testing::Not;
using ::testing::_;

class TestLedDriver : public ::testing::Test {
protected:
	ArduinoMock *arduinoMock;
	LEDDriver ledDriver;
	TestLedDriver() : ledDriver(ROW0PIN, COL0PIN) {}
	void SetUp() {
		arduinoMock = arduinoMockInstance();
	}
	void TearDown() {
		releaseArduinoMock();
	}
};

TEST_F(TestLedDriver, FirstCallToDisplayCallShouldLightRow0)
{
	EXPECT_CALL(*arduinoMock, digitalWrite(Not(ROW0PIN), _)).Times(AnyNumber());
	EXPECT_CALL(*arduinoMock, digitalWrite(ROW0PIN, HIGH)).Times(1);
	ledDriver.display();
}

TEST_F(TestLedDriver, DefaultShouldHaveFirstLedLedInFirstRowOff)
{
	EXPECT_CALL(*arduinoMock, digitalWrite(Not(COL0PIN), _)).Times(AnyNumber());
	EXPECT_CALL(*arduinoMock, digitalWrite(COL0PIN, HIGH));
	ledDriver.display();
}

TEST_F(TestLedDriver, DefaultShouldHaveSecondLedLedInFirstRowOff)
{
	EXPECT_CALL(*arduinoMock, digitalWrite(Not(COL1PIN), _)).Times(AnyNumber());
	EXPECT_CALL(*arduinoMock, digitalWrite(COL1PIN, HIGH));
	ledDriver.display();
}