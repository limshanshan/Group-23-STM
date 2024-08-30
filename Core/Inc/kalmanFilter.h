#ifndef INC_KALMANFILTER_H_
#define INC_KALMANFILTER_H_

typedef struct {
	float latest_est;
	float s_est;
	float s_mean;
} KalmanFilterParams;

void kalmanFilter_init(KalmanFilterParams *params, float start_est, float s_est, float s_mean);
void kalmanFilter_update(KalmanFilterParams *params, float estimate, float mean);

#endif /* INC_KALMANFILTER_H_ */
