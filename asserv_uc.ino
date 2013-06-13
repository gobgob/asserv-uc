#include <Encoder.h>

#include "config.h"
#include "utils.h"
#include "odometry.h"
#include "hbridge.h"

Encoder coderLeft(CODER_L_A,CODER_L_B);
Encoder coderRight(CODER_R_A,CODER_R_B);
HBridge motorLeft(MOTOR_L_PWM,MOTOR_L_DIR,MOTOR_L_BRAKE);
HBridge motorRight(MOTOR_R_PWM,MOTOR_R_DIR,MOTOR_R_BRAKE);

IntervalTimer timer;

static void refreshStatus();

void setup()
{
	pinMode(DEBUG_PIN_GENERAL,OUTPUT);

	Serial.begin(115200);
	timer.begin(refreshStatus, 1000000/REFRESH_FREQ);

	motorRight.setup();
	motorLeft.setup();
	
	odo_enable();
}

void loop()
{
	DUMP_VAR(coderLeft.read());
	DUMP_VAR(coderRight.read());
	DUMP_VAR(odo_X);
	DUMP_VAR(odo_Y);
	DUMP_VAR(odo_angle);
	Serial.println("");	
	delay(300);
}

static void refreshStatus()
{
	DEBUG_PIN_ON;
	odo_update();
	DEBUG_PIN_OFF;
}
