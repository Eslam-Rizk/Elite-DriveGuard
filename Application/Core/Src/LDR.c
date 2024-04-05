/**
 * @file LDR.c
 * @brief Source file for the Light Dependent Resistor.
 * @author: EliteDriveGuard Team
 * @Created on: 15-2-2024
 * This file contains the implementation of the Light Dependent Resistor function.
 */

#include "main.h"
#include "adc.h"
#include "gpio.h"
#include "LDR.h"


uint8_t flag = 0;

/**
  * @brief  Get the Value measured by LDR sensor.
  * @param  None
  * @retval The LDR value
  */
uint8_t LDR_u8GetValue(void)
{
	/*HAL_StatusTypeDef status = HAL_ERROR;

	status = HAL_ADC_Start_IT(&hadc1);	//start adc
	if(flag && (HAL_OK == status))
	{
		temp = HAL_ADC_GetValue(&hadc1);	//read ADC value
		value = (temp/4096.0)*100.0;
		flag=0;

	}*/
	uint32_t temp = 0;
	uint8_t value = 0;
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 100);
	temp = HAL_ADC_GetValue(&hadc1);
	value = (temp/4096.0)*100.0;
	return value;
}


