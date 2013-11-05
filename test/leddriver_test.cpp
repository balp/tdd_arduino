
#include <gmock/gmock.h>
#include "leddriver.h"
#include "Arduino.h"

static const int ROW0PIN = 13;
static const int COL0PIN = 5;

TEST(TestLedDriver, FirstCallToDisplayCallShouldLightRow0)
{
	ArduinoMock *arduinoMock = arduinoMockInstance();

	EXPECT_CALL(*arduinoMock, digitalWrite(ROW0PIN, HIGH));

	LEDDriver ledDriver(ROW0PIN);
	ledDriver.display();

	releaseArduinoMock();
}

TEST(TestLedDriver, DefaultShouldHaveFirstLedLedInFirstRowOff)
{
	ArduinoMock *arduinoMock = arduinoMockInstance();
	EXPECT_CALL(*arduinoMock, digitalWrite(COL0PIN, HIGH));
	LEDDriver ledDriver(ROW0PIN);
	ledDriver.display();
	releaseArduinoMock();
}

