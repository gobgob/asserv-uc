#ifndef ASSERV_H
#define ASSERV_H

#include <Arduino.h> 

void asserv_setup();
void asserv_run();

//activate or deactivate the asserve loop
//be carefull, this does NOT stop the robot if it is moving
void asserv_enable();
void asserv_disable();

void asserv_setSpeedMax(uint32_t speedMax); //ticks/iterations
void asserv_setAccMax(uint32_t accMax); //ticks/(iterations²)
void asserv_setTarget(int32_t newDist,int32_t newAngle);


//do not write these directly
//available here fore debug purpose only
extern volatile int32_t target_dist;
extern volatile int32_t target_angle;
extern volatile int32_t speed_right;
extern volatile int32_t speed_left;
extern volatile int32_t lastdist_right;
extern volatile int32_t lastdist_left;
extern volatile int32_t dist;
extern volatile int32_t angle;
extern volatile int32_t speed_dist;
extern volatile int32_t speed_angle;
extern volatile int32_t Kp_dist;
extern volatile int32_t Kp_angle;
extern volatile int32_t Kd_dist;
extern volatile int32_t Kd_angle;
extern volatile int32_t err_dist;
extern volatile int32_t err_angle;
extern volatile int32_t cmd_dist;
extern volatile int32_t cmd_angle;
extern volatile int32_t cmd_right;
extern volatile int32_t cmd_left;
extern volatile int32_t dist_right;
extern volatile int32_t dist_left;


#endif