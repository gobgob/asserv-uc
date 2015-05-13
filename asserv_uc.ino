#include <Encoder.h>
#include <Servo.h>
#include <Ping.h>

#include <Wire.h>
#include <SFE_VL6180X.h>


#include "config.h"
#include "utils.h"
#include "odometry.h"
#include "asserv.h"
#include "hbridge.h"
#include "navigation.h"
#include "i2c.h"
#include "api.h"

#define VL6180X_ADDRESS 0x29
VL6180xIdentification identification;
VL6180x sensor(VL6180X_ADDRESS);

// Encoder coderLeft(CODER_L_A,CODER_L_B);
// Encoder coderRight(CODER_R_A,CODER_R_B);
HBridge motorLeft(MOTOR_L_PWM,MOTOR_L_DIR,MOTOR_L_BRAKE);
HBridge motorRight(MOTOR_R_PWM,MOTOR_R_DIR,MOTOR_R_BRAKE);

Ping ping = Ping(ULTRASOUND_PIN);

IntervalTimer timer;
IntervalTimer timerRatatouille;

Servo servo[SERVO_MAX];

static void refreshStatus();


volatile int32_t left_coder_position;
volatile int32_t right_coder_position;

static void LA_up()
{
	// DEBUG_PIN_ON;
	noInterrupts();
	if(digitalRead(CODER_L_B))
		left_coder_position+=4;
	else
		left_coder_position-=4;
	interrupts();
	// DEBUG_PIN_OFF;
}

static void RA_up()
{
	// DEBUG_PIN_ON;
	noInterrupts();
	if(digitalRead(CODER_R_B))
		right_coder_position+=4;
	else
		right_coder_position-=4;
	interrupts();
	// DEBUG_PIN_OFF;
}

int32_t coderRightread()
{
	noInterrupts();
	int32_t tmp = right_coder_position;
	interrupts();
	return tmp;
}

int32_t coderLeftread()
{
	noInterrupts();
	int32_t tmp = left_coder_position;
	interrupts();
	return tmp;
}

void coderRightwrite(int32_t tmp)
{
	noInterrupts();
	right_coder_position = tmp;
	interrupts();
}

void coderLeftwrite(int32_t tmp)
{
	noInterrupts();
	left_coder_position = tmp;
	interrupts();
}



void setup()
{
	pinMode(DEBUG_PIN_GENERAL,OUTPUT);

	// Ping ping = Ping(ULTRASOUND_PIN);

	Serial.begin(115200);
	i2c_init();
	timer.begin(refreshStatus, 1000000/REFRESH_FREQ);

	motorRight.setup();
	motorLeft.setup();
	
	asserv_setCoeffDist(40,0);
	asserv_setCoeffAngle(40,0);
	asserv_setSpeedMaxDist(110000);
	asserv_setSpeedMaxAngle(90000);
	asserv_setTarget(0,0,ABS);

	pinMode(CODER_L_A, INPUT);
	pinMode(CODER_L_B, INPUT);
	attachInterrupt(CODER_L_A, LA_up, RISING);
	pinMode(CODER_R_A, INPUT);
	pinMode(CODER_R_B, INPUT);
	attachInterrupt(CODER_R_A, RA_up, RISING);

	if(sensor.VL6180xInit() != 0){
		Serial.println("FAILED TO INITALIZE"); //Initialize device and check for errors
	}; 
	odo_enable();
	asserv_enable();
}

void loop()
{

	serial_process();

	if(cmd_callback)
	{
		// delay(10);
			// Serial.println("############################"); //dont remove
		int cb = cmd_callback();
		if (cb) {
			cmd_callback=NULL;
		}
	}

  	
	// pinMode(ULTRASOUND_PIN,OUTPUT);
	// digitalWrite(ULTRASOUND_PIN, HIGH); 
	// delayMicroseconds(10); 
	// digitalWrite(ULTRASOUND_PIN, LOW);
	// pinMode(ULTRASOUND_PIN,OUTPUT);
 //  	DUMP_VAR(pulseIn(ULTRASOUND_PIN, HIGH)); 



	//DUMP_VAR(odo_angle);
	// DUMP_VAR(coderLeft.read());
	// DUMP_VAR(coderRight.read());
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
