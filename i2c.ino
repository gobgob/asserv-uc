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
	Serial.println("i2c_init");
	Serial1.begin(115200);
}

uint8_t myRead(uint8_t * checksum)
{
	uint8_t res = Serial1.read();
	*checksum^=res;
	return res;
}

void serial_process()
{

	int i;
	int len;
	uint8_t checksum=0;

	static unsigned long cmd_time = 0;

	//Serial.println("serial_process");
	
	if(Serial1.available()>=3) {

		char c = myRead(&checksum);
		if(c!=0xFF) {
			Serial.println(c,DEC);
			Serial.println("bad synchronistation");
			return;
		}

		i2c_reg = myRead(&checksum);
		len = myRead(&checksum);
		// DUMP_VAR(i2c_reg);
		// DUMP_VAR(len);

	}else{
		return;
	}
	
	cmd_time = millis();

	//TODO : add timeout
	while(Serial1.available()<len+1) {
		//Serial.println("waiting");
		if(millis()>(cmd_time+200)) {
			Serial.println("timeout waiting");
			return;
		}
		//wait
	}

	for(i=0;i<len;i++) {
		data_in[i]=myRead(&checksum);
		// DUMP_VAR(data_in[i]);
	}

	uint8_t data_checksum=Serial1.read();

	if (data_checksum!=checksum) {
		Serial.println("bad checksum");
		return;
	}

	i2c_runCmd(i2c_reg, (uint8_t *)data_in, (uint8_t *)data_out, (uint8_t *)&data_out_len);


	if(data_out_len>0) {
		checksum=0;
		for(int i=0;i<data_out_len;i++){
			// data_out[i]=0
			checksum^=data_out[i];
			Serial1.write(data_out[i]);
		}
		Serial1.write(checksum);
		data_out_len=0;
	}
}


// //
// // handle Tx Event (outgoing I2C data)
// //
// void i2c_requestEvent(void)
// {
// 	uint8_t checksum=0;

// 	//Serial.println("requestEvent");
// 	for(int i=0;i<data_out_len;i++){
// 		// data_out[i]=0
// 		checksum^=data_out[i];
// 		Wire.write(data_out[i]);
// 	}
// 	Wire.write(checksum);
// 	//Wire.write((uint8_t *)data_out, data_out_len); // fill Tx buffer (from addr location to end of mem)
// }