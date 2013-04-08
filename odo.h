#ifndef ODO_H
#define ODO_H

#include <Arduino.h> 

extern volatile double odo_X;
extern volatile double odo_Y;
extern volatile double odo_angle;


void odo_enable();
void odo_disable();

int32_t odo_meters2ticks(double meters);
int32_t odo_rads2ticks(double rads);

void odo_setTickRatio(double new_ticks_per_meters,double new_ticks_per_rads);

void odo_update();

#endif