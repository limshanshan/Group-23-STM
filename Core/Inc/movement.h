#ifndef INC_MOVEMENT_H_
#define INC_MOVEMENT_H_

#include "ICM20948.h"

void movement_init(I2C_HandleTypeDef *i2cHandlePtr1);
void read_gyroZ(float *gyroZaxis);
void read_accel(float accelxyzaxis[3]);
void read_heading(float *direction);
void set_bias();

#endif /* INC_MOVEMENT_H_ */
