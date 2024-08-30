
#ifndef INC_ULTRASONICSENSOR_H_
#define INC_ULTRASONICSENSOR_H_
#include "main.h"

void initializeUltrasonicSensor(TIM_HandleTypeDef *ultrasonicTim);
void UltrasonicSensor_delay(uint16_t ultrasonicsensor);

#endif /* INC_ULTRASONICSENSOR_H_ */
