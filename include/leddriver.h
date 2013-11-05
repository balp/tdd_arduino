
#include "Arduino.h"

class LEDDriver
{
public:
	void display() {
		digitalWrite(13, HIGH);
	}
};