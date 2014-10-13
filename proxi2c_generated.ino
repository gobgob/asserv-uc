#include "proxi2c_generated.h"

enum i2c_registers
{
	REG_MOVE=1,
	REG_ROTATE=2,
	REG_GOTO=3,
	REG_GETPOSITION=4,
	REG_SETODO=5,
	REG_SETDISTKPKD=6,
	REG_GETDISTKPKD=7,
	REG_SETROTKPKD=8,
	REG_GETROTKPKD=9,
	REG_GETTICKS=10,
	REG_SETTICKS=11,
	REG_GETULTRASOUNDS=12,
	REG_GETSTATUS=13,
	REG_SETSERVO=14,
	REG_RATATOUILLE=15,
	REG_LAUNCHNET=16,
	REG_SETTICKRATIO=17,
	REG_SETBRAS=18,
};

void i2c_runCmd(int i2c_reg,uint8_t * data_in,uint8_t * data_out,uint8_t * data_out_len)
{
	switch(i2c_reg) {
		case REG_MOVE :
		Serial.println("cmd_move");
			cmd_move( 
			MAKEUINT32_T(data_in[0],data_in[1],data_in[2],data_in[3]),
			MAKEINT8_T(data_in[4]) 
			);
		break;
		case REG_ROTATE :
		Serial.println("cmd_rotate");
			cmd_rotate( 
			MAKEDOUBLE(data_in[0],data_in[1],data_in[2],data_in[3]),
			MAKEINT8_T(data_in[4]) 
			);
		break;
		case REG_GOTO :
		Serial.println("cmd_goto");
			cmd_goto( 
			MAKEINT32_T(data_in[0],data_in[1],data_in[2],data_in[3]),
			MAKEINT32_T(data_in[4],data_in[5],data_in[6],data_in[7]),
			MAKEINT32_T(data_in[8],data_in[9],data_in[10],data_in[11]) 
			);
		break;
		case REG_GETPOSITION :
		Serial.println("cmd_getPosition");
			int32_t ret_getPosition_x;
			int32_t ret_getPosition_y;
			double ret_getPosition_angle;
			cmd_getPosition( 
				&ret_getPosition_x,
				&ret_getPosition_y,
				&ret_getPosition_angle
			);
			SPLITINT32_T(ret_getPosition_x,data_out,0);
			SPLITINT32_T(ret_getPosition_y,data_out,4);
			SPLITDOUBLE(ret_getPosition_angle,data_out,8);
			*data_out_len = 12;
		break;
		case REG_SETODO :
		Serial.println("cmd_setOdo");
			cmd_setOdo( 
			MAKEINT32_T(data_in[0],data_in[1],data_in[2],data_in[3]),
			MAKEINT32_T(data_in[4],data_in[5],data_in[6],data_in[7]),
			MAKEDOUBLE(data_in[8],data_in[9],data_in[10],data_in[11]),
			MAKEINT8_T(data_in[12]) 
			);
		break;
		case REG_SETDISTKPKD :
		Serial.println("cmd_setDistKpKd");
			cmd_setDistKpKd( 
			MAKEUINT32_T(data_in[0],data_in[1],data_in[2],data_in[3]),
			MAKEUINT32_T(data_in[4],data_in[5],data_in[6],data_in[7]) 
			);
		break;
		case REG_GETDISTKPKD :
		Serial.println("cmd_getDistKpKd");
			uint32_t ret_getDistKpKd_kp;
			uint32_t ret_getDistKpKd_kd;
			cmd_getDistKpKd( 
				&ret_getDistKpKd_kp,
				&ret_getDistKpKd_kd
			);
			SPLITUINT32_T(ret_getDistKpKd_kp,data_out,0);
			SPLITUINT32_T(ret_getDistKpKd_kd,data_out,4);
			*data_out_len = 8;
		break;
		case REG_SETROTKPKD :
		Serial.println("cmd_setRotKpKd");
			cmd_setRotKpKd( 
			MAKEUINT32_T(data_in[0],data_in[1],data_in[2],data_in[3]),
			MAKEUINT32_T(data_in[4],data_in[5],data_in[6],data_in[7]) 
			);
		break;
		case REG_GETROTKPKD :
		Serial.println("cmd_getRotKpKd");
			uint32_t ret_getRotKpKd_kp;
			uint32_t ret_getRotKpKd_kd;
			cmd_getRotKpKd( 
				&ret_getRotKpKd_kp,
				&ret_getRotKpKd_kd
			);
			SPLITUINT32_T(ret_getRotKpKd_kp,data_out,0);
			SPLITUINT32_T(ret_getRotKpKd_kd,data_out,4);
			*data_out_len = 8;
		break;
		case REG_GETTICKS :
		Serial.println("cmd_getTicks");
			int32_t ret_getTicks_left;
			int32_t ret_getTicks_right;
			cmd_getTicks( 
				&ret_getTicks_left,
				&ret_getTicks_right
			);
			SPLITINT32_T(ret_getTicks_left,data_out,0);
			SPLITINT32_T(ret_getTicks_right,data_out,4);
			*data_out_len = 8;
		break;
		case REG_SETTICKS :
		Serial.println("cmd_setTicks");
			cmd_setTicks( 
			MAKEINT32_T(data_in[0],data_in[1],data_in[2],data_in[3]),
			MAKEINT32_T(data_in[4],data_in[5],data_in[6],data_in[7]) 
			);
		break;
		case REG_GETULTRASOUNDS :
		Serial.println("cmd_getUltrasounds");
			int32_t ret_getUltrasounds_dist;
			cmd_getUltrasounds( 
				&ret_getUltrasounds_dist
			);
			SPLITINT32_T(ret_getUltrasounds_dist,data_out,0);
			*data_out_len = 4;
		break;
		case REG_GETSTATUS :
		Serial.println("cmd_getStatus");
			int8_t ret_getStatus_bfr;
			int8_t ret_getStatus_bfl;
			int8_t ret_getStatus_bbr;
			int8_t ret_getStatus_bbl;
			int8_t ret_getStatus_cmdhack;
			cmd_getStatus( 
				&ret_getStatus_bfr,
				&ret_getStatus_bfl,
				&ret_getStatus_bbr,
				&ret_getStatus_bbl,
				&ret_getStatus_cmdhack
			);
			SPLITINT8_T(ret_getStatus_bfr,data_out,0);
			SPLITINT8_T(ret_getStatus_bfl,data_out,1);
			SPLITINT8_T(ret_getStatus_bbr,data_out,2);
			SPLITINT8_T(ret_getStatus_bbl,data_out,3);
			SPLITINT8_T(ret_getStatus_cmdhack,data_out,4);
			*data_out_len = 5;
		break;
		case REG_SETSERVO :
		Serial.println("cmd_setServo");
			cmd_setServo( 
			MAKEUINT8_T(data_in[0]),
			MAKEUINT8_T(data_in[1]) 
			);
		break;
		case REG_RATATOUILLE :
		Serial.println("cmd_ratatouille");
			cmd_ratatouille( 
			MAKEINT8_T(data_in[0]),
			MAKEUINT32_T(data_in[1],data_in[2],data_in[3],data_in[4]) 
			);
		break;
		case REG_LAUNCHNET :
		Serial.println("cmd_launchNet");
			cmd_launchNet( 
			MAKEINT8_T(data_in[0]),
			MAKEINT8_T(data_in[1]),
			MAKEINT8_T(data_in[2]) 
			);
		break;
		case REG_SETTICKRATIO :
		Serial.println("cmd_setTickRatio");
			cmd_setTickRatio( 
			MAKEDOUBLE(data_in[0],data_in[1],data_in[2],data_in[3]),
			MAKEDOUBLE(data_in[4],data_in[5],data_in[6],data_in[7]) 
			);
		break;
		case REG_SETBRAS :
		Serial.println("cmd_setBras");
			cmd_setBras( 
			MAKEINT8_T(data_in[0]),
			MAKEINT8_T(data_in[1]) 
			);
		break;
	};
};
