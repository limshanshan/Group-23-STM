#ifndef INC_LEFTRIGHTMOTOR_H_
#define INC_LEFTRIGHTMOTOR_H_
#include "main.h"
#include "PIDController.h"
#include "calc_conversions.h"
//#include "commands.h"

//PWM Parameters
#define MOTOR_PWM_CYCLE_PERIOD 7200
#define MOTOR_PWM_SAFE_MAX 6000
#define MOTOR_PWM_MIN_SPEED 375
#define MOTOR_PWM_MAX_ACCEL_CHANGE 20
#define MOTOR_PWM_MAX_OFFSET_RATIO 0.05f
#define MOTOR_BRAKING_TARGET 30.0f
#define MOTOR_BRAKING_AWAY 40.0f
#define MOTOR_PERIOD_ADJUST 10.0f

#define LEFT_MOTOR_CHANNEL TIM_CHANNEL_1
#define RIGHT_MOTOR_CHANNEL TIM_CHANNEL_2

typedef enum COMMAND_TYPE CommandType;


#endif /* INC_LEFTRIGHTMOTOR_H_ */
