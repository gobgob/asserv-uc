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


static void spi_sendAck()
{
	frameSetSize(0);
	frameSetType(ACK);
	frameComputeChecksum();
	if( frameSend() != 0 )
		Serial.println("Error while putting data in send buffer");
}

static void spi_sendData(int type, uint8_t * data,int size)
{
	frameSetSize(size);
	frameSetType(type);
	frameSetData(data);
	frameComputeChecksum();
	if( frameSend() != 0 )
		Serial.println("Error while putting data in send buffer");
}



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
						cmd_goForwardOrBackward(MAKEUINT16T(data[1],data[2]),-1);
						break;
					case ROTATE:
						cmd_rotate(MAKEINT16T(data[1],data[2]));
						break;
					case GOTO:
						cmd_goto(
							MAKEINT16T(data[1],data[2]), \
							MAKEINT16T(data[3],data[4]), \
							MAKEINT16T(data[5],data[6]) \
							);
						break;
					default:
					;
				}
				spi_sendAck();
				break;

			case GETTER:
				switch(data[0])
				{
					case ODO:
						data[0]=ODO;
						cmd_getOdo(data+1);
						spi_sendData(GETTER,data,13);
					break;
					case STATUS:
						data[0]=STATUS;
						//data[1]=0;
						cmd_getStatus(data+1);
						spi_sendData(GETTER,data,2);
					break;
					default:
					;
				}
				break;

			case REBOOT:
				spi_sendAck();
				cmd_reboot();	
				break;
			default:

			;
		}

	}
	// if( millis() - old > 1000 )
	// {
	// 	Serial.println(millis());
	// 	old = millis();
	// }
}

