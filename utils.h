#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define INT_MAX = (32767)
#define INT_MIN = (-32768)
//#define PI (3.14159265359)

#define cbi(x,y)	x&= ~(1<<y) //cbi(x,y)
#define sbi(x,y)	x|= (1<<y)//sbi(x,y)

#define pythagore(x,y)	sqrt((x)*(x)+(y)*(y))

int32_t maximizeDiff(int32_t oldValue, int32_t newValue, int32_t diffMax);
int32_t maximize(int32_t value, int32_t diffMax);

double principal_angle(double angle);
double closest_equivalent_angle(double old_angle,double new_angle);

#endif