#include "movement.h"
#include <math.h>

#define I2C_ADDR 0

const uint8_t GYRO_SENS = GYRO_FULL_SCALE_2000DPS;
const uint8_t ACCEL_SENS = ACCEL_FULL_SCALE_2G;

I2C_HandleTypeDef *hi2c1_ptr;
volatile int16_t gyroZ_raw;
volatile float accel_raw[3];
volatile int16_t magZ_raw;

//bias.
float accel_bias[3];
volatile float dir_bias;

void movement_init(I2C_HandleTypeDef *i2cHandlePtr1) {
	hi2c1_ptr = i2cHandlePtr1;
	ICM20948_init(hi2c1_ptr, I2C_ADDR, GYRO_SENS, ACCEL_SENS);
}


void read_gyroZ(float *gyroZaxis) {
	ICM20948_readGyroscope_Z(hi2c1_ptr, I2C_ADDR, GYRO_SENS, gyroZaxis);
}


void read_accel(float accelxyzaxis[3]) {
	ICM20948_readAccelerometer_all(hi2c1_ptr, I2C_ADDR, ACCEL_SENS, accelxyzaxis);
	for (int i = 0; i < 3; i++) accelxyzaxis[i] -= accel_bias[i];
}

float readMagnetometer() {
	//Calculate angle from X and Y
	float xy[2];
	ICM20948_readMagnetometer_XY(hi2c1_ptr, xy);
	return atan2(xy[1], xy[0]) * 180 / M_PI;
}
void read_heading(float *direction) {
	*direction = readMagnetometer() - dir_bias;
	if (*direction < 0) *direction += 360;
}

void set_bias() {
	for (int i = 0; i < 500; i++) {
		ICM20948_readAccelerometer_all(hi2c1_ptr, I2C_ADDR, ACCEL_SENS, accel_bias); //accelerometer bias
		dir_bias = readMagnetometer(); //heading bias
	}
}
