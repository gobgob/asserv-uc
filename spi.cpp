#include "api.h"
#include "spi.h"
#include "spi_buffer.h"
#include "spi_frame.h"
#include "asserv.h"
#include "odo.h"


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

#include <stdarg.h>
void p(char *fmt, ... ){
        char tmp[128]; // resulting string limited to 128 chars
        va_list args;
        va_start (args, fmt );
        vsnprintf(tmp, 128, fmt, args);
        va_end (args);
        Serial.print(tmp);
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
						cmd_rotate(
							MAKEINT32T(data[1],data[2],data[3],data[4]),\
							data[5]
							);
						break;
					case GOTO:
						cmd_goto(
							MAKEINT32T(data[1],data[2],data[3],data[4]), \
							MAKEINT32T(data[5],data[6],data[7],data[8]), \
							MAKEINT32T(data[9],data[10],data[11],data[12]) \
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
					case KPKD_LIN:
						data[0]=KPKD_LIN;
						cmd_getKpKdLin(data+1);
						spi_sendData(GETTER,data,9);
						break;
					case KPKD_ROT:
						data[0]=KPKD_ROT;
						cmd_getKpKdRot(data+1);
						spi_sendData(GETTER,data,9);
						break;
					case ODO:
						data[0]=ODO;
						cmd_getOdo(data+1);
						spi_sendData(GETTER,data,13);
						break;
					case STATUS:
						data[0]=STATUS;
						cmd_getStatus(data+1);
						spi_sendData(GETTER,data,2);
						break;
					case TICKS:
						data[0]=TICKS;
						cmd_getTicks(data+1);
						spi_sendData(GETTER,data,9);
						break;
				}
				break;

			case SETTER:
				switch(data[0])
				{
					case KPKD_LIN:
						asserv_setCoeffDist(
							MAKEUINT32T(data[1],data[2],data[3],data[4]),
							MAKEUINT32T(data[5],data[6],data[7],data[8])
							);
						break;
					case KPKD_ROT:
						asserv_setCoeffAngle(
							MAKEUINT32T(data[1],data[2],data[3],data[4]),
							MAKEUINT32T(data[5],data[6],data[7],data[8])
							);
						break;
					case ODO:
						if(data[1]&SET_ODO_X)
							odo_setX(MAKEINT32T(data[2],data[3],data[4],data[5])/1000.);
						if(data[1]&SET_ODO_Y)
							odo_setY(MAKEINT32T(data[6],data[7],data[8],data[9])/1000.);
						if(data[1]&SET_ODO_ANGLE)
							odo_setAngle((double)MAKEINT32T(data[10],data[11],data[12],data[13])/10000);
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

