#include "PIDController.h"

void reset_pid_state(PID *pid) {
	pid->integralError = 0;
	pid->prevError = 0;
}

void pid_configure(PID *pid, float Kp, float Ki, float Kd) {
	pid_reset(pid);

	pid->Kp = Kp;
	pid->Ki = Ki;
	pid->Kd = Kd;
}

float update_pid(PID *pid, float error, float rescale_factor) {
	pid->integralError += error;
	float errorRate = (error - pid->prevError);
	pid->prevError = error;

	return error * pid->Kp * rescale_factor + pid->integralError * pid->Ki * rescale_factor + errorRate * pid->Kd * rescale_factor;
}
