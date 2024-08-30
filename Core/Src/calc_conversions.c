#include "calc_conversions.h"
#define PI 3.14159265358979323846


float absolute_float(float num) {
	if(num<0){
		return -num;
	}
	else{
		return num;
	}
}

float min_value_float(float num1, float num2) {
	if(num1<num2){
		return num1;
	}
	else{
		return num2;
	}
}

float squaredValue(float value) {
	return value * value;
}

float Euclid_dist(float xaxis1, float xaxis2, float yaxis1, float yaxis2) {
	return squaredValue(xaxis1 - xaxis2) + squaredValue(yaxis1 - yaxis2);
}

uint8_t min_value_int(uint8_t num1, uint8_t num2) {
	if(num1<num2){
		return num1;
	}
	else{
		return num2;
	}
}

uint8_t max_value_int(uint8_t num1, uint8_t num2) {
	if(num1>num2){
		return num1;
	}
	else{
		return num2;
	}
}

uint8_t lcm(uint8_t num1, uint8_t num2) {
	uint8_t maxValue= (num1 > num2) ? num1 : num2;

    // While loop to check if max variable
    // is divisible by x and y
    while (maxValue < 255) {
    	if((maxValue % num2 == 0)&&(maxValue % num1 == 0)){
    		return maxValue;
    	}
        ++maxValue;
    }
    return maxValue;
}

int16_t absolute_int(int16_t value) {

	if(value<0){
		return -value;
	}
	else{
		return value;
	}
}

uint16_t convertToUint16(char *inputBuffer, uint16_t bufferSize) {
	uint16_t result  = 0, index  = 0;
	while (index  < bufferSize) {
		uint8_t digit  = *(inputBuffer + index++) - '0';

		if(digit  > 9 || digit  < 0 ){
			break;
		}
		result = result * 10 + digit;
	}
	return result;
}

//get a uint16_t from a string until terminating character.
uint16_t extract_int(uint8_t **inputBuffer, uint8_t terminator, uint8_t size) {
	uint8_t index  = 0, currentChar  = **inputBuffer;
	uint16_t result  = 0;

	while (index  < size && currentChar  != terminator) {

		if(currentChar  >= '0' && currentChar  <= '9'){
			result  = result  * 10 + (currentChar  - '0');
		}
		currentChar  = *(++(*inputBuffer)); index ++;
	}

	return result;
}

//get a float from a string until terminating character.
float extract_float(uint8_t **inputBuffer, uint8_t terminator, uint8_t size) {
	uint8_t index = 0, currentChar = **inputBuffer, fractionFlag  = 0;
	int8_t signMultiplier  = 1;
	uint32_t wholePart  = 0;
	float fractionalPart  = 0, divisor = 0.1;

	while (index < size && currentChar != terminator) {

		if(currentChar == '.'){
			fractionFlag = 1;
		}
		else if(currentChar <= '9' && currentChar >= '0'){
			uint8_t d = currentChar - '0';
			if (fractionFlag) {
				fractionalPart += divisor * d;
				divisor *= 0.1;
			}
			else wholePart = wholePart * 10 + d;
		}
		else if(index == 0 && currentChar == '-'){
			signMultiplier *= -1;
		}

		currentChar = *(++(*inputBuffer));
		index++;
	}

	return signMultiplier* (wholePart + fractionalPart);
}

static float calculateLturning(float Angle) {
	return VEHICLE_FRAME + FRONT_AXLE_DISTANCE_CM / 2 * tan(absolute_float(Angle) * PI / 180);
}

static float computeTurningRadiusFromSteering(float angle) {
	return calculateLturning(angle) / sin(angle * PI / 180);
}

float computeTurningRadiusBack(float angle) {
	return calculateLturning(angle) / tan(angle * PI / 180);
}

float computeTurningRadiusRobot(float angle) {
	float rearTurningRadius  = computeTurningRadiusBack(angle);
	float halfWheelbase  = calculateLturning(angle) / 2;
	float totalTurningRadius  = sqrt(rearTurningRadius * rearTurningRadius + halfWheelbase * halfWheelbase);
	if (angle < 0) {
		totalTurningRadius = -totalTurningRadius;
	}
	return totalTurningRadius;
}

float AngluVelo(float speed, float turningRadius) {
	return speed / turningRadius *  180 / PI;
}

float Computegyro(float gyroscope) {
	return gyroscope;
//	return gyroscope - 0.001;
}

static float normalizeAngle(float angle) {
	while (angle < -180) angle += 360;
	while (angle > 180) angle -= 360;
	return angle;
}

float adjust_angle(float currentAngle, float angleChange) {
	return normalizeAngle(currentAngle + angleChange);
}

float computeAngularDifference(float angle1, float angle2) {
	return normalizeAngle(angle1 - angle2);
}

float directionalAngleDifference(float angle1, float angle2, int8_t direction) {
	float difference = angle1 - angle2;

	if(direction < 0 && difference > 0 ){
		difference -= 360;
	}
	else if(direction > 0 && difference < 0){
		difference += 360;
	}

	return difference;
}

float calDistance(int16_t pulseCount) {
	return ((float) pulseCount) / ENCODER_PULSES_PER_REVOLUTION * 2 * PI * WHEEL_RADIUS_CM;
}

float calculateArcLength(float angle, float radius) {
	return 2 * PI * radius * angle / 360;
}
