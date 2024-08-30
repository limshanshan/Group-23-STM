#include "calDistance.h"

static KalmanFilterParams kalmanFilter;
static distanceSetting distance;

void distance_initialization() {
  distance_reset(0);
}

void distance_reset(float velocity){
  kalmanFilter_init(&kalmanFilter, 0,  ACCEL_CM_CONVERSION_FACTOR, MOTOR_DIST_SCALING_FACTOR);
  distance.distance = 0;
  distance.velocity = velocity;
  distance.velocityUncertainty = 0;
}

static void update_distance(float timeElapsedMs, float acceleration) {
  distance.distance += distance.velocity * timeElapsedMs; //Updates the distance by adding the product of velocity and elapsed time.
  distance.velocity += acceleration * timeElapsedMs; //Updates the velocity by adding the product of acceleration and elapsed time

  //update uncertainties.
  kalmanFilter.s_est += timeElapsedMs * timeElapsedMs * distance.velocityUncertainty; //estimate uncertainty based on the time elapsed and the current uncertainty of velocity
  distance.velocityUncertainty += timeElapsedMs * timeElapsedMs * ACCEL_CM_CONVERSION_FACTOR; //Updates the uncertainty in velocity by adding the product of elapsed time squared and the acceleration noise variance.
}

float distance_in_cm(float timeElapsedMs, float acceleration, float Distance) {
  //get raw estimate, and update uncertainty.
  update_distance(timeElapsedMs, acceleration);

  //get improved estimate.
  kalmanFilter_update(&kalmanFilter, distance.distance, Distance);
  distance.distance = kalmanFilter.latest_est;

  return distance.distance;
}
