/**
 * @file LDR.c
 * @brief Source file for the Light Dependent Resistor.
 * @author: EliteDriveGuard Team
 * @Created on: 15-2-2024
 * This file contains the function prototypes for the Light Dependent Resistor.
 */

#ifndef INC_LDR_H_
#define INC_LDR_H_


/**
  * @brief  Get the Value measured by LDR sensor.
  * @param  None
  * @retval The LDR value
  */
uint8_t LDR_u8GetValue(void);

#endif /* INC_LDR_H_ */
