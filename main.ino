
#include "utils.h"
#include "conf.h"
#include "asserv.h"
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

	asserv_enable();

	target_dist=0;
	target_angle=0;
}

ISR(TIMER1_COMPA_vect) //asserv
{
	digitalWrite(DEBUG_PIN_ASSERV,HIGH);
	asserv_run();
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


	// Serial.print("mxcd=");
	// Serial.println(mxcd);
	// Serial.print("mxca=");
	// Serial.println(mxca);

	// Serial.print("coderLeft.count=");
	// Serial.println(coderLeft.count);
	// Serial.print("coderRight.count=");
	// Serial.println(coderRight.count);

	// Serial.print("dist_right=");
	// Serial.println(dist_right);
	// Serial.print("dist_left=");
	// Serial.println(dist_left);

	// Serial.print("dist=");
	// Serial.println(dist);
	// Serial.print("angle=");
	// Serial.println(angle);

	// Serial.print("err_dist=");
	// Serial.println(err_dist);
	// Serial.print("err_angle=");
	// Serial.println(err_angle);

	// Serial.print("cmd_dist=");
	// Serial.println(cmd_dist);
	// Serial.print("cmd_angle=");
	// Serial.println(cmd_angle);

	// Serial.print("speed_dist=");
	// Serial.println(speed_dist);
	// Serial.print("speed_angle=");
	// Serial.println(speed_angle);

	// Serial.print("cmd_right=");
	// Serial.println(cmd_right/1024);
	// Serial.print("cmd_left=");
	// Serial.println(cmd_left/1024);

	// Serial.println(millis());

	// Serial.print("X=");
	// Serial.println(X);
	// Serial.print("Y=");
	// Serial.println(Y);

	if(abs(err_angle)<30 && abs(err_dist)<50)
	{
		target_dist+=210;
		target_angle+=60;
	}

	digitalWrite(13,!digitalRead(13));
}
