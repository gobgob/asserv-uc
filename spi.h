#ifndef SPI_H
#define SPI_H

#include <Arduino.h> 

void spi_interrupt();
void spi_process();
void spi_setup();


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
#define ODO 4

// Define Args Functions
#define GOFORWARD 0
#define GOBACK 1
#define ROTATE 2
#define GOTO 3

#define MAKEUINT16T(x,y) (uint16_t)((x<<8)|y)
#define MAKEINT16T(x,y) (int16_t)((x<<8)|y)

#define SPLITINT32T(a,tab,offset) 		\
{										\
	tab[0+offset]=(a>>24);				\
	tab[1+offset] = (a>>16)&0x00ff;		\
	tab[2+offset] = (a>>8)&0x00ff;		\
	tab[3+offset] = (a>>0)&0x00ff;		\
} 								


#endif