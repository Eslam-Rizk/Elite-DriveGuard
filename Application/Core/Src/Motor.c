/**
 * @file Motor.c
 * @brief Source file for the motor driver.
 * @author: EliteDriveGuard Team
 * @Created on: 25-1-2024
 * This file contains the implementation of the motor driver functions.
 */

#include "tim.h"
#include "gpio.h"
#include "Motor.h"


void MotorDriver_voidInit(void)
{
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);	/* Motor1 + Motor2 */
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);   /* Motor3 + Motor4 */
}

void MotorDriver_voidControlSpeed(uint8_t DutyCycle)
{
	htim3.Instance->CCR1 = 99-DutyCycle;		/* Motor1 + Motor2 */
	htim3.Instance->CCR2 = 99-DutyCycle;		/* Motor3 + Motor4 */

	//htim3.Instance->CCR1 = DutyCycle;
	//htim3.Instance->CCR2 = DutyCycle;
}

void MotorDriver_voidStop(void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET); // Motor 1
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET); // Motor 2
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET); // Motor 3
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET); // Motor 4
}

void MotorDriver_voidMoveForward(void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);    // Motor 1
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);  // Motor 2
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);    // Motor 3
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);  // Motor 4
}

void MotorDriver_voidMoveBackward(void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);   // Motor 1
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);     // Motor 2
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);   // Motor 3
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);     // Motor 4
}

void MotorDriver_voidMoveRight(void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);   // Motor 1
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);   // Motor 2
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);     // Motor 3
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);   // Motor 4
}

void MotorDriver_voidMoveLeft(void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);     // Motor 1
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);   // Motor 2
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);   // Motor 3
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);   // Motor 4
}

