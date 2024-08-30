#include "leftrightmotor.h"

//Timers for: PWM, L/R Encoders
static TIM_HandleTypeDef *motor_pwm_tim, *left_encoder_tim, *right_encoder_tim;

//for matching motor speeds.
static int16_t pwmAcceleration = 0, pwmTarget = 0,
	leftMotorPWM = 0, rightMotorpwm = 0;
static int16_t leftCount = 0, rightCount = 0;
//for bi-directional correction.
static int8_t direction = 0;

//We can fine tune these values below (PID)
static PID pidMatchSpeed;
const static float Kp_match = 5e4;
const static float Ki_match = 7e2;
const static float Kd_match = 3e3;

static PID pidDistTarget;

const static float Kp_distTarget = 1.4;
const static float Ki_distTarget = 0.0011;
const static float Kd_distTarget = 0.12;

static PID pidDistAway;
const static float Kp_distAway = 1.55;
const static float Ki_distAway = 7e-5;
const static float Kd_distAway = 0.25;
