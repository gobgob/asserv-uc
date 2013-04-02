#include "hbridge.h"
#include "utils.h"

HBridge::HBridge(int pwmPin, int dirPin, int brakePin):
pwmPin(pwmPin),
dirPin(dirPin),
brakePin(brakePin),
pwmRegister(pwmRegister)
{
}

void HBridge::setup()
{
	pinMode(pwmPin, OUTPUT);
	pinMode(dirPin, OUTPUT);
	pinMode(brakePin, OUTPUT);
}



void HBridge::setSpeed(int speed)
{
	int pwm;
	int direction;

	speed=MIN(HB_VMAX,MAX(HB_VMIN,speed));

	if (speed>0)
	{
		direction=0;
		pwm=speed;
	}else{
		direction=1;
		pwm=-speed;
	}

	analogWrite(pwmPin,pwm);
	digitalWrite(dirPin,direction);
}

int HBridge::getSpeed()
{
	return speed;
}

void HBridge::brakeOn()
{
	analogWrite(pwmPin,255);
	speed = 0;
	digitalWrite(brakePin,HIGH);
}

void HBridge::brakeOff()
{
	setSpeed(0);
	digitalWrite(brakePin,LOW);
}