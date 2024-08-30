
#ifndef INC_SERVOMOTOR_H_
#define INC_SERVOMOTOR_H_


#include "main.h"
#include "calc_conversions.h"
#include "oled.h"

#define SERVOMOTOR_WIDTH 25.0f //degrees L/R
#define SERVOMOTOR_TURN_INTERVAL 20.0f //ms before turn is updated
#define SERVOMOTOR_TURN_INCREMENT 3.0f //degrees to turn

#define SERVOMOTOR_PWM_CHANNEL TIM_CHANNEL_1

void servomotor_init(TIM_HandleTypeDef *PWM);
void servomotor_setvalue(uint32_t value);
void servomotor_setangle(float angle);

#endif /* INC_SERVOMOTOR_H_ */
