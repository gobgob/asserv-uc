#include "asserv.h"
#include "utils.h"
#include "hbridge.h"
#include "conf.h"

HBridge motorLeft(MOTORL_PWM,MOTORL_DIR,0);
HBridge motorRight(MOTORR_PWM,MOTORR_DIR,0);

volatile bool asserv_enabled = 0;

volatile int32_t target_dist=0;		//distance cumulée à atteindre
volatile int32_t target_angle=0;	//angle à atteindre

volatile int32_t speed_right=0;		//vittesse roue droite, ticks/itération
volatile int32_t speed_left=0;		//vittesse roue gauche, ticks/itération

volatile int32_t lastdist_right=0;	//distance cumulée à l'itération précédente
volatile int32_t lastdist_left=0;	//angle à l'itération précédente
volatile int32_t dist=0;			//distance cumulé actuelle
volatile int32_t angle=0;			//angle actuel

volatile int32_t speed_dist=0;		//vitesse globale du robot
volatile int32_t speed_angle=0;		//vitesse angulaire du robot

volatile int32_t Kp_dist=5*1024;
volatile int32_t Kp_angle=5*1024;

volatile int32_t Kd_dist=0;
volatile int32_t Kd_angle=0;

volatile int32_t err_dist=0;
volatile int32_t err_angle=0;

volatile int32_t cmd_dist=0;
volatile int32_t cmd_angle=0;

volatile int32_t cmd_right=0;
volatile int32_t cmd_left=0;

volatile int32_t dist_right=0;
volatile int32_t dist_left=0;

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


void asserv_run()
{
	if (!asserv_enabled)
		return;

	digitalWrite(DEBUG_PIN_ASSERV,HIGH);


	//dist_right=coderRight.count;
	//dist_left=coderLeft.count;

	dist=(dist_left+dist_right)/2;
	angle=dist_right-dist_left;

	speed_right=(dist_right-lastdist_right);
	speed_left=(dist_left-lastdist_left);

	speed_dist=(speed_right+speed_left)/2;
	speed_angle=speed_right-speed_left;

	err_dist = target_dist-dist;
	err_angle = target_angle-angle;

	cmd_dist=err_dist*Kp_dist;//-Kd_dist*speed_dist;
	cmd_angle=err_angle*Kp_angle;//-Kd_angle*speed_angle;

	cmd_right=cmd_dist+cmd_angle;
	cmd_left=cmd_dist-cmd_angle;

	motorRight.setSpeed(cmd_right/1024);
	motorLeft.setSpeed(cmd_left/1024);

	digitalWrite(DEBUG_PIN_ASSERV,LOW);
}