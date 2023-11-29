/*
 * my_keypad.c
 *
 *  Created on: Nov 29, 2023
 *      Author: HP
 */

#include"my_keypad.h"

GPIO_InitTypeDef GPIO_InitStructPrivate = { 0 };
uint32_t previousMillis = 0;
uint32_t currentMillis = 0;
uint8_t keyPressed = UNPRESSED;

static void keypad_scan(uint16_t GPIO_Pin) {
	currentMillis = HAL_GetTick();
	if (currentMillis - previousMillis > 10) {
		/*Configure GPIO pins :  to GPIO_INPUT*/
		GPIO_InitStructPrivate.Pin = KEYPAD_R1_PIN | KEYPAD_R2_PIN
				| KEYPAD_R3_PIN | KEYPAD_R4_PIN;
		GPIO_InitStructPrivate.Mode = GPIO_MODE_INPUT;
		GPIO_InitStructPrivate.Pull = GPIO_PULLUP;
		GPIO_InitStructPrivate.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(KEYPAD_R_PORT, &GPIO_InitStructPrivate);

		HAL_GPIO_WritePin(KEYPAD_C_PORT, KEYPAD_C4_PIN, 0);
		HAL_GPIO_WritePin(KEYPAD_C_PORT, KEYPAD_C3_PIN, 1);
		HAL_GPIO_WritePin(KEYPAD_C_PORT, KEYPAD_C2_PIN, 1);
		HAL_GPIO_WritePin(KEYPAD_C_PORT, KEYPAD_C1_PIN, 1);
		if (GPIO_Pin == KEYPAD_R4_PIN
				&& !HAL_GPIO_ReadPin(KEYPAD_R_PORT, KEYPAD_R4_PIN)) {
			keyPressed = 15; //ASCII value of D
		} else if (GPIO_Pin == KEYPAD_R3_PIN
				&& !HAL_GPIO_ReadPin(KEYPAD_R_PORT, KEYPAD_R3_PIN)) {
			keyPressed = 11; //ASCII value of C
		} else if (GPIO_Pin == KEYPAD_R2_PIN
				&& !HAL_GPIO_ReadPin(KEYPAD_R_PORT, KEYPAD_R2_PIN)) {
			keyPressed = 7; //ASCII value of B
		} else if (GPIO_Pin == KEYPAD_R1_PIN
				&& !HAL_GPIO_ReadPin(KEYPAD_R_PORT, KEYPAD_R1_PIN)) {
			keyPressed = 3; //ASCII value of A
		}

		HAL_GPIO_WritePin(KEYPAD_C_PORT, KEYPAD_C4_PIN, 1);
		HAL_GPIO_WritePin(KEYPAD_C_PORT, KEYPAD_C3_PIN, 0);
		HAL_GPIO_WritePin(KEYPAD_C_PORT, KEYPAD_C2_PIN, 1);
		HAL_GPIO_WritePin(KEYPAD_C_PORT, KEYPAD_C1_PIN, 1);
		if (GPIO_Pin == KEYPAD_R4_PIN
				&& !HAL_GPIO_ReadPin(KEYPAD_R_PORT, KEYPAD_R4_PIN)) {
			keyPressed = 14; //ASCII value of #
		} else if (GPIO_Pin == KEYPAD_R3_PIN
				&& !HAL_GPIO_ReadPin(KEYPAD_R_PORT, KEYPAD_R3_PIN)) {
			keyPressed = 10; //ASCII value of 9
		} else if (GPIO_Pin == KEYPAD_R2_PIN
				&& !HAL_GPIO_ReadPin(KEYPAD_R_PORT, KEYPAD_R2_PIN)) {
			keyPressed = 6; //ASCII value of 6
		} else if (GPIO_Pin == KEYPAD_R1_PIN
				&& !HAL_GPIO_ReadPin(KEYPAD_R_PORT, KEYPAD_R1_PIN)) {
			keyPressed = 2; //ASCII value of 3
		}

		HAL_GPIO_WritePin(KEYPAD_C_PORT, KEYPAD_C4_PIN, 1);
		HAL_GPIO_WritePin(KEYPAD_C_PORT, KEYPAD_C3_PIN, 1);
		HAL_GPIO_WritePin(KEYPAD_C_PORT, KEYPAD_C2_PIN, 0);
		HAL_GPIO_WritePin(KEYPAD_C_PORT, KEYPAD_C1_PIN, 1);
		if (GPIO_Pin == KEYPAD_R4_PIN
				&& !HAL_GPIO_ReadPin(KEYPAD_R_PORT, KEYPAD_R4_PIN)) {
			keyPressed = 13; //ASCII value of 0
		} else if (GPIO_Pin == KEYPAD_R3_PIN
				&& !HAL_GPIO_ReadPin(KEYPAD_R_PORT, KEYPAD_R3_PIN)) {
			keyPressed = 9; //ASCII value of 8
		} else if (GPIO_Pin == KEYPAD_R2_PIN
				&& !HAL_GPIO_ReadPin(KEYPAD_R_PORT, KEYPAD_R2_PIN)) {
			keyPressed = 5; //ASCII value of 5
		} else if (GPIO_Pin == KEYPAD_R1_PIN
				&& !HAL_GPIO_ReadPin(KEYPAD_R_PORT, KEYPAD_R1_PIN)) {
			keyPressed = 1; //ASCII value of 2
		}

		HAL_GPIO_WritePin(KEYPAD_C_PORT, KEYPAD_C4_PIN, 1);
		HAL_GPIO_WritePin(KEYPAD_C_PORT, KEYPAD_C3_PIN, 1);
		HAL_GPIO_WritePin(KEYPAD_C_PORT, KEYPAD_C2_PIN, 1);
		HAL_GPIO_WritePin(KEYPAD_C_PORT, KEYPAD_C1_PIN, 0);
		if (GPIO_Pin == KEYPAD_R4_PIN
				&& !HAL_GPIO_ReadPin(KEYPAD_R_PORT, KEYPAD_R4_PIN)) {
			keyPressed = 12; //ASCII value of *
		} else if (GPIO_Pin == KEYPAD_R3_PIN
				&& !HAL_GPIO_ReadPin(KEYPAD_R_PORT, KEYPAD_R3_PIN)) {
			keyPressed = 8; //ASCII value of 7
		} else if (GPIO_Pin == KEYPAD_R2_PIN
				&& !HAL_GPIO_ReadPin(KEYPAD_R_PORT, KEYPAD_R2_PIN)) {
			keyPressed = 4; //ASCII value of 4
		} else if (GPIO_Pin == KEYPAD_R1_PIN
				&& !HAL_GPIO_ReadPin(KEYPAD_R_PORT, KEYPAD_R1_PIN)) {
			keyPressed = 0; //ASCII value of 1
		}

		HAL_GPIO_WritePin(KEYPAD_C_PORT, KEYPAD_C4_PIN, 0);
		HAL_GPIO_WritePin(KEYPAD_C_PORT, KEYPAD_C3_PIN, 0);
		HAL_GPIO_WritePin(KEYPAD_C_PORT, KEYPAD_C2_PIN, 0);
		HAL_GPIO_WritePin(KEYPAD_C_PORT, KEYPAD_C1_PIN, 0);
		/*Configure GPIO pins : back to EXTI*/
		GPIO_InitStructPrivate.Mode = GPIO_MODE_IT_FALLING;
		GPIO_InitStructPrivate.Pull = GPIO_PULLUP;
		HAL_GPIO_Init(KEYPAD_R_PORT, &GPIO_InitStructPrivate);
		previousMillis = currentMillis;
	}
}
void keypad_init(void) {
	HAL_GPIO_WritePin(KEYPAD_C_PORT, KEYPAD_C4_PIN, 0);
	HAL_GPIO_WritePin(KEYPAD_C_PORT, KEYPAD_C3_PIN, 0);
	HAL_GPIO_WritePin(KEYPAD_C_PORT, KEYPAD_C2_PIN, 0);
	HAL_GPIO_WritePin(KEYPAD_C_PORT, KEYPAD_C1_PIN, 0);
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	keypad_scan(GPIO_Pin);
}

