#include "display.h"

uint8_t oled_buf[25];

void write_arr(uint8_t x, uint8_t y, uint8_t label, float r[3]) {
	snprintf(oled_buf, 25, "%c%+.3f|%+.3f|%+.3f", label, r[0], r[1], r[2]);
	OLED_ShowString(x, y, oled_buf);
	OLED_Refresh_Gram();
}

void write_motion(float accelxyzaxis[3], float direction, float gyroZaxis) {
	snprintf(oled_buf, 25, "Z%+.3f|%+.3f", direction, gyroZaxis);
	OLED_ShowString(0, 0, oled_buf);

	write_arr(0, 30, 'A', accelxyzaxis);
}

void write_motors(uint16_t leftAngle, uint16_t rightAngle, uint16_t leftPwmVal, uint16_t rightPwmVal, int32_t offset_val) {
	snprintf(oled_buf, 25, "%5i", leftAngle - rightAngle);
	OLED_ShowString(0, 0, oled_buf);
	snprintf(oled_buf, 25, "%5i|%5i", leftPwmVal, rightPwmVal);
	OLED_ShowString(0, 20, oled_buf);
	snprintf(oled_buf, 25, "%10d", offset_val);
	OLED_ShowString(0, 40, oled_buf);
	OLED_Refresh_Gram();
}

void display_init() {
	OLED_Init();
}
