#ifndef INC_PIDCONTROLLER_H_
#define INC_PIDCONTROLLER_H_

typedef struct {
	float prevError;
	float integralError;
	float Kp;
	float Ki;
	float Kd;
} PID;

void pid_configure(PID *pid, float Kp, float Ki, float Kd);
void reset_pid_state(PID *pid);
float update_pid(PID *pid, float error, float rescale_factor) ;
#endif /* INC_PIDCONTROLLER_H_ */
