#ifndef CODER_H
#define CODER_H

/*coder's pins*/
#define CODER_L_A    (3)
#define CODER_L_B    (4)
#define CODER_R_A    (6)
#define CODER_R_B    (5)

#define DEBUG_PIN_CODEUSE 14
#define DEBUG_PIN_GENERAL 13

#define MOTOR_L_PWM		10
#define MOTOR_L_DIR		11
#define MOTOR_L_BRAKE	12
#define MOTOR_L_SENSE	A1

#define MOTOR_R_PWM		9
#define MOTOR_R_DIR		7
#define MOTOR_R_BRAKE	8
#define MOTOR_R_SENSE	A0

#define DEFAULT_TICK_PER_METERS (27793)
#define DEFAULT_TICK_PER_RADS (4125)

//refresh frequency of the PID and odometry, in Hz
#define REFRESH_FREQ 1000

//Absolute pwm that must not be exceded to avoid damaging the motors
#define PWM_MAX 200

//frequency off the pwm (the noise generated by the pwm become almost inaudible above 16khz)
#define PWM_FREQ 16000

//If the target pwm is < ZONE_51 it will be considered equal to 0
//Avoid useless "biiiiiiiiiii" from the motors when to pwm is to low to make it move
#define ZONE_51	0
#define BLOCK_CMD_DETECT_MIN	((int32_t)(50))
#define BLOCK_DURATION_MIN	((int32_t)(500)) //ms
#define BLOCK_DURATION_LOOP_COUNT ((int32_t)((BLOCK_DURATION_MIN*REFRESH_FREQ)/1000))


#define ACK_DIST	0.02 //en m
#define ACK_ANGLE	0.02 //en rad

#define DIST_WHEEL2CENTER (0.055)

#define I2C_ADDR	0x42

#define ULTRASOUND_PIN 14

#define SERVO_MAX 12

#endif
