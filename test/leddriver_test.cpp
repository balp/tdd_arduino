#include <gtest/gtest.h>
#include "leddriver.h"
#include "Arduino.h"
using ::testing::AnyNumber;
using ::testing::Not;
using ::testing::_;


static const int ROW1PIN = 13;
static const int COL1PIN = 4;

class TestLedDriver : public ::testing::Test
{
    protected:
        ArduinoMock *arduinoMock;

        LEDDriver ledDriver;
        TestLedDriver() : arduinoMock(arduinoMockInstance()), ledDriver(ROW1PIN, COL1PIN) {
        }
};



TEST_F(TestLedDriver, DisplayFunctionsShouldAtFirstCalTurnOnRowOne)
{
    EXPECT_CALL(*arduinoMock, digitalWrite(Not(ROW1PIN), _)).Times(AnyNumber());
    EXPECT_CALL(*arduinoMock, digitalWrite(ROW1PIN, HIGH)).Times(1);

    ledDriver.display();
    releaseArduinoMock();
}

TEST_F(TestLedDriver, DisplayFunctionsShouldAtFirstCalTurnOffColumnOne)
{
    EXPECT_CALL(*arduinoMock, digitalWrite(Not(COL1PIN), _)).Times(1);
    EXPECT_CALL(*arduinoMock, digitalWrite(COL1PIN, HIGH)).Times(1);

    LEDDriver ledDriver(ROW1PIN, COL1PIN);
    ledDriver.display();
    releaseArduinoMock();
}
