#include "navigation.h"	
#include "utils.h"
#include "config.h"
#include "asserv.h"
#include "odometry.h"
// #include "coders.h"

static int isIn8Zone(double x1, double y1, double x2, double y2,double angle)
{
	angle=angle+PI/2;
	double cos_angle = DIST_WHEEL2CENTER*cos(angle);
	double sin_angle = DIST_WHEEL2CENTER*sin(angle);
	double right_wheel_x = x1+cos_angle;
	double right_wheel_y = y1+sin_angle;
	double left_wheel_x = x1-cos_angle;
	double left_wheel_y = y1-sin_angle;

	if (pythagore(right_wheel_x-x2,right_wheel_y-y2)<DIST_WHEEL2CENTER)
		return 1;

	if (pythagore(left_wheel_x-x2,left_wheel_y-y2)<DIST_WHEEL2CENTER)
		return 1;

	return 0;
}

int nav_gotoPoint(double new_x, double new_y, double delta_max)
{
	double old_x=odo_X;
	double old_y=odo_Y;
	double old_angle=odo_angle;
	double diff_x = new_x-old_x;
	double diff_y = new_y-old_y;

	double approx_dist = pythagore(diff_x,diff_y);

	// Serial.print("approx_dist=");
	// Serial.println(approx_dist);

	double n_angle_rad = atan2(diff_y,diff_x);
	n_angle_rad=closest_equivalent_angle(old_angle,n_angle_rad);
	double diff = n_angle_rad-odo_angle;
	// Serial.println("--");
	// Serial.print(approx_dist,3);
	// Serial.print(" ");
	// Serial.println(delta_max,3);
	if(approx_dist>=delta_max)
	{
		if(isIn8Zone(old_x,old_y,new_x,new_y,old_angle))
		{
			// Serial.println("ZONE 8 ============================");
			asserv_setTarget(
				0,
				odo_rads2ticks(n_angle_rad),
				DEST_REL|ANGL_ABS);
			approx_dist=0;
		}

		asserv_setTarget(
			odo_meters2ticks(approx_dist),
			odo_rads2ticks(diff),
			DEST_REL|ANGL_REL);

		return 0;		
	}else{
		
		return 1;
	}

}
