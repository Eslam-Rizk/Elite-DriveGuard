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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LDR_Sensor_Pin GPIO_PIN_0
#define LDR_Sensor_GPIO_Port GPIOA
#define Buzzer_Pin GPIO_PIN_1
#define Buzzer_GPIO_Port GPIOA
#define Ultrasonic_TX_Pin GPIO_PIN_2
#define Ultrasonic_TX_GPIO_Port GPIOA
#define Ultrasonix_RX_Pin GPIO_PIN_3
#define Ultrasonix_RX_GPIO_Port GPIOA
#define Motor_PWM1_Pin GPIO_PIN_6
#define Motor_PWM1_GPIO_Port GPIOA
#define Motor_PWM2_Pin GPIO_PIN_7
#define Motor_PWM2_GPIO_Port GPIOA
#define Right_IR_Pin GPIO_PIN_0
#define Right_IR_GPIO_Port GPIOB
#define Left_IR_Pin GPIO_PIN_1
#define Left_IR_GPIO_Port GPIOB
#define Red_Led_Pin GPIO_PIN_2
#define Red_Led_GPIO_Port GPIOB
#define Motor1_2_PIN1_Pin GPIO_PIN_12
#define Motor1_2_PIN1_GPIO_Port GPIOB
#define Motor1_2_PIN2_Pin GPIO_PIN_13
#define Motor1_2_PIN2_GPIO_Port GPIOB
#define Motor3_4_PIN1_Pin GPIO_PIN_14
#define Motor3_4_PIN1_GPIO_Port GPIOB
#define Motor3_4_PIN2_Pin GPIO_PIN_15
#define Motor3_4_PIN2_GPIO_Port GPIOB
#define Raspberry_TX_Pin GPIO_PIN_9
#define Raspberry_TX_GPIO_Port GPIOA
#define Raspberry_RX_Pin GPIO_PIN_10
#define Raspberry_RX_GPIO_Port GPIOA
#define Bluetooth_TX_Pin GPIO_PIN_11
#define Bluetooth_TX_GPIO_Port GPIOA
#define Bluetooth_RX_Pin GPIO_PIN_12
#define Bluetooth_RX_GPIO_Port GPIOA
#define Head_Led_Pin GPIO_PIN_6
#define Head_Led_GPIO_Port GPIOB
#define Update_LED_Pin GPIO_PIN_8
#define Update_LED_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
