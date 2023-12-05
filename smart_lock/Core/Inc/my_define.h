/*
 * my_define.h
 *
 *  Created on: Nov 29, 2023
 *      Author: HP
 */

#ifndef INC_MY_DEFINE_H_
#define INC_MY_DEFINE_H_
#include"stm32f1xx_hal.h"
#include <string.h>
#include<stdio.h>
#define DEBUG_LED_PORT 	GPIOC
#define DEBUG_LED_PIN 	GPIO_PIN_13

#define KEYPAD_PORT		GPIOB
#define KEYPAD_SCL_PIN	GPIO_PIN_1
#define KEYPAD_SDO_PIN	GPIO_PIN_0

#define BUTTON_PORT		GPIOA
#define BUTTON_PIN		GPIO_PIN_4

#define BUZZER_PORT		GPIOB
#define BUZZER_PIN		GPIO_PIN_10

#define LOCK_PORT		GPIOB
#define LOCK_PIN		GPIO_PIN_11

typedef uint8_t bool;

#endif /* INC_MY_DEFINE_H_ */
