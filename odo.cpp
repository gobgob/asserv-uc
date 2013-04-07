#include "odo.h"
#include "utils.h"
#include "coders.h"



// valeurs de réglage
volatile double ticks_per_meters=0;
volatile double ticks_per_rads=0;

//valeurs de fonctionnement
volatile bool mutex_odo_is_running=0;
volatile bool odo_enabled = 0;

//valeurs calculées
volatile double odo_X = 0;		//metres
volatile double odo_Y = 0;		//metres
volatile double odo_angle = 0;	//radians

static void wait_for_odo();

void odo_setTickRatio(double new_ticks_per_meters,double new_ticks_per_rads)
{
	bool enable_save = odo_enabled;
	odo_disable();
	wait_for_odo();
	ticks_per_meters=new_ticks_per_meters;
	ticks_per_rads=new_ticks_per_rads;
	if(enable_save)
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

void odo_update()
{

	static int32_t old_dist_tick = 0;

	int32_t dist_right=coderRight.count;
	int32_t dist_left=coderLeft.count;

	int32_t new_dist_tick=(dist_left+dist_right)/2;
	int32_t new_angle_tick=dist_right-dist_left;

	double delta_dist=((double)(new_dist_tick-old_dist_tick))/ticks_per_meters;

	odo_angle = new_angle_tick/ticks_per_rads;

	double dX = cos(odo_angle) * delta_dist;
	double dY = sin(odo_angle) * delta_dist;

	odo_X += dX;
	odo_Y += dY;

	old_dist_tick=new_dist_tick;
}