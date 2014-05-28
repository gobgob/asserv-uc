#include "asserv_uc.h"
#include "config.h"
#include "odometry.h"
#include "utils.h"

// settings
volatile double ticks_per_meters=DEFAULT_TICK_PER_METERS;
volatile double ticks_per_rads=DEFAULT_TICK_PER_RADS;
volatile double offset_angle; 		//radians

//mutex, to avoid changing values when odo is running
volatile boolean mutex_odo_is_running=0;
volatile boolean odo_enabled = 0;

//position of the robot, calculated values
volatile double odo_X = 0;		//metres
volatile double odo_Y = 0;		//metres
volatile double odo_angle = 0;	//radians

static void wait_for_odo();

/*
Set the ratio between ticks and real world units (meters and radians)
*/
void odo_setTickRatio(double new_ticks_per_meters,double new_ticks_per_rads)
{
	boolean enable_save = odo_enabled;
	odo_disable();
	wait_for_odo();
	if(new_ticks_per_meters>0)
		ticks_per_meters=new_ticks_per_meters;
	if(new_ticks_per_rads>0)
		ticks_per_rads=new_ticks_per_rads;
	if(enable_save)
		odo_enable();
}

/*
Force the current X coordinate
*/
void odo_setX(double new_x)
{
	odo_disable();
	wait_for_odo();
	odo_X=new_x;
	odo_enable();
}

/*
Force the current Y coordinate
*/
void odo_setY(double new_y)
{
	odo_disable();
	wait_for_odo();
	odo_Y=new_y;
	odo_enable();
}

/*
Force the current angle to be new_angle.
For that we calculate an offset that will be used later
by the odometry calculation.
*/
void odo_setAngle(double new_angle_rad)
{
	odo_disable();
	wait_for_odo();
	int32_t dist_right=coderRight.read();
	int32_t dist_left=coderLeft.read();
	int32_t current_angle_tick=dist_right-dist_left;
	double current_angle_rad = current_angle_tick/ticks_per_rads;

	offset_angle=new_angle_rad-current_angle_rad;
	odo_enable();
}

void odo_enable()
{
	odo_enabled=true;
}

void odo_disable()
{
	odo_enabled=false;
}

static void wait_for_odo()
{
	while (mutex_odo_is_running)
	{
		//wait
	}
}

int32_t odo_meters2ticks(double meters)
{
	return meters*ticks_per_meters;
}

int32_t odo_rads2ticks(double rads)
{
	return rads*ticks_per_rads;
}

/*
This is the real stuff
*/
void odo_update()
{
	if (!odo_enabled)
		return;

	//acquire the mutex
	mutex_odo_is_running = 1;

	static int32_t old_dist_tick = 0;

	int32_t dist_right=coderRight.read();
	int32_t dist_left=coderLeft.read();

	//The relative distance since the last time whe updated the postion
	int32_t new_dist_tick=(dist_left+dist_right)/2;
	double delta_dist=((double)(new_dist_tick-old_dist_tick))/ticks_per_meters;

	//The absolute robot angle, corrected with the offset
	int32_t new_angle_tick=dist_right-dist_left;
	odo_angle=offset_angle+new_angle_tick/ticks_per_rads;

	//Compute the absolute position of the robot
	double dX = cos(odo_angle) * delta_dist;
	double dY = sin(odo_angle) * delta_dist;
	odo_X += dX;
	odo_Y += dY;

	//we save that for the next time we update
	old_dist_tick=new_dist_tick;

	//free the mutex
	mutex_odo_is_running = 0;
}