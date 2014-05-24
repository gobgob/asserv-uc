#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>
#include <stdarg.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define INT_MAX = (32767)
#define INT_MIN = (-32768)

#define pythagore(x,y)	sqrt((x)*(x)+(y)*(y))

void myPrintf(char *fmt, ... );
int32_t maximizeDiff(int32_t oldValue, int32_t newValue, int32_t diffMax);
int32_t maximize(int32_t value, int32_t diffMax);
double principal_angle(double angle);
double closest_equivalent_angle(double old_angle,double new_angle);

#define DUMP_VAR(x)		\
{						\
	Serial.print(#x);	\
	Serial.print(" : ");\
	Serial.println(x);	\
}

#define DEBUG_PIN_ON digitalWrite(DEBUG_PIN_GENERAL,HIGH)
#define DEBUG_PIN_OFF digitalWrite(DEBUG_PIN_GENERAL,LOW)


// #define MAKEDOUBLE(x,y,z,t) (double)((x<<24)|y<<16|z<<8|t)
#define MAKEINT8_T(x) (int8_t)x
#define MAKEUINT8_T(x) (uint8_t)x
#define MAKEINT16_T(x,y) (int16_t)(((int16_t)x<<8)|(int16_t)y)
#define MAKEINT32_T(x,y,z,t) (int32_t)(((int32_t)x<<24)|(int32_t)y<<16|(int32_t)z<<8|(int32_t)t)
#define MAKEUINT16_T(x,y) (uint16_t)(((uint16_t)x<<8)|y)
#define MAKEUINT32_T(x,y,z,t) (uint32_t)(((uint32_t)x<<24)|(uint32_t)y<<16|(uint32_t)z<<8|(uint32_t)t)



double MAKEDOUBLE(uint8_t x,uint8_t y,uint8_t z,uint8_t t)
{						
	return ((double)(MAKEUINT32_T(x,y,z,t)))/100000.;
}									

#define SPLITDOUBLE(a,tab,offset) 					\
{													\
	SPLITINT32_T((int32_t)(a*100000.),tab,offset);	\
}

#define SPLITINT32_T(a,tab,offset) 		\
{										\
	tab[0+offset]=(a>>24);				\
	tab[1+offset] = (a>>16)&0x00ff;		\
	tab[2+offset] = (a>>8)&0x00ff;		\
	tab[3+offset] = (a>>0)&0x00ff;		\
}

#define SPLITUINT32_T(a,tab,offset) 	\
{										\
	tab[0+offset]=(a>>24);				\
	tab[1+offset] = (a>>16)&0x00ff;		\
	tab[2+offset] = (a>>8)&0x00ff;		\
	tab[3+offset] = (a>>0)&0x00ff;		\
}

#define SPLITINT16_T(a,tab,offset) 		\
{										\
	tab[0+offset]=(a>>8);				\
	tab[1+offset] = (a>>0)&0x00ff;		\
}								

#define SPLITINT8_T(a,tab,offset) 		\
{										\
	tab[offset]=a;						\
}

#endif