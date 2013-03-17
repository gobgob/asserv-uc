//Most of this class is from :
//http://brettbeauregard.com/blog/2011/04/improving-the-beginner%E2%80%99s-pid-tuning-changes/


#include "pidController.h"

PidController::PidController(HBridge * hb,FeedbackProvider * fp):
hb(hb),
fp(fp),
setpoint(0)
{
	// outMax = hb->getMaxOutput();
	// outMin = hb->getMaxOutput();
}

void PidController::compute()
{
		int32_t input = fp->read();
		/*Compute all the working error variables*/
		int32_t  error = setpoint - input;
		iTerm+= error;
		
		int32_t dinput = (input - lastInput);
		/*Compute PID output*/
		output =  error*kp+ iTerm*ki - dinput*kd;
		hb->setSpeed(output/1024);

		/*Remember some variables for next time*/
		lastInput = input;	
}



void PidController::setTunings(int Kp, int Ki, int Kd)
{
  double sampleTimeInSec = ((double)sampleTime)/1000;
   kp = Kp;
   ki = Ki;
   kd = Kd;
}
 
void PidController::setSampleTime(int newSampleTime)
{

}

void PidController::setTarget(double target)
{
	setpoint=target;
}