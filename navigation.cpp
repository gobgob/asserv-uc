#include "navigation.h"
#include "utils.h"
#include "conf.h"
#include "asserv.h"
#include "odo.h"
#include "coders.h"

int nav_gotoPoint(double new_x, double new_y, double delta_max)
{
	double old_x=odo_X;
	double old_y=odo_Y;
	double diff_x = new_x-old_x;
	double diff_y = new_y-old_y;

	double approx_dist = pythagore(diff_x,diff_y);

	if(approx_dist>=delta_max)
	{
		double new_angle = atan2(diff_y,diff_x);
		new_angle=closest_equivalent_angle(odo_angle,new_angle);
		asserv_setTarget(
			odo_meters2ticks(approx_dist),
			odo_rads2ticks(new_angle),
			DEST_REL|ANGL_ABS);
		
		return -1;		
	}else{
		return 0;
	}

}
