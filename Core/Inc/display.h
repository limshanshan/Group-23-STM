#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include "oled.h"

void display_init();
void write_motion(float accelxyzaxis[3], float direction, float gyroZaxis);
void write_motors(uint16_t leftAngle, uint16_t rightAngle, uint16_t leftPwmVal, uint16_t rightPwmVal, int32_t offset_val);

#endif /* INC_DISPLAY_H_ */
