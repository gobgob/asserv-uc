#ifndef CODER_H
#define CODER_H

/*coder's pins*/
#define CODER1A    (1 << PORTC0)
#define CODER1B    (1 << PORTC1)
#define CODER2A    (1 << PORTC2)
#define CODER2B    (1 << PORTC3)
#define CODERPINS (CODER1A | CODER1B | CODER2A | CODER2B)

/*pid setup*/
#define PID_FREQ 300
#define PWM_MAX 250

#endif