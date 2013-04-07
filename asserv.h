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

void asserv_setAbsTarget(int32_t new_dist,int32_t new_angle);
void asserv_setRelTarget(int32_t new_dist,int32_t new_angle);

void asserv_setCoeffDist(int32_t new_Kp_dist,int32_t new_Kd_dist);
void asserv_setCoeffAngle(int32_t new_Kp_angle,int32_t new_Kd_angle);

extern volatile int32_t err_dist;
extern volatile int32_t err_angle;


#endif