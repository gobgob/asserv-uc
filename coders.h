#ifndef CODERS_H
#define CODERS_H

#include <Arduino.h> 

typedef struct {
	volatile int32_t count;
} coder_t;

extern coder_t coderLeft;
extern coder_t coderRight;

void coders_setup();
void coders_tick();

#endif