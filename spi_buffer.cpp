#include "spi.h"
#include "spi_buffer.h"
CircleBuffer_t buffer_write;
CircleBuffer_t buffer_read;

void circle_buffer_init(CircleBuffer_t *buffer)
{
	buffer->head = 0;
	buffer->tail = 0;
	buffer->msb = 0;
}

unsigned int circle_buffer_available(CircleBuffer_t *buffer)
{
	return ( buffer->msb * BUFFER_SIZE + buffer->head - buffer->tail );
}

int circle_buffer_write(CircleBuffer_t *buffer, unsigned char value)
{
	if( buffer->head == buffer->tail && buffer->msb == 1 )
		return -1;
	buffer->data[buffer->head] = value;
	buffer->head = ( buffer->head + 1 ) % BUFFER_SIZE;
	if( buffer->head == 0 )
		buffer->msb = 1;
	return 0;
}

int circle_buffer_read(CircleBuffer_t *buffer, unsigned char *value)
{
	if( buffer->head == buffer->tail && buffer->msb == 0 )
		return -1;
	*value = buffer->data[buffer->tail];
	buffer->tail = ( buffer->tail + 1 ) % BUFFER_SIZE;
	if( buffer->tail == 0 )
		buffer->msb = 0;
	return 0;
}