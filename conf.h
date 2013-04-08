#ifndef CODER_H
#define CODER_H

/*coder's pins*/
#define CODER1A    (1 << PORTC0)
#define CODER1B    (1 << PORTC1)
#define CODER2A    (1 << PORTC3)
#define CODER2B    (1 << PORTC2)
#define CODERPINS (CODER1A | CODER1B | CODER2A | CODER2B)

/*coder's pins arduino format, probably not the right order but not inportant here*/
#define CODER1A_PIN    A0
#define CODER1B_PIN    A1
#define CODER2A_PIN    A2
#define CODER2B_PIN    A3

/*coder's pins interrupts mask format, probably not the right order but not inportant here*/
#define CODER1A_INT    PCINT11
#define CODER1B_INT    PCINT10
#define CODER2A_INT    PCINT9
#define CODER2B_INT    PCINT8

#define ZONE_51	20

#define DEBUG_PIN_ASSERV 9

#define MOTORL_PWM	5
#define MOTORL_DIR	4

#define MOTORR_PWM	6
#define MOTORR_DIR	8


/*pid setup*/
#define PID_FREQ 500
#define PWM_MAX 250

#define TICK2MM

#endif