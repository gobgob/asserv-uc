#include <i2c_t3.h>
#include "i2c.h"
#include "config.h"
#include "api.h"
#include "proxi2c_generated.h"


// Function prototypes
void i2c_receiveEvent(size_t len);
void i2c_requestEvent(void);

volatile uint8_t data_in[256];
volatile uint8_t data_out[256];
volatile uint8_t data_out_len=0;

volatile int i2c_reg;

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

	int i;

	
	if(Wire.available())
	{
		i2c_reg = Wire.readByte();
	}
	
	if(Wire.available())
	{
		int len = Wire.readByte();
	
		for(i=0;i<len;i++)
		{
			if(Wire.available()) {
			data_in[i]=Wire.readByte();
			} else {
			Serial.println("Really not good !");
			}
		}	 
	}
	i2c_runCmd(i2c_reg, (uint8_t *)data_in, (uint8_t *)data_out, (uint8_t *)&data_out_len);
}

//
// handle Tx Event (outgoing I2C data)
//
void i2c_requestEvent(void)
{
	Serial.println("requestEvent");
	// for(int i=0;i<data_out_len;i++){
	// 	DUMP_VAR(data_out[i]);		
	// }
	Wire.write((uint8_t *)data_out, data_out_len); // fill Tx buffer (from addr location to end of mem)
}