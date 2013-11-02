#include "timer.h"
#include "gmock/gmock.h"
#include "Arduino.h"

#include "debug.h"
using ::testing::Return;

class TestTimer : public ::testing::Test {
    protected:
    class MockTimerCallback : public Timer::CallbackInterface {
        public:
            virtual ~MockTimerCallback() {}
            MOCK_METHOD0(onTimeout, void());
    };
    ArduinoMock* arduinoMock;
    TestTimer() : arduinoMock( arduinoMockInstance() ) {}
    virtual ~TestTimer() {
        releaseArduinoMock();
    }
};

TEST_F(TestTimer, SimpleTimer)
{
    MockTimerCallback cb;
    EXPECT_CALL(*arduinoMock, millis())
        .Times(2)
        .WillOnce(Return(1))
        .WillOnce(Return(2));
    EXPECT_CALL(cb, onTimeout()).Times(0);
    Timer timer;
    timer.addTimer(cb, 100, false);
    EXPECT_EQ(99, timer.handleTimeouts());
}

TEST_F(TestTimer, SimpleTimeout)
{
    MockTimerCallback cb;
    EXPECT_CALL(*arduinoMock, millis())
        .Times(3)
        .WillOnce(Return(1))
        .WillOnce(Return(2))
        .WillOnce(Return(101))
        ;
    EXPECT_CALL(cb, onTimeout()).Times(1);
    Timer timer;
    timer.addTimer(cb, 100, false);
    EXPECT_EQ(99, timer.handleTimeouts());
    EXPECT_EQ(-1, timer.handleTimeouts());
}

TEST_F(TestTimer, RepeatingTimer)
{
    MockTimerCallback cb;
    EXPECT_CALL(*arduinoMock, millis())
        .Times(3)
        .WillOnce(Return(1))
        .WillOnce(Return(2))
        .WillOnce(Return(101))
        ;
    EXPECT_CALL(cb, onTimeout()).Times(1);
    Timer timer;
    timer.addTimer(cb, 100, true);
    EXPECT_EQ(99, timer.handleTimeouts());
    EXPECT_EQ(100, timer.handleTimeouts());
}

TEST_F(TestTimer, RemoveRepeatingTimer)
{
    MockTimerCallback cb;
    EXPECT_CALL(*arduinoMock, millis())
        .Times(3)
        .WillOnce(Return(1))
        .WillOnce(Return(2))
        .WillOnce(Return(101))
        ;
    EXPECT_CALL(cb, onTimeout()).Times(1);
    Timer timer;
    timer.addTimer(cb, 100, true);
    EXPECT_EQ(99, timer.handleTimeouts());
    EXPECT_EQ(100, timer.handleTimeouts());
    timer.removeTimer(cb);
    EXPECT_EQ(-1, timer.handleTimeouts());
}

TEST_F(TestTimer, RemoveAndAddTimer)
{
    MockTimerCallback timer_one_cb;
    MockTimerCallback timer_two_cb;
    EXPECT_CALL(*arduinoMock, millis())
        .Times(6)
        .WillOnce(Return(1))
        .WillOnce(Return(2))
        .WillOnce(Return(101))
        .WillOnce(Return(102))
        .WillOnce(Return(102))
        .WillOnce(Return(202))
        ;
    EXPECT_CALL(timer_one_cb, onTimeout()).Times(1);
    EXPECT_CALL(timer_two_cb, onTimeout()).Times(1);
    Timer timer;
    timer.addTimer(timer_one_cb, 100, true);
    EXPECT_EQ(99, timer.handleTimeouts());
    EXPECT_EQ(100, timer.handleTimeouts());
    timer.removeTimer(timer_one_cb);
    EXPECT_EQ(-1, timer.handleTimeouts());
    timer.addTimer(timer_two_cb, 100, true);
    EXPECT_EQ(100, timer.handleTimeouts());
    EXPECT_EQ(100, timer.handleTimeouts());
}
TEST_F(TestTimer, RepetingTimerAndOtherTimer)
{
    EXPECT_CALL(*arduinoMock, millis())
        .Times(10)
        .WillOnce(Return(1))
        .WillOnce(Return(1))
        .WillOnce(Return(1))
        .WillOnce(Return(11))
        .WillOnce(Return(21))
        .WillOnce(Return(31))
        .WillOnce(Return(31))
        .WillOnce(Return(32))
        .WillOnce(Return(32))
        .WillOnce(Return(62))
        ;
    MockTimerCallback timer_one_cb;
    MockTimerCallback timer_two_cb;
    MockTimerCallback timer_three_cb;
    EXPECT_CALL(timer_one_cb, onTimeout()).Times(3);
    EXPECT_CALL(timer_two_cb, onTimeout()).Times(1);
    EXPECT_CALL(timer_three_cb, onTimeout()).Times(1);
    Timer timer;
    timer.addTimer(timer_two_cb, 30, false);
    timer.addTimer(timer_one_cb, 10, true);
    EXPECT_EQ(10, timer.handleTimeouts());
    EXPECT_EQ(10, timer.handleTimeouts());
    EXPECT_EQ(10, timer.handleTimeouts());
    EXPECT_EQ(0, timer.handleTimeouts());
    EXPECT_EQ(10, timer.handleTimeouts());
    timer.removeTimer(timer_one_cb);
    timer.addTimer(timer_three_cb, 30, false);
    EXPECT_EQ(30, timer.handleTimeouts());
    EXPECT_EQ(-1, timer.handleTimeouts());

}

TEST_F(TestTimer, TwoTimersAfterEachOther)
{
    MockTimerCallback cb_one;
    MockTimerCallback cb_two;
    EXPECT_CALL(*arduinoMock, millis())
        .Times(4)
        .WillOnce(Return(1))
        .WillOnce(Return(2))
        .WillOnce(Return(3))
        .WillOnce(Return(101))
        ;
    EXPECT_CALL(cb_one, onTimeout()).Times(1);
    EXPECT_CALL(cb_two, onTimeout()).Times(0);
    Timer timer;
    timer.addTimer(cb_one, 100, false);
    timer.addTimer(cb_two, 100, false);
    EXPECT_EQ(98, timer.handleTimeouts());
    EXPECT_EQ(1, timer.handleTimeouts());
}

TEST_F(TestTimer, MainLoop)
{
    boolean g_exitflag = false;
    class MyTimerCallback : public Timer::CallbackInterface {
        public:
            boolean& m_flag;
            MyTimerCallback(boolean& flag) : m_flag(flag) {}

            virtual ~MyTimerCallback() {}
            virtual void onTimeout() {
                m_flag = true;
            }
    };
    MyTimerCallback cb(g_exitflag);
    EXPECT_CALL(*arduinoMock, millis())
        .Times(3)
        .WillOnce(Return(1)) // Add the timer here
        .WillOnce(Return(2)) // First loop, delay 99
        .WillOnce(Return(101)) ; // After delay
    EXPECT_CALL(*arduinoMock, delay(99))
        .Times(1);
    Timer timerHandler;
    timerHandler.addTimer(cb, 100, false);
    int c = 0;
    LOG << "loop()" << std::endl;
    while(!g_exitflag) {
        unsigned long loopdelay = timerHandler.handleTimeouts();
        if(loopdelay == -1) {
            break;
        }
        delay(loopdelay);
        if(c++ > 1) g_exitflag = true;
    }
}

