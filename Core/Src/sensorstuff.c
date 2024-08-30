#include "sensorstuff.h"
#define IRsensor_MIN 6.0f
#define IRsensor_MAX 70.0f
#define IRsensor_OFFSET 4.5f
#define PI 3.14159265358979323846
static const uint8_t Accelerometer = ACCEL_FULL_SCALE_2G;
static const uint8_t Gyroscope=GYRO_FULL_SCALE_250DPS;
static const float const_irDist=0.95;

static const float const_usDist = 0.58;
static const float const_mag = 0.9;
static float oldMagReadings[2];

static I2C_HandleTypeDef *i2cHandlePtr;
static ADC_HandleTypeDef *leftAdcHandlePtr;
static ADC_HandleTypeDef *rightAdcHandlePtr;
static TIM_HandleTypeDef *inputCaptureHandlePtr;
static SensorReadings *sensorDataPtr;

//low pass filter to smooth out sensor data
static float LowPassFilter(float smoothingFactor, float previousValue, float currentValue) {
	// a: smoothing factor (between 0 to 1), higher a results in smoother data and less responsive to suudden change
	return ((1-smoothingFactor)*currentValue)+(smoothingFactor*previousValue);
}

static float ReadMagnetometerAngle() {
	//Calculate angle from X and Y
	float magnetometerValues[2];
	ICM20948_readMagnetometer_XY(i2cHandlePtr, magnetometerValues); //read magnetometer values for X and Y axis
	for (uint8_t a = 0; a < 2; a++) {
		magnetometerValues[a] = LowPassFilter(const_mag, oldMagReadings[a], magnetometerValues[a]); //noises can affect the readings, so we need lpf to smooth out the readings
		oldMagReadings[a] = magnetometerValues[a];
	}
	magcal_adjust(magnetometerValues);
	return -atan2(magnetometerValues[1], magnetometerValues[0]) * 180 / PI;
}

void initializeSensors(I2C_HandleTypeDef *i2c, ADC_HandleTypeDef *adcL, ADC_HandleTypeDef *adcR, TIM_HandleTypeDef *ic, SensorReadings *sensor){
	i2cHandlePtr = i2c;
	inputCaptureHandlePtr = ic;
	leftAdcHandlePtr = adcL;
	rightAdcHandlePtr = adcR;
	sensorDataPtr = sensor;

	ICM20948_init(i2cHandlePtr, ICM20948_I2C_ADDR, Gyroscope, Accelerometer);
	ICM20948_readMagnetometer_XY(i2cHandlePtr, oldMagReadings); //pre-load magOld values.

	//Starts the TIM Input Capture measurement in interrupt mode by measuring the distance based on the time it takes for an echo to return after a pulse is sent out
	HAL_TIM_IC_Start_IT(ic, ULTRASOUND_IC_CHANNEL);

	sensor->zAxisGyroBias = 0;
	sensor->accelerationBias[0] = sensor->accelerationBias[1] = sensor->accelerationBias[2] = 0;

	float dir_angle = ReadMagnetometerAngle();
	sensor->direction_bias = dir_angle;
	angle_init(dir_angle);
}

void sensors_us_trig() {
	CLEAR_US_TRIGGER(); //reset the sensor and ensure that any previous signals do not interfere with the new measurement.
	ultrasonic_Delay(5);

	//1. 10us pulse
	SET_US_TRIGGER();
	ultrasonic_Delay(10);
	CLEAR_US_TRIGGER();
}

void fetchUltrasoundSensorData(float pulse) {
	// Sound velocity = 343 meters/sec
	// new_dist is in cm
	float distance = pulse * 34300 / 2; //divide 2 to find 1 way distance
//	sensors_ptr->usDist = new_dist;
	sensorDataPtr->ultrasonicDist = LowPassFilter(const_usDist, sensorDataPtr->ultrasonicDist, distance);
}

