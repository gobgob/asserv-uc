#ifndef API_H
#define API_H

#include <Arduino.h> 

extern bool (*cmd_callback)();

//rel_dist in mm
void cmd_goForwardOrBackward(uint16_t rel_dist,int8_t sign);
void cmd_rotate(int16_t rel_angle);
void cmd_goto(int16_t new_x, int16_t new_y, int16_t delta_max);

void cmd_getOdo(uint8_t * data);
void cmd_getStatus(uint8_t * data);
void cmd_reboot();


#endif