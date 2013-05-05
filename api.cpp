#include "api.h"
#include "asserv.h"
#include "odo.h"
#include "conf.h"
#include "utils.h"
#include "spi.h"
#include "navigation.h"

#include <avr/io.h>
#include <avr/wdt.h>

bool (*cmd_callback)()=NULL;
bool (*cmd_callback_ack)()=NULL;

///////////////////////_goForward

// float cmd_start_odo_X = 0;
// float cmd_start_odo_Y = 0;
int32_t cmd_start_dist = 0;
int32_t cmd_end_dist = 0; 
double cmd_end_angle = 0; 
unsigned long cmd_start_time;

bool cmd_cb_goForwardOrBackward()
{
	int ret = (abs(cmd_end_dist-dist)<=odo_meters2ticks(ACK_DIST));
	return ret;
}

void cmd_goForwardOrBackward(uint16_t rel_dist,int8_t sign)
{
	//Serial.println("cmd_goForward ");
	cmd_callback_ack=cmd_cb_goForwardOrBackward;
	cmd_start_dist = dist;
	int32_t dist_to_parcour = sign*odo_meters2ticks(rel_dist/1000.);
	cmd_end_dist = dist + dist_to_parcour;
	asserv_setTarget(dist_to_parcour,0,DEST_REL|ANGL_REL);
}


bool cmd_cb_rotate()
{	
	//Serial.println("cmd_cb_rotate()");
	return (abs(cmd_end_angle-odo_angle)<=ACK_ANGLE);
}

void cmd_rotate(int32_t n_angle, uint8_t isAbs)
{
	//Serial.println("cmd_rotate ");
	cmd_callback_ack=cmd_cb_rotate;

	//Serial.println(rel_angle);
	double n_angle_rad=n_angle/1000.;

	if(isAbs)
	{
		// Serial.println("IS ABS");
		// delay(4000);
		n_angle_rad=closest_equivalent_angle(odo_angle,n_angle_rad);
		double diff = n_angle_rad-odo_angle;
		int32_t angle_to_parcour = odo_rads2ticks(diff);
		cmd_end_angle = n_angle_rad;
		asserv_setTarget(0,angle_to_parcour,DEST_REL|ANGL_REL); 
	}else{
		// Serial.println("IS NOT ABS");
		// delay(4000);
		int32_t angle_to_parcour = odo_rads2ticks(n_angle_rad);
		cmd_end_angle = odo_angle+n_angle_rad; 
		asserv_setTarget(0,angle_to_parcour,DEST_REL|ANGL_REL);
	}

}



double goto_x=0; 
double goto_y=0; 
double goto_delta=0; 

bool cmd_cb_goto()
{
	// Serial.println(goto_x);
	// Serial.println(goto_y);
	// Serial.println(goto_delta);
	return nav_gotoPoint(goto_x,goto_y,goto_delta);
}

void cmd_goto(int32_t new_x, int32_t new_y, int32_t delta_max)
{
	cmd_callback=cmd_cb_goto;
	cmd_callback_ack=cmd_cb_goto;
	goto_x=new_x/1000.;
	goto_y=new_y/1000.;
	goto_delta=delta_max/1000.;

	// Serial.println(goto_x);
	// Serial.println(goto_y);
	// Serial.println(goto_delta);
	// delay(5000);
}


///////////////////////getter
void cmd_getOdo(uint8_t * data)
{
	int32_t x = odo_X*1000;
	int32_t y = odo_Y*1000;
	int32_t a = odo_angle*1000;
	SPLITINT32T(x,data,0);
	SPLITINT32T(y,data,4);
	SPLITINT32T(a,data,8);
}

void cmd_getStatus(uint8_t * data)
{
	int cb = 0;
	if(cmd_callback_ack)
	{
		cb = cmd_callback_ack();
	}

	data[0]=block_flags | (cb<<4);
}

void cmd_getKpKdLin(uint8_t * data)
{
	uint32_t kp;
	uint32_t kd;
	asserv_getCoeffDist(&kp,&kd);
	SPLITUINT32T(kp,data,0);
	SPLITUINT32T(kd,data,4);
}
void cmd_getKpKdRot(uint8_t * data)
{
	uint32_t kp;
	uint32_t kd;
	asserv_getCoeffAngle(&kp,&kd);
	SPLITUINT32T(kp,data,0);
	SPLITUINT32T(kd,data,4);
}


void cmd_reboot()
{
	wdt_enable(WDTO_30MS);
	while(1) {};
}

