
#include <gmock/gmock.h>
#include "leddriver.h"
#include "Arduino.h"

TEST(TestLedDriver, FirstCallToDisplayCallShouldLightRow0)
{
	ArduinoMock *arduinoMock = arduinoMockInstance();

	EXPECT_CALL(*arduinoMock, digitalWrite(13, HIGH));

	LEDDriver ledDriver;
	ledDriver.display();

	releaseArduinoMock();
}