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


#define	DEST_ABS	(1<<0)
#define	DEST_REL	(1<<1)
#define	ANGL_ABS	(1<<2)
#define	ANGL_REL	(1<<3)
#define ABS 		(DEST_ABS|ANGL_ABS)
#define REL 		(DEST_REL|ANGL_REL)
void asserv_setTarget(int32_t new_dist,int32_t new_angle,uint8_t flags);


void asserv_setCoeffDist(uint32_t new_Kp_dist,uint32_t new_Kd_dist);
void asserv_setCoeffAngle(uint32_t new_Kp_angle, uint32_t new_Kd_angle);
void asserv_getCoeffDist(uint32_t * Kp,uint32_t * Kd);
void asserv_getCoeffAngle(uint32_t * Kp, uint32_t * Kd);


extern volatile int32_t err_dist;
extern volatile int32_t err_angle;

extern volatile int32_t dist;
extern volatile int32_t angle;

//blockages front/back right/left
#define	BLOCK_FR	(1<<0)
#define	BLOCK_FL	(1<<1)
#define	BLOCK_BR	(1<<2)
#define	BLOCK_BL	(1<<3)
#define	CMD_HACK	(1<<4)

extern	volatile uint8_t block_flags;


#endif