/*
 * my_uart.c
 *
 *  Created on: Nov 29, 2023
 *      Author: HP
 */

#include"my_uart.h"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
static uint8_t uart_data1;
static uint8_t uart_data3;
void uart_fp_init(void) {
	HAL_UART_Receive_IT(&huart1, &uart_data1, 1);
}

void uart_esp32_init(void) {
	HAL_UART_Receive_IT(&huart3, &uart_data3, 1);
}
void uart_SendInPW(void) {
	char str[30];
	uint8_t len = sprintf(str, "#InPW:%s!\n", pw_ReturnInput());
	HAL_UART_Transmit(&huart2, (void*) str, len, 10);
}

void uart_SendPressedKey(uint8_t key) {
	char str[30];
	uint8_t len = sprintf(str, "#Key:%u!\n", key);
	HAL_UART_Transmit(&huart2, (void*) str, len, 10);
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart->Instance == huart1.Instance) {
		fp_receive_data(uart_data1);
		HAL_UART_Receive_IT(&huart1, &uart_data1, 1);
	} else if (huart3.Instance) {
		esp32_receive_data(uart_data3);
		HAL_UART_Receive_IT(&huart3, &uart_data3, 1);
	}

}
