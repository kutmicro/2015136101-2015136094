#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#include <thePins_arduino.h>
#endif

class MSGEQ7
{
public:
	MSGEQ7();
	void init(int value, int strobePin, int resetPin);
	void init();
	void poll();

	int getValue(int index);

private:
	int Pin; // read left value
	int strobePin; // strobe is attached to digital pin 2
	int resetPin; // reset is attached to digital pin 3

	int spectrumValues[7];
};
