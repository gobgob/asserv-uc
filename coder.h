#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <Arduino.h> 
#include "feedbackProvider.h"

class Coder : public FeedbackProvider {
private:
public:
	Coder();
	volatile int32_t count; //public is not the best, be i want to keep it simple in the interrupt
	virtual int read();
};

#endif