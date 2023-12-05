/*
 * my_uart.c
 *
 *  Created on: Nov 29, 2023
 *      Author: HP
 */

#include"my_uart.h"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

void uart_SendInPW(void) {
	char str[30];
	uint8_t len = sprintf(str,"#InPW:%s!\n",pw_ReturnInput());
	HAL_UART_Transmit(&huart2, (void*)str, len, 10);
}

void uart_SendPressedKey(uint8_t key) {
	char str[30];
	uint8_t len = sprintf(str,"#Key:%u!\n",key);
	HAL_UART_Transmit(&huart2, (void*)str, len, 10);
}
