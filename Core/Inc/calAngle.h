#ifndef INC_CALANGLE_H_
#define INC_CALANGLE_H_
#include "calc_conversions.h"
#include "kalmanFilter.h"

#define CAL_ANGLE_S_W 14.0f
#define CAL_ANGLE_S_HEADING 9.0f

void cal_angle_init(float direction);
void cal_angle_reset(float direction);
float cal_angle_get(float timeElapsed, float w, float direction);

#endif /* INC_CALANGLE_H_ */
