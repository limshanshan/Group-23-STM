#include "calAngle.h"

static KalmanFilterParams kfParams;

void cal_angle_init(float direction) {
	cal_angle_reset(direction);
}

void cal_angle_reset(float direction) {
	kalmanFilter_init(&kfParams, direction, CAL_ANGLE_S_W, CAL_ANGLE_S_HEADING);
}
float cal_angle_get(float timeElapsed, float w, float direction) {
	float angle_w = adjust_angle(kfParams.latest_est, w * timeElapsed);

	kfParams.s_est += timeElapsed * timeElapsed * CAL_ANGLE_S_W;
	kalmanFilter_update(&kfParams, angle_w, direction);

	if ((angle_w < -90 && (direction - angle_w) > 180) || (direction < -90 && (angle_w - direction) > 180)) {
		//detect discontinuous wrapping; adjust accordingly.
		kfParams.latest_est = adjust_angle(kfParams.latest_est, 180);
	}
	return kfParams.latest_est;
}
