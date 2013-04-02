
#include "utils.h"

#include "hbridge.h"
#include "feedbackProvider.h"
#include "pidController.h"

#include "coder.h"
#include "conf.h"



Coder coderLeft;
Coder coderRight;

HBridge motorLeft(MOTORL_PWM,MOTORL_DIR,0);
HBridge motorRight(MOTORR_PWM,MOTORR_DIR,0);


void setup()
{

	/*pin setup*/
	pinMode(A0,INPUT);
	pinMode(A1,INPUT);
	pinMode(A2,INPUT);
	pinMode(A3,INPUT);
	pinMode(DEBUG_PIN,OUTPUT);
	pinMode(13,OUTPUT);

	Serial.begin(115200);

	motorRight.setup();
	motorLeft.setup();

	noInterrupts();
	/*coders setup*/
	PCMSK1 |= (1 << PCINT11) | (1 << PCINT10) |(1 << PCINT9) | (1 << PCINT8); //A0,A1,A2,A3
    PCICR |= (1 << PCIE1); // Activer les interruptionssur le port c (analogs sur arduino)
    /*timer setup*/
    TCCR1A = 0;
    TCCR1B = 0;
    OCR1A=16000000/PID_FREQ;
	TCNT1=0;
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << CS10);// Set 1 prescaler = 1
	TIMSK1 = (1 << OCIE1A);//enable interrupt sur comparaison réussie
    interrupts();

}

volatile int32_t target_dist=0;
volatile int32_t target_angle=0;

volatile int32_t speed_right=0;
volatile int32_t speed_left=0;

volatile int32_t lastdist_right=0;
volatile int32_t lastdist_left=0;

volatile int32_t dist=0;
volatile int32_t angle=0;

volatile int32_t speed_dist=0;
volatile int32_t speed_angle=0;

volatile int32_t Kp_dist=5*1024;
volatile int32_t Kp_angle=5*1024;

volatile int32_t Kd_dist=0;
volatile int32_t Kd_angle=0;

volatile int32_t err_dist=0;
volatile int32_t err_angle=0;

volatile int32_t cmd_dist=0;
volatile int32_t cmd_angle=0;

volatile int32_t cmd_right=0;
volatile int32_t cmd_left=0;

volatile int32_t dist_right=0;
volatile int32_t dist_left=0;

ISR(TIMER1_COMPA_vect) //asserv
{
	digitalWrite(9,HIGH);


	dist_right=coderRight.count;
	dist_left=coderLeft.count;

	dist=(dist_left+dist_right)/2;
	angle=dist_right-dist_left;

	speed_right=(dist_right-lastdist_right);
	speed_left=(dist_left-lastdist_left);

	speed_dist=(speed_right+speed_left)/2;
	speed_angle=speed_right-speed_left;

	err_dist = target_dist-dist;
	err_angle = target_angle-angle;

	cmd_dist=err_dist*Kp_dist;//-Kd_dist*speed_dist;
	cmd_angle=err_angle*Kp_angle;//-Kd_angle*speed_angle;

	cmd_right=cmd_dist+cmd_angle;
	cmd_left=cmd_dist-cmd_angle;

	motorRight.setSpeed(cmd_right/1024);
	motorLeft.setSpeed(cmd_left/1024);

	digitalWrite(9,LOW);
}

ISR (PCINT1_vect)//coders
{
	static int8_t codersLastState=0;
	int8_t changedPins=codersLastState^(PINC);

	if(changedPins & CODER1A) //change of the pin 1A
	{
		if(PINC & CODER1A)//rising edge
			(PINC & CODER1B)?coderLeft.count++:coderLeft.count--;
		else//falling edge
			(PINC & CODER1B)?coderLeft.count--:coderLeft.count++;
	}
	else if(changedPins & CODER1B) //change of the pin 1B
	{
		if(PINC & CODER1B)//rising edge
			(PINC & CODER1A)?coderLeft.count--:coderLeft.count++;
		else//falling edge
			(PINC & CODER1A)?coderLeft.count++:coderLeft.count--;
	}


	if(changedPins & CODER2A) //change of the pin 2A
	{
		if(PINC & CODER2A)//rising edge
			(PINC & CODER2B)?coderRight.count++:coderRight.count--;
		else//falling edge
			(PINC & CODER2B)?coderRight.count--:coderRight.count++;
	}
	else if(changedPins & CODER2B) //change of the pin 2B
	{
		if(PINC & CODER2B)//rising edge
			(PINC & CODER2A)?coderRight.count--:coderRight.count++;
		else//falling edge
			(PINC & CODER2A)?coderRight.count++:coderRight.count--;
	}

	codersLastState=PINC & CODERPINS;
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
