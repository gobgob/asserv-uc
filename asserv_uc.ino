#include <Encoder.h>

#include "config.h"
#include "utils.h"
#include "odometry.h"

Encoder coderLeft(CODER_L_A,CODER_L_B);
Encoder coderRight(CODER_R_A,CODER_R_B);

void setup()
{
	Serial.begin(115200);
	pinMode(DEBUG_PIN_GENERAL,OUTPUT);
	odo_enable();
}

void loop()
{
	DEBUG_PIN_ON;
	odo_update();
	DEBUG_PIN_OFF;
	DUMP_VAR(coderLeft.read());
	DUMP_VAR(coderRight.read());
	DUMP_VAR(odo_X);
	DUMP_VAR(odo_Y);
	DUMP_VAR(odo_angle);

	Serial.println("");

	delay(300);
}
