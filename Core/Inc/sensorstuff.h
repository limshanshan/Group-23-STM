
#ifndef INC_SENSORSTUFF_H_
#define INC_SENSORSTUFF_H_
#include "main.h"
#include "calc_conversions.h"
#include "ICM20948.h"
#include "magnetometer.h"
#include <math.h>
#include "ultrasonicsensor.h"
#include "calAngle.h"
//#include "dist.h"

#define ICM20948_I2C_ADDR 0
#define GRAVITATIONAL_CONSTANT 9.80665e-4f
typedef struct {
	float irSensorDistances[2];		//IR Sensor L,R distance
	volatile float ultrasonicDist;	//distance from ultrasonic sensor.

	float zAxisGyro;			//gyroscope Z axis
	float accelReadings[3];			//accelerometer X, Y, Z axis.
	float direction ;			//heading -180 to 180 degrees.

	float zAxisGyroBias;
	float accelerationBias[3];
	float direction_bias;
} SensorReadings;

#define ULTRASOUND_IC_CHANNEL TIM_CHANNEL_1
#define US_SENSOR_MIN_DELAY 20.0f //minimum delay
#define SET_US_TRIGGER() HAL_GPIO_WritePin(US_Trigger_GPIO_Port,US_Trigger_Pin,GPIO_PIN_SET)
#define CLEAR_US_TRIGGER() HAL_GPIO_WritePin(US_Trigger_GPIO_Port,US_Trigger_Pin,GPIO_PIN_RESET)

void initializeSensors(I2C_HandleTypeDef *i2c, ADC_HandleTypeDef *adcL, ADC_HandleTypeDef *adcR, TIM_HandleTypeDef *ic, SensorReadings *sensor);
void fetchIRSensorData();
void ultrasoundTriggerPulse();
void fetchUltrasoundSensorData(float pulse);
void fetchAccelReadings();
void fetchGyroscopeZData();
void calculatedirection (float timeElapsedMs, float zAxisGyro);
void calibrateSensorBias(uint16_t numSamples);

#endif /* INC_SENSORSTUFF_H_ */
