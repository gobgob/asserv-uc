#ifndef HBRIDGE_H
#define HBRIDGE_H

#include <Arduino.h> 
#include "conf.h"

#define HB_VMAX (+PWM_MAX)
#define HB_VMIN (-HB_VMAX)

class HBridge {
private:
	int32_t speed;
	int pwmPin;
	int dirPin;
	int brakePin;
	volatile uint8_t * pwmRegister;

public:
	HBridge(int pwmPin, int dirPin, int brakePin);

	void setup();
	/*
	*Set the motor speed value between -255 and 255
	*/
	void setSpeed(int speed);
	int getSpeed();

	void brakeOn();
	void brakeOff();

};

#endif