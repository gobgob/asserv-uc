#ifndef ASSERV_H
#define ASSERV_H

#include <Arduino.h> 

void asserv_setup();
void asserv_run();

//activate or deactivate the asserve loop
//be carefull, this does NOT stop the robot if it is moving
void asserv_enable();
void asserv_disable();

void asserv_setSpeedMaxDist(uint32_t new_speed_max); //ticks/iterations
void asserv_setSpeedMaxAngle(uint32_t new_speed_max_angle);
void asserv_setAccMaxDist(uint32_t new_acc_max);//ticks/(iterations²)
void asserv_setTarget(int32_t newDist,int32_t newAngle);

void asserv_setCoeffDist(int32_t new_Kp_dist,int32_t new_Kd_dist);
void asserv_setCoeffAngle(int32_t new_Kp_angle,int32_t new_Kd_angle);

//asup
extern volatile int32_t mxcd;
extern volatile int32_t mxca;
// extern volatile float y;
// extern volatile float X;
// extern volatile float Y;

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