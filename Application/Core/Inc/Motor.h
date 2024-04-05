/**
 * @file Motor.c
 * @brief Source file for the motor driver.
 * @author: EliteDriveGuard Team
 * @Created on: 25-1-2024
 * This file contains the function prototypes for controlling the motor driver.
 */


#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_



/**
  * @brief  Initializes pins of motor driver.
  * @param  None
  * @retval None
  */
void MotorDriver_voidInit(void);
/**
  * @brief  Initialize dutycycles of motors.
  * @param  DutyCycle value of dutycycle (0-->100) for PWM signal
  * @retval None
  */
void MotorDriver_voidControlSpeed(uint8_t DutyCycle);
/**
  * @brief  Move motor forward
  * @param  DutyCycle value of dutycycle (0-->100) for PWM signal
  * @retval None
  */
void MotorDriver_voidMoveForward(void);
/**
  * @brief  Move motor backward.
  * @param  DutyCycle value of dutycycle (0-->100) for PWM signal
  * @retval None
  */
void MotorDriver_voidMoveBackward(void);
/**
  * @brief  Move motor Right.
  * @param  DutyCycle value of dutycycle (0-->100) for PWM signal
  * @retval None
  */
void MotorDriver_voidMoveRight(void);
/**
  * @brief  Move motor Left.
  * @param  DutyCycle value of dutycycle (0-->100) for PWM signal
  * @retval None
  */
void MotorDriver_voidMoveLeft(void);
/**
  * @brief  Stop motor
  * @param  DutyCycle value of dutycycle (0-->100) for PWM signal
  * @retval None
  */

void MotorDriver_voidStop(void);


#endif /* INC_MOTOR_H_ */
