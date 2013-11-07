
#include <gmock/gmock.h>
#include "leddriver.h"
#include "Arduino.h"

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

using ::testing::AnyNumber;
using ::testing::AnyOf;
using ::testing::Mock;
using ::testing::Not;
using ::testing::_;
const static int cols[LEDDriver::NOCOLUMS] = {COL0PIN, COL1PIN, COL2PIN, COL3PIN, COL4PIN};
const static int rows[LEDDriver::NOROWS] = {ROW0PIN, ROW1PIN, ROW2PIN, ROW3PIN, ROW4PIN};

class TestLedDriver : public ::testing::Test {
protected:
	ArduinoMock *arduinoMock;
	LEDDriver ledDriver;
	
	TestLedDriver() : ledDriver(rows, cols) {}
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

TEST_F(TestLedDriver, DefaultShouldHaveFirstLedInFirstRowOff)
{
	EXPECT_CALL(*arduinoMock, digitalWrite(Not(COL0PIN), _)).Times(AnyNumber());
	EXPECT_CALL(*arduinoMock, digitalWrite(COL0PIN, HIGH));
	ledDriver.display();
}

TEST_F(TestLedDriver, DefaultShouldHaveSecondLedInFirstRowOff)
{
	EXPECT_CALL(*arduinoMock, digitalWrite(Not(COL1PIN), _)).Times(AnyNumber());
	EXPECT_CALL(*arduinoMock, digitalWrite(COL1PIN, HIGH));
	ledDriver.display();
}

TEST_F(TestLedDriver, DefaultShouldHaveThirdLedInFirstRowOff)
{
	EXPECT_CALL(*arduinoMock, digitalWrite(Not(COL2PIN), _)).Times(AnyNumber());
	EXPECT_CALL(*arduinoMock, digitalWrite(COL2PIN, HIGH));
	ledDriver.display();
}

TEST_F(TestLedDriver, DefaultShouldHaveForthLedInFirstRowOff)
{
	EXPECT_CALL(*arduinoMock, digitalWrite(Not(COL3PIN), _)).Times(AnyNumber());
	EXPECT_CALL(*arduinoMock, digitalWrite(COL3PIN, HIGH));
	ledDriver.display();
}

TEST_F(TestLedDriver, DefaultShouldHaveFifthLedInFirstRowOff)
{
	EXPECT_CALL(*arduinoMock, digitalWrite(Not(COL4PIN), _)).Times(AnyNumber());
	EXPECT_CALL(*arduinoMock, digitalWrite(COL4PIN, HIGH));
	ledDriver.display();
}

TEST_F(TestLedDriver, SecondCallShouldTurnRowOneOffAndRowTwoOn)
{
	EXPECT_CALL(*arduinoMock, digitalWrite(_, _)).Times(AnyNumber());
	ledDriver.display();
	Mock::VerifyAndClearExpectations(arduinoMock);
		
	EXPECT_CALL(*arduinoMock, digitalWrite(ROW0PIN, LOW)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(ROW1PIN, HIGH)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(Not(AnyOf(ROW0PIN, ROW1PIN)), _)).Times(AnyNumber());
	ledDriver.display();
}

TEST_F(TestLedDriver, LightingFirstLEdInFirstRow)
{
	int matrix[5][5] = { {1,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0} };
	ledDriver.show((int*)matrix);
	EXPECT_CALL(*arduinoMock, digitalWrite(Not(COL0PIN), _)).Times(AnyNumber());
	EXPECT_CALL(*arduinoMock, digitalWrite(COL0PIN, LOW));
	ledDriver.display();
};

TEST_F(TestLedDriver, MakeSureThatTheRowsAreWrapping)
{
	EXPECT_CALL(*arduinoMock, digitalWrite(_, _)).Times(AnyNumber());
	ledDriver.display(); // row 0
	ledDriver.display(); // row 1
	ledDriver.display(); // row 2
	ledDriver.display(); // row 3
	ledDriver.display(); // row 4
	Mock::VerifyAndClearExpectations(arduinoMock);
		
	EXPECT_CALL(*arduinoMock, digitalWrite(ROW4PIN, LOW)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(ROW0PIN, HIGH)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(Not(AnyOf(ROW4PIN, ROW0PIN)), _)).Times(AnyNumber());
	ledDriver.display();
}
