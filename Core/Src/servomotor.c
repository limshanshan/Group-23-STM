#include "servomotor.h"

static TIM_HandleTypeDef *pwm_timer;

#define SERVO_ANGLETOPWMTABLE_SIZE 38
static float angletopwmtable[38][2] = {
	//{angle, PWM value}
	{-35, 3200},
	{-32, 3300},
	{-29, 3400},
	{-26, 3500},
	{-24, 3600},
	{-22, 3750},
	{-20, 3800},
	{-18, 3900},
	{-14, 4000},
	{-13, 4100},
	{-10, 4200},
	{-7, 4300},
	{-6, 4400},
	{-4, 4500},
	{-2, 4600},
	{-1, 4700},
	{0, 4800},
	{1, 4900},
	{1.5, 5000},
	{3, 5100},
	{4.5, 5200},
	{7, 5300},
	{8.5, 5400},
	{10, 5500},
	{12, 5600},
	{13, 5700},
	{14, 5800},
	{15, 5900},
	{16, 6000},
	{17, 6100},
	{20, 6200},
	{21, 6300},
	{22, 6400},
	{23, 6500},
	{24, 6600},
	{25, 6700},
	{25.5, 6800},
	{26, 6900}
};

void servomotor_init(TIM_HandleTypeDef *PWM) {
	pwm_timer = PWM;
	HAL_TIM_PWM_Start(PWM, SERVOMOTOR_PWM_CHANNEL); //Start PWM signal generation
}

void servomotor_setvalue(uint32_t value) {
	//sets the PWM duty cycle to control the servo motor position.
	//control the servo motor position. = turning angle
	pwm_timer->Instance->CCR1 = value;
}

//turning angle of the servo motor
void servomotor_setangle(float servoangle) {
	//clamp angle to within width.
	//prevents the servo from moving beyond its mechanical limits.
	uint32_t value = 0;
	uint8_t a;
	if(servoangle > SERVOMOTOR_WIDTH){
		 servoangle = SERVOMOTOR_WIDTH;
	}
	else if(servoangle < -SERVOMOTOR_WIDTH){
		servoangle = -SERVOMOTOR_WIDTH;
	}

	if(servoangle >= angletopwmtable[SERVO_ANGLETOPWMTABLE_SIZE - 1][0]){
		value = angletopwmtable[SERVO_ANGLETOPWMTABLE_SIZE - 1][0];
	}
	else if(servoangle <= angletopwmtable[0][0]){
		value = angletopwmtable[0][0];
	}
	else{
		float min_pwm_val, max_pwm_val, min_servo_angle, max_servo_angle;
		for (a = 0; a < SERVO_ANGLETOPWMTABLE_SIZE - 1; a++) {
			min_servo_angle = angletopwmtable[a][0];
			max_servo_angle = angletopwmtable[a+1][0];
			min_pwm_val = angletopwmtable[a][1];
			max_pwm_val = angletopwmtable[a+1][1];
			if(servoangle <= max_servo_angle && servoangle >= min_servo_angle){
				value = min_pwm_val + (max_pwm_val - min_pwm_val) * (servoangle - min_servo_angle) / (max_servo_angle - min_servo_angle);
				break;
			}
		}
	}

	if (value == 0) value = angletopwmtable[SERVO_ANGLETOPWMTABLE_SIZE - 1][1];
	servomotor_setvalue(value);
}
