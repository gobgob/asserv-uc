#include "utils.h"

void myPrintf(char *fmt, ... ){
        char tmp[128]; // resulting string limited to 128 chars
        va_list args;
        va_start (args, fmt );
        vsnprintf(tmp, 128, fmt, args);
        va_end (args);
        Serial.print(tmp);
}

int32_t maximizeDiff(int32_t oldValue, int32_t newValue, int32_t diffMax)
{

	if(diffMax==-1)
		return newValue;

	int32_t diff = oldValue-newValue;
	if(abs(diff)>diffMax)
	{
		if(diff>0)
			return	oldValue-diffMax;
		else
			return	oldValue+diffMax;
	}
	return newValue;
}

int32_t maximize(int32_t value, int32_t max)
{
	if(max==-1)
		return value;

	if(abs(value)>max)
	{
		if(value>0)
			return	max;
		else
			return	-max;
	}
	return value;
}

double principal_angle(double angle)
{
	if (angle>=0)
	{
		while(angle>PI)
		{
			angle=angle-(2.*PI);
		}
		return angle;
	}else{
		return -principal_angle(-angle);
	}

}

double closest_equivalent_angle(double old_angle,double new_angle)
{
	// DUMP_VAR(old_angle);
	// DUMP_VAR(new_angle);
	// DUMP_VAR(PI);
	if(new_angle<=old_angle)
	{
		while(!(old_angle-PI<=new_angle && new_angle<old_angle+PI))
		{
			new_angle+=2*PI;
		}
		return new_angle;
	}
	else
	{
		while(!(old_angle-PI<=new_angle && new_angle<old_angle+PI))
		{
			new_angle-=2*PI;
		}
		return new_angle;
	}
}