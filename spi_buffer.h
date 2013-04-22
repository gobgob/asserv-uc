#ifndef SPI_BUFFER_H
#define SPI_BUFFER_H

#include <Arduino.h> 

#define BUFFER_SIZE 32

typedef volatile struct CircleBuffer
{
	unsigned char data[BUFFER_SIZE];
	unsigned char head;
	unsigned char tail;
	unsigned char msb;
} CircleBuffer_t;

extern CircleBuffer_t buffer_write;
extern CircleBuffer_t buffer_read;

void circle_buffer_init(CircleBuffer_t *buffer);
unsigned int circle_buffer_available(CircleBuffer_t *buffer);

int circle_buffer_write(CircleBuffer_t *buffer, unsigned char value);
int circle_buffer_read(CircleBuffer_t *buffer, unsigned char *value);

#endif