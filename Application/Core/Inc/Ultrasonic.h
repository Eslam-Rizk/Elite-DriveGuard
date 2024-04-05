/*
 * @file Ultrasonic.h
 * @brief Source file for the (HC-SR401) Ultrasonic sensor.
 * @Author: EliteDriveGuard Team
 * @Created on: 25-1-2024
 * This file provides the interfaces for the HC-SR401 Ultrasonic sensor functions.
 */

#ifndef INC_ULTRASONIC_H_
#define INC_ULTRASONIC_H_


/**
  * @brief  Get the distance measured by the HC-SR401 ultrasonic sensor.
  * @param  None
  * @retval The distance value
  */
uint16_t Ultrasonic_u16GetDistance(void);


#endif /* INC_ULTRASONIC_H_ */
