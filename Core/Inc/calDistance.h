#ifndef INC_CALDISTANCE_H_
#define INC_CALDISTANCE_H_

#include "kalmanFilter.h"

#define ACCEL_CM_CONVERSION_FACTOR 9.80665e-6f
#define MOTOR_DIST_SCALING_FACTOR 0.75f

//accurate range of IR sensor.
#define DIST_IRSENSOR_MIN 10.0f //6.0f
#define DIST_IRSENSOR_MAX 80.0f //70.0f
#define DIST_IRSENSOR_OFFSET 4.5f //distance from front of vehicle

typedef struct {
  float distance;
  float velocity;
  float velocityUncertainty;
} distanceSetting;

void distance_initialization();
void distance_reset(float velocity);
float distance_in_cm(float timeElapsedMs, float acceleration, float Distance);

#endif /* INC_CALDISTANCE_H_ */
