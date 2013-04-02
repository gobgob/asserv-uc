#include "utils.h"
#include "conf.h"

#include "coders.h"

coder_t coderLeft;
coder_t coderRight;

void coders_setup()
{
	pinMode(CODER1A_PIN,INPUT);
	pinMode(CODER1B_PIN,INPUT);
	pinMode(CODER2A_PIN,INPUT);
	pinMode(CODER2B_PIN,INPUT);
	PCMSK1 |= (1 << CODER1A_INT) | (1 << CODER1B_INT) |(1 << CODER2A_INT) | (1 << CODER2B_INT);
	PCICR |= (1 << PCIE1); // Activer les interruptionssur le port c (analogs sur arduino)

}

void coders_tick()
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