#include "spi.h"
#include "spi_buffer.h"
#include "spi_frame.h"

//================================================================
// FRAME
//================================================================

Frame_t trame;
unsigned char frame_status = STATUS_IDLE;

int frameComputeChecksum()
{
	unsigned char i = 0;
	unsigned char checksum = trame.sizeType;
	for( i=0; i < ( GET_SIZE(trame.sizeType) );i++)
		checksum ^= trame.data[i];
	trame.checksum = checksum;
	return 0;
}

int frameSend()
{
	unsigned char data[18];
	int len;
	if( frameCreateBeforeStail( data, &len) != 0 )
		return -1;
	int i;
	for( i=0; i<len; i++ )
	{
		// Serial.println(data[i],HEX);
		if( circle_buffer_write(&buffer_write, data[i]) != 0 )
			return -1;
		
	}
	return 0;
}

int frameReceive()
{
	if(frame_status == STATUS_IDLE)
	{
		if( circle_buffer_available(&buffer_read) >= 2 )
		{
			unsigned char value;
			circle_buffer_read(&buffer_read, &value);
			if( value != head_BYTE )
				return -1;
			circle_buffer_read(&buffer_read, &value);
			trame.sizeType = value;
			frame_status = GET_SIZE(value)+1;
		}
	}
	else
	{
		if( circle_buffer_available(&buffer_read) >= frame_status )
		{
			unsigned char value;
			int i;
			for( i=0; i<frame_status-1;i++)
			{
				circle_buffer_read(&buffer_read, &value);
				trame.data[i] = value;
			}
			circle_buffer_read(&buffer_read, &value);
			trame.checksum = value;
			frame_status = STATUS_IDLE;
			return 0;
		}
	}
	return -2;
}

inline int frameCreateBeforeStail(unsigned char data[], int *len)
{
	unsigned char size;
	int i;
	for(i=0;i<18;i++)
		data[i] = 0;
	data[0] = head_BYTE;
	data[1] = trame.sizeType;
	if( frameGetSize(&size) != 0 )
		return -1;
	for( i=0; i<size; i++)
		data[i+2] = trame.data[i];
	data[i+2] = trame.checksum;
	*len = (int)size+3;
	return 0;
}

int frameGetChecksum(unsigned char *checksum)
{
	*checksum = trame.checksum;
	return 0;
}

int frameSetType(unsigned char type)
{
	if( type > 15 )
		return -1;
	trame.sizeType &= 0x0f;
	trame.sizeType |= SET_TYPE(type);
	return 0;
}

int frameGetType(unsigned char *type)
{
	*type = GET_TYPE(trame.sizeType);
	return 0;
}

int frameSetSize(unsigned char size)
{
	if( size > 15 )
		return -1;
	trame.sizeType &= 0xf0;
	trame.sizeType |= SET_SIZE(size);
	return 0;
}

int frameGetSize(unsigned char *size)
{
	*size = GET_SIZE(trame.sizeType);
	return 0;
}

int frameSetData(unsigned char data[15])
{
	int i;
	for( i=0;i<15;i++)
		trame.data[i] = data[i];
	return 0;
}

int frameGetData(unsigned char data[])
{
	int i;
	for( i=0;i<16;i++)
		data[i] = trame.data[i];
	return 0;
}

int frameVerifChecksum()
{
	unsigned char checksum = trame.checksum;
	frameComputeChecksum();
	if( trame.checksum != checksum )
		return -1;
	return 0;
}