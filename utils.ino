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