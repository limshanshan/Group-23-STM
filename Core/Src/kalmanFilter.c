#include "kalmanFilter.h"

void kalmanFilter_init(KalmanFilterParams *params, float start_est, float s_est, float s_mean){
	params->latest_est = start_est;
	params->s_est = s_est;
	params->s_mean = s_mean;
}

void kalmanFilter_update(KalmanFilterParams *params, float estimate, float mean){
	//calculate Kalman gain.
	float G = (params->s_est) / (params->s_est + params->s_mean);

	//update estimate.
	params->latest_est += G * (mean - estimate);
}
