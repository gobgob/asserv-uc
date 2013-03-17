#ifndef FEEDBACKPROVIDER_H
#define FEEDBACKPROVIDER_H

#include <Arduino.h> 

#define FP_MAXVALUE (1024)
#define FP_MINVALUE (-FP_MAXVALUE)

class FeedbackProvider {
public:
	/*
	* return value between -1024 and 1024
	*/
	virtual int read();
};

#endif