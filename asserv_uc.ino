#include <Encoder.h>

#include "config.h"

Encoder coderLeft(CODER_L_A,CODER_L_B);
Encoder coderRight(CODER_R_A,CODER_R_B);

void setup()
{
	Serial.begin(115200);
}

int32_t oldPosition	= -999;

void loop()
{
	int32_t newPosition = coderLeft.read();
	if (newPosition != oldPosition)
	{
		oldPosition = newPosition;
		Serial.println(newPosition);
	}
}
