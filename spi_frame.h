#ifndef SPI_FRAME_H
#define SPI_FRAME_H

#include <Arduino.h> 

#define head_BYTE 0xff

#define GET_SIZE(octet) ( octet & 15 )
#define GET_TYPE(octet) ( octet >> 4 )
#define SET_SIZE(size) (size & 15)
#define SET_TYPE(type) (type << 4)
#define SET_SIZE_TYPE(type, size) ( ( ( type << 4) | (size & 15) ) )

#define STATUS_IDLE 0

#define RETRY_MAX 5


typedef struct Frame_t
{
	unsigned char sizeType;
	unsigned char checksum;
	unsigned char data[15];
} Frame_t;

extern Frame_t trame;
extern unsigned char frame_status;

int frameComputeChecksum();
int frameSend();
int frameReceive();
inline int frameCreateBeforeStail(unsigned char data[], int *len);
int frameGetChecksum(unsigned char *checksum);
int frameSetType(unsigned char type);
int frameGetType(unsigned char *type);
int frameSetSize(unsigned char size);
int frameGetSize(unsigned char *size);
int frameSetData(unsigned char data[15]);
int frameGetData(unsigned char data[]);
int frameVerifChecksum();

#endif