static float computeDistanceFromIrSensor(uint16_t irSensorValue) {
	float div = pow(((float) irSensorValue) / 4095, 1.226);
	float calculatedDistance;
	if(div < (6.3028 / IRsensor_MAX)){
		calculatedDistance=IRsensor_MAX;
	}
	else{
		calculatedDistance=6.3028 / div;
	}

	calculatedDistance = calculatedDistance - IRsensor_OFFSET;
	if (calculatedDistance < IRsensor_MIN)
	{
		calculatedDistance = IRsensor_MIN;
	}
	return calculatedDistance; //dist is in cm
}

void fetchIRSensorData() {
	HAL_ADC_Start(leftAdcHandlePtr); //Initiates the analog-to-digital conversion
	HAL_ADC_Start(rightAdcHandlePtr);
	while((HAL_ADC_PollForConversion(rightAdcHandlePtr, HAL_MAX_DELAY) != HAL_OK)&&(HAL_ADC_PollForConversion(leftAdcHandlePtr, HAL_MAX_DELAY) != HAL_OK));
	//check if the conversion is complete

	uint16_t leftSensorValue  = (uint16_t) HAL_ADC_GetValue(leftAdcHandlePtr), rightSensorValue = (uint16_t) HAL_ADC_GetValue(rightAdcHandlePtr);//Reads the digital values from left&right IR Sensor
	sensorDataPtr->irSensorDistances[0] = LowPassFilter(const_irDist, sensorDataPtr->irSensorDistances[0], computeDistanceFromIrSensor(leftSensorValue));
	sensorDataPtr->irSensorDistances[1] = LowPassFilter(const_irDist, sensorDataPtr->irSensorDistances[1], computeDistanceFromIrSensor(rightSensorValue));
}

void fetchGyroscopeZData() {
	float gyroZValue;
	//z axis for rotation
	ICM20948_readGyroscope_Z(i2cHandlePtr, ICM20948_I2C_ADDR, Gyroscope, &gyroZValue);
	sensorDataPtr->zAxisGyro = (gyroZValue - sensorDataPtr->zAxisGyroBias) / 1000; //convert to ms
}

void fetchAccelReadings() {
	float accelValue[3];
	ICM20948_readAccelerometer_all(i2cHandlePtr, ICM20948_I2C_ADDR, Accelerometer, accelValue);
	for (int i = 0; i < 3; i++) {
		sensorDataPtr->accelReadings[i] = (accelValue[i] - sensorDataPtr->accelerationBias[i]) * GRAVITATIONAL_CONSTANT; //multiplying by GRAVITY converts these readings to m/s².
	}
}

void calculatedirection(float timeElapsedMs, float zAxisGyro) {
	sensorDataPtr->direction = computeAngularDifference(angle_get(timeElapsedMs, zAxisGyro, ReadMagnetometerAngle()), sensorDataPtr->direction_bias);
}

void calibrateSensorBias(uint16_t numSamples) {

	float sumGyrozAxis = 0, currentGyroZ = 0, accumulatedAccel[3] = {0}, currentAccel[3];

	for (uint16_t a = 0; a < numSamples; a++) {
		ICM20948_readGyroscope_Z(i2cHandlePtr, ICM20948_I2C_ADDR, Gyroscope, &currentGyroZ); //gyroscope bias
		sumGyrozAxis += currentGyroZ;

		ICM20948_readAccelerometer_all(i2cHandlePtr, ICM20948_I2C_ADDR, Accelerometer, currentAccel); //accelerometer bias
		for (uint16_t b = 0; b < 3; b++)
		{
			accumulatedAccel[b] += currentAccel[b];
		}
	}

	sensorDataPtr->zAxisGyroBias = sumGyrozAxis / numSamples;

	for (uint16_t c = 0; c < 3; c++) {
		sensorDataPtr->accelerationBias[c] = accumulatedAccel[c] / numSamples;
	}
	//when robot is stationary, z axis should be equal to gravity
	sensorDataPtr->accelerationBias[2] -= GRAVITATIONAL_CONSTANT; //normally z accelerometer should read gravity.
}
