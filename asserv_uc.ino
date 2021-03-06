#include <Encoder.h>
#include <Servo.h>
#include <Ping.h>


#include "config.h"
#include "utils.h"
#include "odometry.h"
#include "asserv.h"
#include "hbridge.h"
#include "navigation.h"
#include "i2c.h"
#include "api.h"

Encoder coderLeft(CODER_L_A,CODER_L_B);
Encoder coderRight(CODER_R_A,CODER_R_B);
HBridge motorLeft(MOTOR_L_PWM,MOTOR_L_DIR,MOTOR_L_BRAKE);
HBridge motorRight(MOTOR_R_PWM,MOTOR_R_DIR,MOTOR_R_BRAKE);

Servo servoBrasLeft;
Servo servoBrasRight;

//Ping ping = Ping(ULTRASOUND_PIN);

IntervalTimer timer;

static void refreshStatus();

void setup()
{
	pinMode(DEBUG_PIN_GENERAL,OUTPUT);

	servoBrasLeft.attach(SERVO_BRAS_LEFT);
	servoBrasRight.attach(SERVO_BRAS_RIGHT);

	servoBrasLeft.write(SERVO_BRAS_LEFT_IDLE);
	servoBrasRight.write(SERVO_BRAS_RIGHT_IDLE);

	//Ping ping = Ping(ULTRASOUND_PIN);

	Serial.begin(115200);
	i2c_init();
	timer.begin(refreshStatus, 1000000/REFRESH_FREQ);

	motorRight.setup();
	motorLeft.setup();
	
	asserv_setCoeffDist(1*9000,0);
	asserv_setCoeffAngle(1*10000,0);
	asserv_setSpeedMaxDist(200000);
	asserv_setSpeedMaxAngle(200000);
	asserv_setTarget(0,0,ABS);

	odo_enable();
	asserv_enable();
}

void loop()
{

	serial_process();

	if(cmd_callback) {
		// delay(10);
			// Serial.println("############################"); //dont remove
		int cb = cmd_callback();
		if (cb) {
			cmd_callback=NULL;
		}
	}

	// DUMP_VAR(odo_angle);
	DUMP_VAR(coderLeft.read());
	DUMP_VAR(coderRight.read());
	// DUMP_VAR(motorRight.getSpeed());
	// DUMP_VAR(motorLeft.getSpeed());
	//nav_gotoPoint(0.4,0.4,0.03);
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
