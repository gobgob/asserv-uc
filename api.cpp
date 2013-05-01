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
int32_t cmd_end_angle = 0; 
unsigned long cmd_start_time;

bool cmd_cb_goForwardOrBackward()
{
	//Serial.println("cmd_cb_goForward()");
	return ((cmd_end_dist-dist)<=odo_meters2ticks(ACK_DIST));
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
	return ((cmd_end_angle-angle)<=odo_rads2ticks(ACK_ANGLE));
}

void cmd_rotate(int16_t rel_angle)
{
	//Serial.println("cmd_rotate ");
	cmd_callback_ack=cmd_cb_rotate;

	//Serial.println(rel_angle);
	int32_t angle_to_parcour = odo_rads2ticks(rel_angle/1000.);
	cmd_end_angle = angle+angle_to_parcour; 
	asserv_setTarget(0,angle_to_parcour,DEST_REL|ANGL_REL);
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

void cmd_goto(int16_t new_x, int16_t new_y, int16_t delta_max)
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

void cmd_reboot()
{
	wdt_enable(WDTO_30MS);
	while(1) {};
}

