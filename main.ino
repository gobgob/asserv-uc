
#include "utils.h"
#include "conf.h"
#include "asserv.h"
#include "coders.h"


void setup()
{
	/*pin setup*/
	pinMode(13,OUTPUT);
	Serial.begin(115200);
	noInterrupts();
	coders_setup();
	asserv_setup();
    interrupts();

    void asserv_enable();
}

ISR(TIMER1_COMPA_vect) //asserv
{
	asserv_run();
}

ISR (PCINT1_vect)//coders
{
	coders_tick();
}


void loop(){
	delay(100);
	Serial.println("");
	Serial.println("");

	Serial.print("dist_right=");
	Serial.println(dist_right);
	Serial.print("dist_left=");
	Serial.println(dist_left);

	Serial.print("dist=");
	Serial.println(dist);
	Serial.print("angle=");
	Serial.println(angle);

	Serial.print("err_dist=");
	Serial.println(err_dist);
	Serial.print("err_angle=");
	Serial.println(err_angle);

	Serial.print("cmd_dist=");
	Serial.println(cmd_dist);
	Serial.print("cmd_angle=");
	Serial.println(cmd_angle);

	Serial.print("cmd_right=");
	Serial.println(cmd_right/1024);
	Serial.print("cmd_left=");
	Serial.println(cmd_left/1024);

 target_dist=-millis()/2;
	
// 	delay(500000);
	digitalWrite(13,!digitalRead(13));

}
