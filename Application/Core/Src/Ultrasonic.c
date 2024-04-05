/*
 * @file Ultrasonic.c
 * @brief Source file for the HC-SR04 ultrasonic sensor.
 * @author: EliteDriveGuard Team
 * @Created on: 25-1-2024
 * This file provides the implementation of the HC-SR04 ultrasonic sensor functions.
 */

#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "Ultrasonic.h"


/**
  * @brief  Get the distance measured by the HC-SR401 ultrasonic sensor.
  * @param  None
  * @retval The distance value
  */
uint16_t Ultrasonic_u16GetDistance(void)
{
	HAL_StatusTypeDef Status1 = HAL_ERROR;

	uint16_t Distance=0;
	uint8_t temp[2]={0};
	uint8_t *ptr1=&temp[0];
	const uint8_t u= 0x55;
	const uint8_t *ptr = &u;

	/*transmit 0x55 to ultrasonic to get distance */
	Status1 = HAL_UART_Transmit(&huart2, ptr, 2, 100);

	if (HAL_OK == Status1)
	{
		for(uint8_t i =0 ; i<2 ;i++)
		{
			/* get 2 bytes of data */
			HAL_UART_Receive(&huart2, ptr1+i, sizeof(uint8_t), 100);
		}
			/*distance = uint16_t data in mm */
			Distance=(uint16_t)temp[1] | ((uint16_t)temp[0])<<8;
			Distance /=10;		/* Distance in CM */
	}
	else
	{
		Status1 = HAL_ERROR;
	}

	return Distance;
}
