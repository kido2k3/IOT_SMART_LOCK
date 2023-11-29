/*
 * my_define.h
 *
 *  Created on: Nov 29, 2023
 *      Author: HP
 */

#ifndef INC_MY_DEFINE_H_
#define INC_MY_DEFINE_H_
#include"stm32f1xx_hal.h"

#define DEBUG_LED_PORT 	GPIOC
#define DEBUG_LED_PIN 	GPIO_PIN_13

#define KEYPAD_C_PORT	GPIOB
#define KEYPAD_R_PORT	GPIOA
#define KEYPAD_C1_PIN	GPIO_PIN_0
#define KEYPAD_C2_PIN	GPIO_PIN_1
#define KEYPAD_C3_PIN	GPIO_PIN_2
#define KEYPAD_C4_PIN	GPIO_PIN_3
#define KEYPAD_R1_PIN	GPIO_PIN_5
#define KEYPAD_R2_PIN	GPIO_PIN_6
#define KEYPAD_R3_PIN	GPIO_PIN_7
#define KEYPAD_R4_PIN	GPIO_PIN_12


typedef uint8_t bool;

#endif /* INC_MY_DEFINE_H_ */
