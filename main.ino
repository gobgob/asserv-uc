
#include "utils.h"
#include "conf.h"
#include "asserv.h"
#include "odo.h"
#include "coders.h"
#include "navigation.h"
#include "api.h"
#include "spi.h"



void setup()
{
	/*pin setup*/
	pinMode(DEBUG_PIN_GENERAL,OUTPUT);
	noInterrupts();
	coders_setup();
	asserv_setup();
	spi_setup();
	interrupts();
	Serial.begin(115200);

	asserv_setCoeffDist(1*1024,5*1024);
	asserv_setCoeffAngle(2*1024/2,100*1024);
	asserv_setSpeedMaxDist(90000);
	asserv_setSpeedMaxAngle(90000);
	asserv_setTarget(0,0,ABS);

	odo_setTickRatio(1420.06472492,265.868332435);
	odo_enable();
	asserv_enable();


	//cmd_goForward(200);

}


ISR(TIMER1_COMPA_vect, ISR_NOBLOCK) //asserv
{
	digitalWrite(DEBUG_PIN_ASSERV,HIGH);
	asserv_run();
	odo_update();
	digitalWrite(DEBUG_PIN_ASSERV,LOW);
}

ISR (PCINT1_vect)//coders
{
	digitalWrite(DEBUG_PIN_GENERAL,HIGH);
	coders_tick();
	digitalWrite(DEBUG_PIN_GENERAL,LOW);
}

ISR( SPI_STC_vect )
{
	digitalWrite(DEBUG_PIN_GENERAL,HIGH);
	spi_interrupt();
	digitalWrite(DEBUG_PIN_GENERAL,LOW);
}

int state = 1;
double A=0;
double B=0;
double R=0.40;
void loop()
{
	spi_process();
	//delay(100);
	// Serial.println("");


	if(cmd_callback)
	{
		int cb = cmd_callback();
		// Serial.print("cmd_callback=");
		// Serial.println(cb);
	}

static unsigned long old = 0;
	if( millis() - old > 300 )
	{
		Serial.println("");
		Serial.print("coderLeft.count=");
		Serial.println(coderLeft.count);
		Serial.print("coderRight.count=");
		Serial.println(coderRight.count);
		Serial.print("odo_X=");
		Serial.println(odo_X,4);
		Serial.print("odo_Y=");
		Serial.println(odo_Y,4);
		Serial.print("odo_angle=");
		Serial.println(odo_angle,4);
		Serial.print("block_flags=");
		Serial.println(block_flags);
		old = millis();
	}

	// Serial.print("dist=");
	// Serial.println((coderRight.count+coderLeft.count)/2);
	// Serial.print("angle=");
	// Serial.println(coderRight.count-coderLeft.count);




	// Serial.print("odo_angle=");
	// Serial.println(odo_angle);
	// Serial.print("debug=");
	// Serial.print("new_angle=");
	// Serial.println(new_angle);


	//asserv_setTarget(0,0,DEST_ABS|ANGL_ABS);

	//if(millis()>2000)
	//{
	//nav_gotoPoint(0.25,0, 0.03);
		//nav_gotoPoint(-0.25,0.25, 0.03);
		//nav_gotoPoint(0.25,-0.25, 0.03);
		//nav_gotoPoint(-0.25,-0.25, 0.03);
		//nav_gotoPoint(0.25,0, 0.03);
		//nav_gotoPoint(0,0.25, 0.03);
		// switch (state)
		// {
		// 	case 0:
		// 		if(nav_gotoPoint(0,-0.25, 0.10)==0)
		// 		{
		// 			state++;
		// 		}
		// 		break;
		// 	case 1:
		// 		if(nav_gotoPoint(0,-0.50, 0.03)==0)
		// 		{
		// 			state++;
		// 		}
		// 		break;
		// 	case 3:
		// 		asserv_setTarget(0,0,REL);
		// 		break;
		// }


		// 	 A=R*sin((2.*3.14/400.)*state);
		// 	 B=R*cos((2.*3.14/400.)*state)-R;

		// 	 if(nav_gotoPoint(A, B, 0.03)==0)
		// 	 {
		// 	 	state++;
		// 	 }

		// double R=0.30;
		// A=2*R*sin((double)state/20.);
		// B=R*sin(2.*(double)state/20.);

	 // 	 if(nav_gotoPoint(A, B, 0.03)==0)
	 // 	 {
	 // 	 	state++;
	 // 	 }
	//}

	//digitalWrite(13,!digitalRead(13));
}
