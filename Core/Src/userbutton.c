#include <userbutton.h>

uint8_t userbutton_pressed() {
	return HAL_GPIO_ReadPin(User_Button_GPIO_Port, User_Button_Pin) != GPIO_PIN_SET;
}
