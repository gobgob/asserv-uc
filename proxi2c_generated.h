void i2c_runCmd(int i2c_reg,uint8_t * data_in,uint8_t * data_out,uint8_t * data_out_len);
void cmd_move(uint32_t rel_dist,int8_t sign);
void cmd_rotate(double angle,int8_t isAbs);
void cmd_goto(int32_t x,int32_t y,int32_t delta_max);
void cmd_getPosition(int32_t* x,int32_t* y,double* angle);
void cmd_setOdo(int32_t x,int32_t y,double angle,int8_t flag);
void cmd_setDistKpKd(uint32_t kp,uint32_t kd);
void cmd_getDistKpKd(uint32_t* kp,uint32_t* kd);
void cmd_setRotKpKd(uint32_t kp,uint32_t kd);
void cmd_getRotKpKd(uint32_t* kp,uint32_t* kd);
void cmd_getTicks(int32_t* left,int32_t* right);
void cmd_setTicks(int32_t left,int32_t right);
void cmd_getUltrasounds(int32_t* dist);
void cmd_getStatus(int8_t* bfr,int8_t* bfl,int8_t* bbr,int8_t* bbl,int8_t* cmdhack);
void cmd_setServo(uint8_t number,uint8_t angle);
void cmd_ratatouille(int8_t run,uint32_t delay_ms);
void cmd_launchNet(int8_t left,int8_t right,int8_t reset);
void cmd_setTickRatio(uint32_t new_ticks_per_meters,uint32_t new_ticks_per_rads);
void cmd_setBras(int8_t left,int8_t right);

#define SET_ODO_X 1
#define SET_ODO_Y 2
#define SET_ODO_ANGLE 4
