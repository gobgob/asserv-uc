#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>
#include <stdarg.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define INT_MAX = (32767)
#define INT_MIN = (-32768)

#define pythagore(x,y)	sqrt((x)*(x)+(y)*(y))

void myPrintf(char *fmt, ... );
int32_t maximizeDiff(int32_t oldValue, int32_t newValue, int32_t diffMax);
int32_t maximize(int32_t value, int32_t diffMax);
double principal_angle(double angle);
double closest_equivalent_angle(double old_angle,double new_angle);

#define DUMP_VAR(x)		\
{						\
	Serial.print(#x);	\
	Serial.print(" : ");\
	Serial.println(x);	\
}

#define DEBUG_PIN_ON digitalWrite(DEBUG_PIN_GENERAL,HIGH)
#define DEBUG_PIN_OFF digitalWrite(DEBUG_PIN_GENERAL,LOW)

#endif