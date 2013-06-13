#ifndef HBRIDGE_H
#define HBRIDGE_H

#include <Arduino.h> 
#include "config.h"

#define HB_VMAX (+PWM_MAX)
#define HB_VMIN (-HB_VMAX)

class HBridge {
private:
	int32_t speed;
	uint8_t pwmPin;
	uint8_t dirPin;
	uint8_t brakePin;

public:
	HBridge(uint8_t pwmPin, uint8_t dirPin, uint8_t brakePin);

	void setup();
	/*
	*Set the motor speed value between -255 and 255
	*/
	void setSpeed(int32_t newSpeed);
	int getSpeed();

	void brakeOn();
	void brakeOff();

};

#endif
