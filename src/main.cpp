// Main startup program, currently copied from Arduino library.
// 

#include "Arduino.h"

int main(void)
{
  init();

#if defined(USBCON)
  USBDevice.attach();
#endif

  setup(); // Run my setup function.

  for (;;) { // Main buzy loop
    loop();
    if (serialEventRun) serialEventRun();
  }

  return 0;
}

