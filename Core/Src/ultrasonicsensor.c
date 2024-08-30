#include "ultrasonicsensor.h"

static TIM_HandleTypeDef *htim;

void initializeUltrasonicSensor(TIM_HandleTypeDef *ultrasonicTim) {
	htim = ultrasonicTim;
	HAL_TIM_Base_Start(htim);
}

void UltrasonicSensor_delay(uint16_t ultrasonicsensor) {
	__HAL_TIM_SET_COUNTER(htim, 0);

	while (__HAL_TIM_GET_COUNTER(htim) < ultrasonicsensor);
}
