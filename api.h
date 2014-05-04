#ifndef API_H
#define API_H

#include <Arduino.h> 

extern bool (*cmd_callback)();

//rel_dist in mm

void cmd_goto(int32_t new_x, int32_t new_y, int32_t delta_max);

void cmd_getOdo(uint8_t * data);
void cmd_getStatus(uint8_t * data);
void cmd_reboot();

void cmd_getKpKdLin(uint8_t * data);
void cmd_getKpKdRot(uint8_t * data);

void cmd_getTicks(uint8_t * data);

#endif