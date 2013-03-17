#ifndef HBRIDGE_H
#define HBRIDGE_H

#include <Arduino.h> 

#define HB_VMAX (+254)
#define HB_VMIN (-HB_VMAX)

class HBridge {
private:
	int speed;
	int pwmPin;
	int dirPin;
	int brakePin;

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

	int getMaxOutput();
	int getMinOutput();


};

#endif