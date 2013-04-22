#ifndef API_H
#define API_H

#include <Arduino.h> 

extern bool (*cmd_callback)();

//rel_dist in mm
void cmd_goForwardOrBackward(uint16_t rel_dist,int8_t sign);
void cmd_rotate(int16_t angle);



#endif