#include "Arduino.h"
#include "timer.h"
#include "leddriver.h"
#include "gameoflife.h"

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

Timer timerHandler;
LedDriver ledDriver(ROW0PIN, ROW1PIN, ROW2PIN, ROW3PIN, ROW4PIN,
      COL0PIN, COL1PIN, COL2PIN, COL3PIN, COL4PIN);

static int seed[5][5] = {{0,0,0,0,0}, {0,0,0,0,0}, {0,1,1,1,0}, {0,0,0,0,0}, {0,0,0,0,0}};
GameOfLife gameOfLife(seed, &ledDriver);

class GameUpdater : public Timer::CallbackInterface {
  public:
    virtual ~GameUpdater() { }
    virtual void onTimeout() {
      gameOfLife.tick();
    }
} gameUpdater;

class DisplayUpdater : public Timer::CallbackInterface {
  public:
    virtual ~DisplayUpdater() { }
    virtual void onTimeout() {
      ledDriver.display();
    }
} displayUpdater;

static int on[5][5] = {{1,1,1,1,1}, {1,1,1,1,1}, {1,1,1,1,1}, {1,1,1,1,1}, {1,1,1,1,1}};
static int off[5][5] = {{0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}};
void setup()
{
  ledDriver.init();
  timerHandler.addTimer(displayUpdater, 2, true);
  timerHandler.addTimer(gameUpdater, 1000, true);
  ledDriver.show((int*)on);
}
static int i = 0;
void loop()
{
  int timeout = timerHandler.handleTimeouts();
  delay(timeout);
}
