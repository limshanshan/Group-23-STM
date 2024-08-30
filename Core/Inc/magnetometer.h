#ifndef INC_MAGNETOMETER_H_
#define INC_MAGNETOMETER_H_

#include <userbutton.h>
#include "main.h"
#include "ICM20948.h"
#include "oled.h"
#include "calc_conversions.h"

#define MAGNETOMETER_CAL_SAMPLES 100

typedef struct{
	float biasVector[2];
	float scaleMatrix[2][2];
} MagCalSettings;

void initialize_magnetometer(I2C_HandleTypeDef *i2cHandlePtr, MagCalSettings *settings);
void magnetometer_settings();
void correctMagnetometer(float magnetometer[2]);

#endif /* INC_MAGNETOMETER_H_ */
