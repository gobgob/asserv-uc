#ifndef ODO_H
#define ODO_H

#include <Arduino.h> 

extern volatile double odo_X;
extern volatile double odo_Y;
extern volatile double odo_angle;



void odo_update();

#endif