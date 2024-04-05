/*
 * LDW.c
 *** LDW (Lane Keeping System)
 *  Created on: Feb 25, 2024
 *      Author: MohamedAmmar
 */

#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "LKS.h"
#include  "Motor.h"


volatile uint8_t left_IR = 0, right_IR = 0;


void LaneKeepingSystem(void) {
	// Read left and right IR sensor values
	left_IR = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1);
	right_IR = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0);


	/* If the car is inside the lane / No lane markings are detected on both sides */
	if (left_IR == BLACK && right_IR == BLACK)
	{
		/* Move the car forward  */
		MotorDriver_voidMoveForward();
	}
	/* If the car drifts to the right / Lane markings are detected on the right side */
	else if (left_IR == BLACK && right_IR == WHITE)
	{
		// Steer the car to the left
		MotorDriver_voidMoveLeft();
		while(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0));
	}
	/* If the car drifts to the left / Lane markings are detected on the left side */
	else if (left_IR == WHITE && right_IR == BLACK)
	{
		// Steer the car to the right
		MotorDriver_voidMoveRight();
		while(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1));
	} else
	{
		// Stop the car
		MotorDriver_voidStop();
		while(!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)));
	}





}
