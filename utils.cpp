#include "utils.h"

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