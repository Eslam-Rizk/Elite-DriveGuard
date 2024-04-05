/*
 * ACC.c
 *
 *  Created on: Feb 25, 2024
 *      Author: MohamedAmmar
 */

#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "Motor.h"
#include "Ultrasonic.h"
#include "ACC.h"

#define max_speed 98
#define default_distance 50
#define min_distance 20

void adaptivecruisecontrol(void)
{
	static uint8_t speed = 0;
	static uint8_t start_flag = 0;
	static uint16_t current_distance = 0;

	/* Set motor direction */
	MotorDriver_voidMoveForward();
	if(0 == start_flag )
	{
		for (uint8_t i =0 ; i < max_speed ; i++)
		{
			/* apply new speed (duty cycle) on motors */
			MotorDriver_voidControlSpeed(speed);
		}
		start_flag = 1;
	}
	else
	{
		/* apply new speed (duty cycle) on motors */
		MotorDriver_voidControlSpeed(speed);
	}
	//static u8 max_speed = 80;
	//static u16 default_distance = 25;


	/* measure distance */
	current_distance = Ultrasonic_u16GetDistance();

	if ((current_distance < default_distance) && (current_distance > min_distance))
	{
		/* Calculate Adaptive Speed */
		//speed = ((((max_speed - 50) * current_distance) - (min_distance * max_speed) + 1500) / 20);
		speed = max_speed + 2*(current_distance -50) ;
	}
	else if (current_distance <= min_distance)
	{
		/* very low distance < 20 --> car stop */
		MotorDriver_voidStop();
		speed = 0;
	}
	else if (current_distance >= default_distance)
	{
		speed = max_speed;
	}
	else{/* nothing */}
	/* Update speed based on Ultrasonic reading */
	MotorDriver_voidControlSpeed(speed);
}
