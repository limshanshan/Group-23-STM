#ifndef INC_CALC_CONVERSIONS_H_
#define INC_CALC_CONVERSIONS_H_
#include <stdint.h>
#include <math.h>
#include "leftrightmotor.h"
#include "sensorstuff.h"
#define VEHICLE_FRAME 15.0f
#define FRONT_AXLE_DISTANCE_CM 16.5f
#define ENCODER_PULSES_PER_REVOLUTION 1535
#define WHEEL_RADIUS_CM 3.25f

float absolute_float(float num);
float min_value_float(float num1, float num2);
float squaredValue(float value);
float Euclid_dist(float xaxis1, float xaxis2, float yaxis1, float yaxis2);
uint8_t min_value_int(uint8_t num1, uint8_t num2);
uint8_t max_value_int(uint8_t num1, uint8_t num2);
uint8_t lcm(uint8_t num1, uint8_t num2);
int16_t absolute_int(int16_t value) ;
uint16_t convertToUint16(char *inputBuffer, uint16_t bufferSize);
uint16_t extract_int(uint8_t **inputBuffer, uint8_t terminator, uint8_t size);
float extract_float(uint8_t **inputBuffer, uint8_t terminator, uint8_t size);
float computeTurningRadiusRobot(float angle);
float computeTurningRadiusBack(float angle);
float computeTurningRadiusRobot(float angle);
float AngluVelo(float speed, float turningRadius);
float Computegyro(float gyroscope);
float adjust_angle(float currentAngle, float angleChange) ;
float computeAngularDifference(float angle1, float angle2);
float directionalAngleDifference(float angle1, float angle2, int8_t direction);


#endif /* INC_CALC_CONVERSIONS_H_ */
