#ifndef CODER_H
#define CODER_H

/*coder's pins*/
#define CODER_L_A    (2)
#define CODER_L_B    (3)
#define CODER_R_A    (7)
#define CODER_R_B    (6)

#define DEBUG_PIN_ASSERV 12
#define DEBUG_PIN_GENERAL 13

#define MOTOR_L_PWM		23
#define MOTOR_L_DIR		21
#define MOTOR_L_BRAKE	17
#define MOTOR_L_SENSE	A1

#define MOTOR_R_PWM		22
#define MOTOR_R_DIR		20
#define MOTOR_R_BRAKE	16
#define MOTOR_R_SENSE	A0

#define DEFAULT_TICK_PER_METERS (17442.0)
#define DEFAULT_TICK_PER_RADS (4918.8)

//refresh frequency of the PID and odometry, in Hz
#define REFRESH_FREQ 1000

//Absolute pwm that must not be exceded to avoid damaging the motors
#define PWM_MAX 220

//If the target pwm is < ZONE_51 it will be considered equal to 0
//Avoid useless "biiiiiiiiiii" from the moteur when to pwm is to low to make it move
#define ZONE_51	6

#endif
