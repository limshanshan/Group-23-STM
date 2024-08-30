/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define OLED_SCLK_Pin GPIO_PIN_5
#define OLED_SCLK_GPIO_Port GPIOE
#define OLED_SDIN_Pin GPIO_PIN_6
#define OLED_SDIN_GPIO_Port GPIOE
#define Right_IR_V0_Pin GPIO_PIN_2
#define Right_IR_V0_GPIO_Port GPIOC
#define Left_IR_V0_Pin GPIO_PIN_3
#define Left_IR_V0_GPIO_Port GPIOC
#define MotorA_AIN2_Pin GPIO_PIN_2
#define MotorA_AIN2_GPIO_Port GPIOA
#define MotorA_AIN1_Pin GPIO_PIN_3
#define MotorA_AIN1_GPIO_Port GPIOA
#define MotorrB_AIN1_Pin GPIO_PIN_4
#define MotorrB_AIN1_GPIO_Port GPIOA
#define MotorB_AIN2_Pin GPIO_PIN_5
#define MotorB_AIN2_GPIO_Port GPIOA
#define MotorB_CH1_Pin GPIO_PIN_6
#define MotorB_CH1_GPIO_Port GPIOA
#define MotorB_CH2_Pin GPIO_PIN_7
#define MotorB_CH2_GPIO_Port GPIOA
#define OLED_RESET__Pin GPIO_PIN_7
#define OLED_RESET__GPIO_Port GPIOE
#define OLED_DATA_COMMAND__Pin GPIO_PIN_8
#define OLED_DATA_COMMAND__GPIO_Port GPIOE
#define SERVO_PWM_Pin GPIO_PIN_9
#define SERVO_PWM_GPIO_Port GPIOE
#define User_Button_Pin GPIO_PIN_8
#define User_Button_GPIO_Port GPIOD
#define MotorA_PWMA_Pin GPIO_PIN_6
#define MotorA_PWMA_GPIO_Port GPIOC
#define MotorB_PWMB_Pin GPIO_PIN_7
#define MotorB_PWMB_GPIO_Port GPIOC
#define MotorA_CH1_Pin GPIO_PIN_15
#define MotorA_CH1_GPIO_Port GPIOA
#define US_Trigger_Pin GPIO_PIN_7
#define US_Trigger_GPIO_Port GPIOD
#define MotorA_CH2_Pin GPIO_PIN_3
#define MotorA_CH2_GPIO_Port GPIOB
#define ICM_SCL_Pin GPIO_PIN_8
#define ICM_SCL_GPIO_Port GPIOB
#define ICM_SDA_Pin GPIO_PIN_9
#define ICM_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
