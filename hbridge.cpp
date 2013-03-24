#include "hbridge.h"
#include "utils.h"

HBridge::HBridge(int pwmPin, int dirPin, int brakePin):
pwmPin(pwmPin),
dirPin(dirPin),
brakePin(brakePin)
{
    pinMode(pwmPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    pinMode(brakePin, OUTPUT);
}

void HBridge::setup()
{
	noInterrupts();           // disable all interrupts
	pinMode(3, OUTPUT);
	pinMode(11, OUTPUT);
	TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
	TCCR2B = _BV(CS20);
	OCR2A = 0;
	OCR2B = 0;
	interrupts();
}

void HBridge::setSpeed(int speed)
{
	int pwm;
	int direction;
		// Serial.print("speed1 : ");
		// Serial.println(speed);
	speed=speed;//map(speed,-1024,1024,-255,255);
		// Serial.print("speed2 : ");
		// Serial.println(speed);
	speed=MIN(HB_VMAX,MAX(HB_VMIN,speed));

		// Serial.print("speed3 : ");
		// Serial.println(speed);
	if (speed>0)
	{
		direction=0;
		pwm=speed;
	}else{
		direction=1;
		pwm=-speed;
	}

	OCR2A = OCR2B = pwm;
	digitalWrite(dirPin,direction);
}

int HBridge::getSpeed()
{
	return speed;
}

int HBridge::getMaxOutput(){return map(HB_VMAX,-255,255,-1024,1024);}
int HBridge::getMinOutput(){return map(HB_VMIN,-255,255,-1024,1024);}

void HBridge::brakeOn()
{
	OCR2A = OCR2B = 255; //put pwm pin high
	speed = 0;
	digitalWrite(brakePin,HIGH);
}

void HBridge::brakeOff()
{
	setSpeed(0);
	digitalWrite(brakePin,LOW);
}