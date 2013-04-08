#include "hbridge.h"
#include "utils.h"

HBridge::HBridge(uint8_t pwmPin, uint8_t dirPin, uint8_t brakePin):
pwmPin(pwmPin),
dirPin(dirPin),
brakePin(brakePin)
{
}

void HBridge::setup()
{
	pinMode(pwmPin, OUTPUT);
	pinMode(dirPin, OUTPUT);
	pinMode(brakePin, OUTPUT);
}

void HBridge::setSpeed(int32_t newSpeed)
{
	int pwm;
	int direction;

	speed=MIN(HB_VMAX,MAX(HB_VMIN,newSpeed));

	if(abs(speed)<ZONE_51)
		speed=0;

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