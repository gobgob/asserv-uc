#include "api.h"
#include "asserv.h"
#include "odo.h"
#include "conf.h"
#include "utils.h"
#include "spi.h"

bool (*cmd_callback)()=NULL;

///////////////////////_goForward

// float cmd_start_odo_X = 0;
// float cmd_start_odo_Y = 0;
int32_t cmd_start_dist = 0;
int32_t cmd_end_dist = 0; 
int32_t cmd_end_angle = 0; 

bool cmd_cb_goForwardOrBackward()
{
	
	//Serial.println("cmd_cb_goForward()");
	return ((cmd_end_dist-dist)>=odo_meters2ticks(ACK_DIST) || abs(cmd_end_dist-dist)<ZONE_51);
}

void cmd_goForwardOrBackward(uint16_t rel_dist,int8_t sign)
{
	//Serial.println("cmd_goForward ");
	cmd_callback=cmd_cb_goForwardOrBackward;

	cmd_start_dist = dist;
	int32_t dist_to_parcour = sign*odo_meters2ticks(rel_dist/1000.);
	cmd_end_dist = dist + dist_to_parcour;
	asserv_setTarget(dist_to_parcour,0,DEST_REL|ANGL_REL);
}


bool cmd_cb_rotate()
{	
	//Serial.println("cmd_cb_rotate()");
// return ((cmd_end_dist-dist)>=odo_meters2ticks(ACK_DIST) || abs(cmd_end_dist-dist)<ZONE_51);
// lk
	return false;
}

void cmd_rotate(int16_t rel_angle)
{
	Serial.println("cmd_rotate ");
	cmd_callback=cmd_cb_rotate;

	Serial.println(rel_angle);
	delay(2000);
	int32_t angle_to_parcour = odo_rads2ticks(rel_angle/1000.);
	cmd_end_angle = angle+angle_to_parcour; 
	asserv_setTarget(0,angle_to_parcour,DEST_REL|ANGL_REL);
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
