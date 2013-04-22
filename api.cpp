#include "api.h"
#include "asserv.h"
#include "odo.h"
#include "conf.h"
#include "utils.h"

bool (*cmd_callback)()=NULL;

///////////////////////_goForward

float cmd_start_odo_X = 0;
float cmd_start_odo_Y = 0;

bool cmd_cb_goForwardOrBackward()
{
	
	Serial.println("cmd_cb_goForward()");
	Serial.println(pythagore(odo_X-cmd_start_odo_X,odo_Y-cmd_start_odo_Y));
	delay(300);
	if(pythagore(odo_X-cmd_start_odo_X,odo_Y-cmd_start_odo_Y)>(18-ACK_DIST))
	{
		return true;
	}
	return false;
}

void cmd_goForwardOrBackward(uint16_t rel_dist,int8_t sign)
{
	Serial.print("cmd_goForward ");
	Serial.println(rel_dist);
	cmd_callback=cmd_cb_goForward;
	cmd_start_odo_X = odo_X;
	cmd_start_odo_Y = odo_Y;
	Serial.print("cmd_start_odo_X=");
	Serial.println(cmd_start_odo_X);
	Serial.print("cmd_start_odo_Y=");
	Serial.println(cmd_start_odo_Y);
	asserv_setTarget(sign*odo_meters2ticks(rel_dist/1000.),0,DEST_ABS|ANGL_REL);
}

void cmd_rotate(int16_t angle)
{
	Serial.print("cmd_goForward ");
	Serial.println(rel_dist);
	cmd_callback=cmd_cb_goForward;
	cmd_start_odo_X = odo_X;
	cmd_start_odo_Y = odo_Y;
	Serial.print("cmd_start_odo_X=");
	Serial.println(cmd_start_odo_X);
	Serial.print("cmd_start_odo_Y=");
	Serial.println(cmd_start_odo_Y);
	asserv_setTarget(sign*odo_meters2ticks(rel_dist/1000.),0,DEST_ABS|ANGL_REL);
}
