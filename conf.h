#ifndef CODER_H
#define CODER_H

/*coder's pins*/
#define CODER1A    (1 << PORTC0)
#define CODER1B    (1 << PORTC1)
#define CODER2A    (1 << PORTC3)
#define CODER2B    (1 << PORTC2)
#define CODERPINS (CODER1A | CODER1B | CODER2A | CODER2B)

#define DEBUG_PIN 9

#define MOTORL_PWM	5
#define MOTORL_DIR	4

#define MOTORR_PWM	6
#define MOTORR_DIR	8


/*pid setup*/
#define PID_FREQ 500
#define PWM_MAX 250

#define TICK2MM

#endif