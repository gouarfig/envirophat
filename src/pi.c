#include <wiringPi.h>

void initPi()
{
	static int initialized = 0;

	if (initialized == 0) {
		wiringPiSetup();
		piHiPri(55);
		initialized = 1;
	}
}
