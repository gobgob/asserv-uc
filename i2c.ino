#include <i2c_t3.h>
#include "i2c.h"
#include "config.h"
#include "api.h"
#include "proxi2c_generated.h"


// Function prototypes
void i2c_receiveEvent(size_t len);
void i2c_requestEvent(void);

void i2c_init()
{
	// Setup for Slave mode, address 0x44, pins 18/19, external pullups, 400kHz
	Wire.begin(
		I2C_SLAVE,
		I2C_ADDR,
		I2C_PINS_18_19,
		I2C_PULLUP_EXT,
		I2C_RATE_400
		);

	// register events
	Wire.onReceive(i2c_receiveEvent);
	Wire.onRequest(i2c_requestEvent);
}

void i2c_receiveEvent(size_t len)
{
	uint8_t data[64];
	int i,i2c_reg;
	
	if(Wire.available())
		i2c_reg = Wire.readByte();
	
	if(Wire.available())
	{
		data[0] = Wire.readByte();
	
		for(i=0;i<data[0];i++)
		{
			if(Wire.available()) {
			data[i+1]=Wire.readByte();
			} else {
			Serial.println("Really not good !");
			}
		}	 
		i2c_runCmd(i2c_reg,data);
	}
}

//
// handle Tx Event (outgoing I2C data)
//
void i2c_requestEvent(void)
{
	Serial.println("requestEvent");
	int mem[256];
	mem[0]=2;
	mem[1]=2;
	//switch(cmd)
	//{
	//case READ:
	Serial.println("requestEvent READ");
	//Wire.write(&mem[0], MEM_LEN); // fill Tx buffer (from addr location to end of mem)
	//	break;
	//}
}