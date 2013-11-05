
#include <gmock/gmock.h>
#include "leddriver.h"
#include "Arduino.h"

static const int ROW0PIN = 13;

TEST(TestLedDriver, FirstCallToDisplayCallShouldLightRow0)
{
	ArduinoMock *arduinoMock = arduinoMockInstance();

	EXPECT_CALL(*arduinoMock, digitalWrite(ROW0PIN, HIGH));

	LEDDriver ledDriver(ROW0PIN);
	ledDriver.display();

	releaseArduinoMock();
}