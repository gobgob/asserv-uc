#include "odo.h"
#include "utils.h"
#include "coders.h"



// valeurs de réglage
volatile double ticksByMeters=1100;
volatile double tickbyRads=263.56058576;

//valeurs calculées
volatile double odo_X = 0;		//metres
volatile double odo_Y = 0;		//metres
volatile double odo_angle = 0;	//radians

void odo_update()
{

	static int32_t old_dist_tick = 0;

	int32_t dist_right=coderRight.count;
	int32_t dist_left=coderLeft.count;

	int32_t new_dist_tick=(dist_left+dist_right)/2;
	int32_t new_angle_tick=dist_right-dist_left;

	double delta_dist=((double)(new_dist_tick-old_dist_tick))/ticksByMeters;

	odo_angle = new_angle_tick/tickbyRads;

	double dX = cos(odo_angle) * delta_dist;
	double dY = sin(odo_angle) * delta_dist;

	odo_X += dX;
	odo_Y += dY;

	old_dist_tick=new_dist_tick;
}