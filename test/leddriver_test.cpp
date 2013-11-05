
#include <gmock/gmock.h>
#include "leddriver.h"
#include "Arduino.h"

static const int ROW0PIN = 13;
static const int COL0PIN = 5;

using ::testing::AnyNumber;
using ::testing::Not;
using ::testing::_;

TEST(TestLedDriver, FirstCallToDisplayCallShouldLightRow0)
{
	ArduinoMock *arduinoMock = arduinoMockInstance();

	EXPECT_CALL(*arduinoMock, digitalWrite(Not(ROW0PIN), _)).Times(AnyNumber());
	EXPECT_CALL(*arduinoMock, digitalWrite(ROW0PIN, HIGH)).Times(1);

	LEDDriver ledDriver(ROW0PIN);
	ledDriver.display();

	releaseArduinoMock();
}

TEST(TestLedDriver, DefaultShouldHaveFirstLedLedInFirstRowOff)
{
	ArduinoMock *arduinoMock = arduinoMockInstance();
	EXPECT_CALL(*arduinoMock, digitalWrite(Not(COL0PIN), _)).Times(AnyNumber());
	EXPECT_CALL(*arduinoMock, digitalWrite(COL0PIN, HIGH));
	LEDDriver ledDriver(ROW0PIN);
	ledDriver.display();
	releaseArduinoMock();
}

