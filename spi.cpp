#include "api.h"
#include "spi.h"
#include "spi_buffer.h"
#include "spi_frame.h"


void spi_setup()
{
	// Init Cirlce buffer
	circle_buffer_init(&buffer_write);
	circle_buffer_init(&buffer_read);

	// Set pin Mode
	DDRB &= ~( 1 << PIN5 );    // CLK input
	DDRB |= ( 1 << PIN4 );     // MISO output
	DDRB &= ~( 1 << PIN3 );     // MOSI input
	DDRB &= ~( 1 << PIN2 );    // SS input

	//Set Pull-up
	PORTB |= ( 1 << PIN5 ) | ( 1 << PIN3 ) | ( 1 << PIN2 );

	// Set Clock rate
	SPCR &= ~( 1 << SPR1);
	SPCR &= ~( 1 << SPR0 );
	SPSR |= ( 1 << SPI2X );

	SPCR &= ~( 1 << MSTR );  // Put slave mode
	SPCR |= ( 1 << SPIE);    // Enable SPI Interrupt
	SPCR |= ( 1 << SPE );    // Enable SPI
}

void spi_interrupt()
{
	circle_buffer_write(&buffer_read,SPDR);
	if( circle_buffer_available(&buffer_write) != 0 )
	{
		unsigned char spdr;
		circle_buffer_read(&buffer_write, &spdr);
		SPDR = spdr;
	}
	else
		SPDR = 0x00;
}



// Define Type of function
#define ACK 0
#define NAK 1
#define SETTER 2
#define GETTER 3
#define ARGS_FUNCTION 4
#define NOARGS_FUNCTION 5
#define PING 6
#define START 7
#define STOP 8

// Define Getter / Setter
#define MAX_SPEED_ROT 0
#define MAX_SPEED_LIN 1
#define KPKD_ROT 2
#define KPKD_LIN 3
#define TICK_RATIO 4

// Define Args Functions
#define GOFORWARD 0
#define GOBACK 1
#define ROTATE 2
#define GOTO 3

#define MAKEUINT16T(x,y) (uint16_t)((x<<8)|y)

void spi_process()
{
	static unsigned long old = 0;
	int result;
	if( (result = frameReceive()) == 0 && frameVerifChecksum() == 0)
	{
		uint8_t type;
		uint8_t size;
		uint8_t data[15];
		frameGetType(&type);
		frameGetSize(&size);
		frameGetData(data);

		switch (type)
		{
			case ARGS_FUNCTION:
				switch(data[0])
				{
					case GOFORWARD:
						cmd_goForwardOrBackward(MAKEUINT16T(data[1],data[2]),1);
						break;
					case GOBACK:
						cmd_goForwardOrBackward(-MAKEUINT16T(data[1],data[2]),-1);
						break;
					case ROTATE:
						cmd_rotate(-MAKEUINT16T(data[1],data[2]));
						break;
					default:
					;
				}
				break;
			default:
			;
		}



		frameSetSize(0);
		frameSetType(ACK);
		for(int i=0;i<15;i++)
			data[i] = i*i;
		frameSetData(data);
		frameComputeChecksum();
		if( frameSend() != 0 )
			Serial.println("Error while putting data in send buffer");
	}
	if( millis() - old > 1000 )
	{
		Serial.println(millis());
		old = millis();
	}
}

