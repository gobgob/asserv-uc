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
#define REBOOT 9

// Define Getter / Setter
#define MAX_SPEED_ROT 0
#define MAX_SPEED_LIN 1
#define KPKD_ROT 2
#define KPKD_LIN 3
#define TICK_RATIO 4
#define ODO 4
#define STATUS 5
#define TICKS 6


// Define Args Functions
#define GOFORWARD 0
#define GOBACK 1
#define ROTATE 2
#define GOTO 3

// Define odo seter flags
#define SET_ODO_X (1<<0)
#define SET_ODO_Y (1<<1)
#define SET_ODO_ANGLE (1<<2)

#define MAKEDOUBLE(x,y,z,t) (double)((x<<24)|y<<16|z<<8|t)
#define MAKEINT16T(x,y) (int16_t)(((int16_t)x<<8)|(int16_t)y)
#define MAKEINT32T(x,y,z,t) (int32_t)(((int32_t)x<<24)|(int32_t)y<<16|(int32_t)z<<8|(int32_t)t)
#define MAKEUINT16T(x,y) (uint16_t)(((uint16_t)x<<8)|y)
#define MAKEUINT32T(x,y,z,t) (uint32_t)(((uint32_t)x<<24)|(uint32_t)y<<16|(uint32_t)z<<8|(uint32_t)t)

#define SPLITINT32T(a,tab,offset) 		\
{										\
	tab[0+offset]=(a>>24);				\
	tab[1+offset] = (a>>16)&0x00ff;		\
	tab[2+offset] = (a>>8)&0x00ff;		\
	tab[3+offset] = (a>>0)&0x00ff;		\
}

#define SPLITUINT32T(a,tab,offset) 		\
{										\
	tab[0+offset]=(a>>24);				\
	tab[1+offset] = (a>>16)&0x00ff;		\
	tab[2+offset] = (a>>8)&0x00ff;		\
	tab[3+offset] = (a>>0)&0x00ff;		\
}

#define SPLITINT16T(a,tab,offset) 		\
{										\
	tab[0+offset]=(a>>8);				\
	tab[1+offset] = (a>>0)&0x00ff;		\
}								


#endif