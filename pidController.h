#ifndef PIDCONTROLER_H
#define PIDCONTROLER_H

#include "feedbackProvider.h"
#include "hbridge.h"

class PidController{
private:
	unsigned long lastTime;
	int32_t output;
	int32_t setpoint;
	int32_t iTerm, lastInput;
	int32_t lastError;
	//double outMin, outMax;
	uint32_t kp, ki, kd;
	double sampleTime;

	HBridge * hb;
	FeedbackProvider * fp;

public:
	PidController(HBridge * hb,FeedbackProvider * fp);

	void compute();

	void setTunings(int Kp, int Ki, int Kd);

	double getKp();
	double getKi();
	double getKd();

	void setSampleTime(int newSampleTime);
	void setTarget(double target);
};

#endif

