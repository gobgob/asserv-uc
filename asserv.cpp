#include "asserv.h"
#include "utils.h"
#include "hbridge.h"
#include "conf.h"
#include "coders.h"
#include "odo.h"

HBridge motorLeft(MOTORL_PWM,MOTORL_DIR,0);
HBridge motorRight(MOTORR_PWM,MOTORR_DIR,0);

//valeurs de réglage
volatile int32_t speed_max_dist=0;
volatile int32_t speed_max_angle=0;

volatile int32_t acc_max=0;

volatile int32_t target_dist=0;		//distance cumulée à atteindre
volatile int32_t target_angle=0;	//angle à atteindre

volatile int32_t Kp_dist=0;
volatile int32_t Kp_angle=0;

volatile int32_t Kd_dist=0;
volatile int32_t Kd_angle=0;

volatile int32_t err_dist=0;
volatile int32_t err_angle=0;

//valeurs de fonctionnement
volatile bool mutex_asserve_is_running=0;
volatile bool asserv_enabled = 0;

//valeurs calculées
volatile int32_t old_dist_right=0;
volatile int32_t old_dist_left=0;

void asserv_setup()
{
	pinMode(DEBUG_PIN_ASSERV,OUTPUT);
	motorRight.setup();
	motorLeft.setup();

	/*timer setup*/
	TCCR1A = 0;
	TCCR1B = 0;
	OCR1A=16000000/PID_FREQ; //setup frequency
	TCNT1=0;
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << CS10);// Set 1 prescaler = 1
	TIMSK1 = (1 << OCIE1A);//enable interrupt sur comparaison réussie
}

void asserv_enable()
{
	asserv_enabled=true;
}
void asserv_disable()
{
	asserv_enabled=false;
}

void wait_for_asserve()
{
	while (mutex_asserve_is_running)
	{
		//wait
	}
}

void asserv_setCoeffDist(int32_t new_Kp_dist,int32_t new_Kd_dist)
{
	bool enable_save = asserv_enabled;
	asserv_disable();
	wait_for_asserve();
	Kp_dist=new_Kp_dist;
	Kd_dist=new_Kd_dist;
	if(enable_save)
		asserv_enable();
}

void asserv_setCoeffAngle(int32_t new_Kp_angle,int32_t new_Kd_angle)
{
	bool enable_save = asserv_enabled;
	asserv_disable();
	wait_for_asserve();
	Kp_angle=new_Kp_angle;
	Kd_angle=new_Kd_angle;
	if(enable_save)
		asserv_enable();
}

void asserv_setAccMaxDist(uint32_t new_acc_max)
{
	bool enable_save = asserv_enabled;
	asserv_disable();
	wait_for_asserve();
	acc_max=new_acc_max;
	if(enable_save)
		asserv_enable();
}

void asserv_setSpeedMaxDist(uint32_t new_speed_max_dist)
{
	bool enable_save = asserv_enabled;
	asserv_disable();
	wait_for_asserve();
	speed_max_dist=new_speed_max_dist;
	if(enable_save)
		asserv_enable();
}

void asserv_setSpeedMaxAngle(uint32_t new_speed_max_angle)
{
	bool enable_save = asserv_enabled;
	asserv_disable();
	wait_for_asserve();
	speed_max_angle=new_speed_max_angle;
	if(enable_save)
		asserv_enable();
}

void asserv_setAbsTarget(int32_t new_dist,int32_t new_angle)
{
	bool enable_save = asserv_enabled;
	asserv_disable();
	wait_for_asserve();
	target_dist=new_dist;
	target_angle=new_angle;
	if(enable_save)
		asserv_enable();
}

void asserv_setRelTarget(int32_t new_dist,int32_t new_angle)
{
	bool enable_save = asserv_enabled;
	asserv_disable();
	wait_for_asserve();
	target_dist+=new_dist;
	target_angle+=new_angle;
	if(enable_save)
		asserv_enable();
}

void asserv_run()
{
	if (!asserv_enabled)
		return;

	mutex_asserve_is_running=true;

	int32_t dist_right=coderRight.count;
	int32_t dist_left=coderLeft.count;

	int32_t dist=(dist_left+dist_right)/2;
	int32_t angle=dist_right-dist_left;

	int32_t speed_right=(dist_right-old_dist_right);
	int32_t speed_left=(dist_left-old_dist_left);

	int32_t speed_dist=(speed_right+speed_left)/2;
	int32_t speed_angle=speed_right-speed_left;

	err_dist = target_dist-dist;
	err_angle = target_angle-angle;

	int32_t cmd_dist=err_dist*Kp_dist-Kd_dist*speed_dist;
	int32_t cmd_angle=err_angle*Kp_angle-Kd_angle*speed_angle;

	cmd_dist=maximize(cmd_dist,speed_max_dist);
	cmd_angle=maximize(cmd_angle,speed_max_angle);

	int32_t cmd_right=cmd_dist+cmd_angle;
	int32_t cmd_left=cmd_dist-cmd_angle;

	motorRight.setSpeed(cmd_right/1024);
	motorLeft.setSpeed(cmd_left/1024);

	old_dist_right=dist_right;
	old_dist_left=dist_left;

	mutex_asserve_is_running=false;
}
