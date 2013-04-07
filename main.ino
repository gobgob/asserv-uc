
#include "utils.h"
#include "conf.h"
#include "asserv.h"
#include "odo.h"
#include "coders.h"


void setup()
{
	/*pin setup*/
	pinMode(13,OUTPUT);
	noInterrupts();
	coders_setup();
	asserv_setup();
	interrupts();
	Serial.begin(115200);

	asserv_setCoeffDist(2*1024,5000*1024);
	asserv_setCoeffAngle(1*1024/2,10000*1024);
	asserv_setSpeedMaxDist(90000);
	asserv_setSpeedMaxAngle(90000);
	asserv_setAbsTarget(0,0);

	odo_setTickRatio(1100,263.56058576);
	odo_enable();
	asserv_enable();

}

ISR(TIMER1_COMPA_vect) //asserv
{
	digitalWrite(DEBUG_PIN_ASSERV,HIGH);
	asserv_run();
	odo_update();
	digitalWrite(DEBUG_PIN_ASSERV,LOW);
}

ISR (PCINT1_vect)//coders
{
	coders_tick();
}


void loop()
{
	delay(100);
	Serial.println("");
	Serial.println("");

	Serial.print("coderLeft.count=");
	Serial.println(coderLeft.count);
	Serial.print("coderRight.count=");
	Serial.println(coderRight.count);

	Serial.print("odo_X=");
	Serial.println(odo_X);
	Serial.print("odo_Y=");
	Serial.println(odo_Y);
	Serial.print("odo_angle=");
	Serial.println(odo_angle);
	// Serial.print("debug=");
	// Serial.println(debug);

	if(abs(err_angle)<30 && abs(err_dist)<50)
	{
		asserv_setRelTarget(210,60);
	}

	digitalWrite(13,!digitalRead(13));
}
