#include <Encoder.h>

#include "config.h"
#include "utils.h"
#include "odometry.h"
#include "asserv.h"
#include "hbridge.h"
#include "navigation.h"

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
	
	asserv_setCoeffDist(1*9000,0);
	asserv_setCoeffAngle(1*10000,0);
	asserv_setSpeedMaxDist(900000);
	asserv_setSpeedMaxAngle(900000);
	asserv_setTarget(0,0,ABS);

	odo_enable();
	asserv_enable();
}

void loop()
{
	//DUMP_VAR(coderLeft.read());
	//DUMP_VAR(coderRight.read());
	DUMP_VAR(odo_X*1000);
	DUMP_VAR(odo_Y*1000);
	//DUMP_VAR(odo_angle);
	// DUMP_VAR(coderLeft.read());
	// DUMP_VAR(coderRight.read());
	// DUMP_VAR(motorRight.getSpeed());
	// DUMP_VAR(motorLeft.getSpeed());
	delay(100);

	nav_gotoPoint(0.4,0.4,0.03);
	// motorLeft.setSpeed(100);
	// motorRight.setSpeed(200);



	//delay(300);
}

static void refreshStatus()
{
	DEBUG_PIN_ON;
	odo_update();
	asserv_run();
	DEBUG_PIN_OFF;
}
