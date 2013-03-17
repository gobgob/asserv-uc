
#include "utils.h"

#include "hbridge.h"
#include "feedbackProvider.h"
#include "pidController.h"

#include "coder.h"
#include "conf.h"



Coder coderLeft;
Coder coderRight;

HBridge motorLeft(11,12,13);
HBridge motorRight(11,12,13);

PidController pidLeft(&motorLeft,&coderLeft);
PidController pidRight(&motorRight,&coderRight);

void setup()
{

	/*pin setup*/
	pinMode(A0,INPUT);
	pinMode(A1,INPUT);
	pinMode(A2,INPUT);
	pinMode(A3,INPUT);
	pinMode(8,OUTPUT);

	Serial.begin(115200);

	noInterrupts();  

	/*coders setup*/
	PCMSK1 |= (1 << PCINT11) | (1 << PCINT10) |(1 << PCINT9) | (1 << PCINT8); //A0,A1,A2,A3
    PCICR |= (1 << PCIE1); // Activer les interruptionssur le port c (analogs sur arduino)

    /*timer setup*/
	OCR1A=16000000/PID_FREQ; //set timer limit
	TCNT1=0;
	TCCR1B = (1 << WGM12);
	TCCR1B = (1 << CS10);// Set 1 prescaler = 1
	TIMSK1 = (1 << OCIE1A);//enable interrupt sur comparaison réussie


    interrupts();
}

ISR(TIMER1_COMPA_vect) 
{ 
	digitalWrite(8,HIGH);
	pidLeft.compute();
	pidRight.compute();
	digitalWrite(8,LOW);
}

ISR (PCINT1_vect)
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
			(PINC & CODER2B)?coderLeft.count++:coderLeft.count--;	
		else//falling edge
			(PINC & CODER2B)?coderLeft.count--:coderLeft.count++;			
	}
	else if(changedPins & CODER2B) //change of the pin 2B
	{
		if(PINC & CODER1B)//rising edge
			(PINC & CODER2A)?coderLeft.count--:coderLeft.count++;	
		else//falling edge
			(PINC & CODER2A)?coderLeft.count++:coderLeft.count--;
	}

	codersLastState=PINC & CODERPINS;
}

void loop(){
	delay(100);
	Serial.println(coderLeft.read());
}
