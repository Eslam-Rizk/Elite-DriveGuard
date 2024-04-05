/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Ultrasonic.h"
#include "Motor.h"
#include "LDR.h"
#include "tim.h"
#include "usart.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MIN_DISTANCE		10
#define DEFAULT_DISTANCE    50
#define MAX_SPEED  			98

#define WHITE   0
#define BLACK   1
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
uint16_t Current_Distance = 0;
uint8_t Bluetooth_Value = 0;

uint8_t ACC_Flag = 0;
uint8_t Bootloader_Flag = 0;
uint8_t AEB_Flag = 0;
uint8_t LKS_Flag = 0;
uint8_t Left_IR = 0;
uint8_t Right_IR = 0;


/* USER CODE END Variables */
/* Definitions for TASK_1 */
osThreadId_t TASK_1Handle;
const osThreadAttr_t TASK_1_attributes = {
		.name = "TASK_1",
		.stack_size = 128 * 4,
		.priority = (osPriority_t) osPriorityLow1,
};
/* Definitions for TASK_2 */
osThreadId_t TASK_2Handle;
const osThreadAttr_t TASK_2_attributes = {
		.name = "TASK_2",
		.stack_size = 128 * 4,
		.priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for TASK_3 */
osThreadId_t TASK_3Handle;
const osThreadAttr_t TASK_3_attributes = {
		.name = "TASK_3",
		.stack_size = 128 * 4,
		.priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for TASK_4 */
osThreadId_t TASK_4Handle;
const osThreadAttr_t TASK_4_attributes = {
		.name = "TASK_4",
		.stack_size = 128 * 4,
		.priority = (osPriority_t) osPriorityLow,
};
/* Definitions for TASK_5 */
osThreadId_t TASK_5Handle;
const osThreadAttr_t TASK_5_attributes = {
		.name = "TASK_5",
		.stack_size = 128 * 4,
		.priority = (osPriority_t) osPriorityLow,
};
/* Definitions for TASK_6 */
osThreadId_t TASK_6Handle;
const osThreadAttr_t TASK_6_attributes = {
		.name = "TASK_6",
		.stack_size = 128 * 4,
		.priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void ACC_TASK(void *argument);
void AEB_TASK(void *argument);
void LKS_Task(void *argument);
void ALC_TASK(void *argument);
void Bluetooth_Task(void *argument);
void FOTA_Task(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void) {
	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
	/* USER CODE END RTOS_MUTEX */

	/* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
	/* USER CODE END RTOS_SEMAPHORES */

	/* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
	/* USER CODE END RTOS_TIMERS */

	/* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
	/* USER CODE END RTOS_QUEUES */

	/* Create the thread(s) */
	/* creation of TASK_1 */
	TASK_1Handle = osThreadNew(ACC_TASK, NULL, &TASK_1_attributes);

	/* creation of TASK_2 */
	TASK_2Handle = osThreadNew(AEB_TASK, NULL, &TASK_2_attributes);

	/* creation of TASK_3 */
	TASK_3Handle = osThreadNew(LKS_Task, NULL, &TASK_3_attributes);

	/* creation of TASK_4 */
	TASK_4Handle = osThreadNew(ALC_TASK, NULL, &TASK_4_attributes);

	/* creation of TASK_5 */
	TASK_5Handle = osThreadNew(Bluetooth_Task, NULL, &TASK_5_attributes);

	/* creation of TASK_6 */
	TASK_6Handle = osThreadNew(FOTA_Task, NULL, &TASK_6_attributes);

	/* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
	/* USER CODE END RTOS_THREADS */

	/* USER CODE BEGIN RTOS_EVENTS */
	/* add events, ... */
	/* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_ACC_TASK (Adaptive Cruise Control) */
/**
 * @brief  Function implementing the TASK_1 thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_ACC_TASK */
void ACC_TASK(void *argument)
{
	/* USER CODE BEGIN ACC_TASK */
	static uint8_t speed = 0;

	/* Infinite loop */
	for(;;)
	{
		if((!AEB_Flag) && (!LKS_Flag) && (ACC_Flag))
		{

			//Current_Distance = Ultrasonic_u16GetDistance();
			/* Reset speed for safty*/
			speed = 0 ;
			/* Set motor direction */
			MotorDriver_voidMoveForward();

			if ((Current_Distance < DEFAULT_DISTANCE) && (Current_Distance > MIN_DISTANCE))
			{
				/* Calculate Adaptive Speed */
				speed = MAX_SPEED - 2*(DEFAULT_DISTANCE - Current_Distance) ;
			}
			else if (Current_Distance >= DEFAULT_DISTANCE)
			{
				speed = MAX_SPEED ;
			}
			else{/* nothing */}
			/* Update speed based on Ultrasonic reading */
			MotorDriver_voidControlSpeed(speed);

		}
		else{/* Nothing */}

		osDelay(1);
	}
	/* USER CODE END ACC_TASK */
}

/* USER CODE BEGIN Header_AEB_TASK (Automatic Emergency Braking) */
/**
 * @brief Function implementing the TASK_2 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_AEB_TASK */
void AEB_TASK(void *argument)
{
	/* USER CODE BEGIN AEB_TASK */
	/* Infinite loop */
	for(;;)
	{
		/* Measure distance */
		Current_Distance = Ultrasonic_u16GetDistance();
		/* Read Left IR Value (BLACK/WHITE) */
		Left_IR = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1);
		/* Read Right IR Value (BLACK/WHITE) */
		Right_IR = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0);

		if ((Current_Distance <= MIN_DISTANCE)||(Left_IR == WHITE && Right_IR == WHITE))
		{
			/* very low distance < 10 --> car stop */
			MotorDriver_voidStop();
			/* Set (Automatic Emergency Braking) Flag */
			AEB_Flag = 1;
			/* Stop the car */
			MotorDriver_voidControlSpeed(0);
			/* Turn On Back Leds  */
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
			/* Turn On Buzzer */
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
			/* Wait Task for 3 Sec*/
			vTaskDelay(3000);
			/* Turn On Buzzer  */
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
			/* Turn On Back Leds  */
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
		}
		else
		{
			AEB_Flag = 0;
		}

		osDelay(1);
	}
	/* USER CODE END AEB_TASK */
}

/* USER CODE BEGIN Header_LKS_Task (Lane Keeping Status ) */
/**
 * @brief Function implementing the TASK_3 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_LKS_Task */
void LKS_Task(void *argument)
{
	/* USER CODE BEGIN LKS_Task */

	/* Infinite loop */
	for(;;)
	{
		if(!AEB_Flag)
		{
			/* If the car is inside the lane / No lane markings are detected on both sides */
			if ((Left_IR == BLACK) && (Right_IR == BLACK) && (ACC_Flag))
			{

				/* Move the car forward  */
				MotorDriver_voidMoveForward();
				/* Reset (Lane Keeping Status) Flag */
				LKS_Flag = 0;
			}
			/* If the car drifts to the right / Lane markings are detected on the right side */
			else if (Left_IR == BLACK && Right_IR == WHITE)
			{
				/* Set (Lane Keeping Status) Flag */
				LKS_Flag = 1;
				// Steer the car to the left
				MotorDriver_voidMoveLeft();
			}
			/* If the car drifts to the left / Lane markings are detected on the left side */
			else if (Left_IR == WHITE && Right_IR == BLACK)
			{
				/* Set (Lane Keeping Status) Flag */
				LKS_Flag = 1;
				// Steer the car to the right
				MotorDriver_voidMoveRight();
			}
			else
			{/* Nothing */}

		}
		else {/* Nothing */}
		osDelay(1);
	}
	/* USER CODE END LKS_Task */
}

/* USER CODE BEGIN Header_ALC_TASK ( Adaptive Light Control )*/
/**
 * @brief Function implementing the TASK_4 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_ALC_TASK */
void ALC_TASK(void *argument)
{
	/* USER CODE BEGIN ALC_TASK */
	uint8_t LDR_Value = 0;

	/* Infinite loop */
	for(;;)
	{

		/* Read LDR Value */
		LDR_Value = LDR_u8GetValue();
		if(LDR_Value >= 93)
		{
			/* Head Lead with Max lighting */
			htim4.Instance->CCR1 = 98 ;
		}
		else if(LDR_Value < 93 || LDR_Value >= 80)
		{
			/* Head Led with adaptive lighting*/
			htim4.Instance->CCR1 =  (LDR_Value )  ;
		}
		else if(LDR_Value < 80 || LDR_Value > 10)
		{
			/* Head Led with Low lighting */
			htim4.Instance->CCR1 =  (LDR_Value ) / 2 ;
		}
		else
		{
			/* Head Led Off*/
			htim4.Instance->CCR1 =  0 ;
		}
		/* Task will come in every 1 msec */
		osDelay(1);
	}
	/* USER CODE END ALC_TASK */
}

/* USER CODE BEGIN Header_Bluetooth_Task */
/**
 * @brief Function implementing the TASK_5 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_Bluetooth_Task */
void Bluetooth_Task(void *argument)
{
	/* USER CODE BEGIN Bluetooth_Task */
	uint8_t Speed = 0 ;
	/* Infinite loop */
	for(;;)
	{
		if(!AEB_Flag && !LKS_Flag)
		{
			if(Current_Distance < 100)
			{
				Speed = (uint8_t)Current_Distance;
			}
			else
			{
				Speed = 90 ;
			}
			HAL_StatusTypeDef Status = HAL_ERROR;
			/* Receive from Bluetooth*/
			Status = HAL_UART_Receive(&huart6, &Bluetooth_Value, sizeof(uint8_t), 50);
			if(HAL_OK == Status)
			{
				if(!ACC_Flag)
				{
					switch(Bluetooth_Value)
					{
					case 'J' :	/* Bluetooth send 'J' */
						ACC_Flag = 1;
						Bootloader_Flag = 0;
						break;
					case 'F' :	/* Bluetooth send 'F' */
						MotorDriver_voidMoveForward();
						MotorDriver_voidControlSpeed(Speed);
						Bootloader_Flag = 0;
						break;
					case 'L' :	/* Bluetooth send 'L' */
						MotorDriver_voidMoveLeft();
						MotorDriver_voidControlSpeed(Speed);
						Bootloader_Flag = 0;
						break;
					case 'R' :	/* Bluetooth send 'R' */
						MotorDriver_voidMoveRight();
						MotorDriver_voidControlSpeed(Speed);
						Bootloader_Flag = 0;
						break;
					case 'S' :	/* Bluetooth send 'S' */
						MotorDriver_voidStop();
						Bootloader_Flag = 0;
						break;
					case 'B' :	/* Bluetooth send 'B' */
						Bootloader_Flag = 1;
						break;
					default :
						Status = HAL_ERROR;
						break;
					}
				}
				else
				{
					/* Bluetooth send 'H' */
					if(Bluetooth_Value == 'H')
					{
						ACC_Flag = 0;
						Bootloader_Flag = 0;
					}
					else
					{/* Nothing */}

				}
			}
		}
		/* Task will come in every 1 msec */
		osDelay(1);
	}
	/* USER CODE END Bluetooth_Task */
}

/* USER CODE BEGIN Header_FOTA_Task */
/**
 * @brief Function implementing the TASK_6 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_FOTA_Task */
void FOTA_Task(void *argument)
{
	/* USER CODE BEGIN FOTA_Task */
	uint8_t Fota_Value = 0;
	uint8_t RaspberrySendValue = 7;
	/* Infinite loop */
	for(;;)
	{
		/* Receive from Raspberry PI*/
		HAL_UART_Receive(&huart1, &Fota_Value, sizeof(uint8_t), 100);
		//if((Fota_Value == 55) || (Fota_Value == '55') || (Fota_Value == 0x55) || (Fota_Value == '0x55') || (Fota_Value == '7') || (Fota_Value == 7))
		if((Fota_Value == '7') || (Fota_Value == 55))
		{
			/* Set the update led */
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
			if(1 == Bootloader_Flag)
			{
				/* Send By Bluetooth (7) to raspberry pi */
				HAL_UART_Transmit(&huart1, &RaspberrySendValue, sizeof(uint8_t), 100);
				/* Software Reset to starting the update */
				HAL_NVIC_SystemReset();
			}
			else{/*Nothing*/}
		}
		osDelay(1);
	}
	/* USER CODE END FOTA_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

