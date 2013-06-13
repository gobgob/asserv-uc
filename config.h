#ifndef CODER_H
#define CODER_H

/*coder's pins*/
#define CODER_L_A    (2)
#define CODER_L_B    (3)
#define CODER_R_A    (4)
#define CODER_R_B    (5)

#define DEBUG_PIN_ASSERV 2
#define DEBUG_PIN_GENERAL 12

#define MOTOR_L_PWM		5
#define MOTOR_L_DIR		4
#define MOTOR_L_BRAKE	8
#define MOTOR_L_SENSE	A4

#define MOTOR_R_PWM		6
#define MOTOR_R_DIR		7
#define MOTOR_R_BRAKE	9
#define MOTOR_R_SENSE	A5

#define DEFAULT_TICK_PER_METERS (1420.06472492)
#define DEFAULT_TICK_PER_RADS (269.735797552)

//refresh frequency of the PID and odometry, in Hz
#define REFRESH_FREQ 1000

//Absolute pwm that must not be exceded to avoid damaging the motors
#define PWM_MAX 220

//If the target pwm is < ZONE_51 it will be considered equal to 0
//Avoid useless "biiiiiiiiiii" from the moteur when to pwm is to low to make it move
#define ZONE_51	6

#endif
