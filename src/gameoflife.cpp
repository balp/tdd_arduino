#include "Arduino.h"
#include "timer.h"
Timer timerHandler;

void setup()
{
}

void loop()
{
    int timeout = timerHandler.handleTimeouts();
    if(timeout < 0) {
        timeout = 100;
    }
    delay(timeout);
}
