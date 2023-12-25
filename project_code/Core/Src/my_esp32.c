/*
 * my_esp32.c
 *
 *  Created on: Dec 19, 2023
 *      Author: HP
 */

#include"my_esp32.h"

extern UART_HandleTypeDef huart3;
#define LOCK_CMD	"LOCK:0#"
#define ESP_BUF_MAX	14
static uint8_t esp32_buffer[ESP_BUF_MAX];
static uint8_t esp32_idx = 0;
static bool esp32_flag = 0;
void esp32_init(void) {
	uart_esp32_init();
	esp32_send_lock(1);
}

void esp32_receive_data(uint8_t uart_data3) {
	esp32_buffer[esp32_idx++] = uart_data3;
	if (strstr((char*)esp32_buffer,LOCK_CMD)) {
		esp32_flag = 1;
		esp32_idx = 0;
		return;
	}
	if(esp32_buffer[esp32_idx-1]=='#'){
		esp32_idx = 0;
		return;
	}
	if (esp32_idx >= ESP_BUF_MAX) {
		esp32_idx = 0;
	}
}
bool esp32_get_flag(void) {
	return esp32_flag;
}
void esp32_reset_flag(void) {
	esp32_flag = 0;
}
void esp32_send_lock(bool lock_status) {
	if (lock_status) {
		char str[10];
		uint8_t len = sprintf(str, "LOCK:1#");
		HAL_UART_Transmit(&huart3, (void*) str, len, 100);
	} else {
		char str[10];
		uint8_t len = sprintf(str, "LOCK:0#");
		HAL_UART_Transmit(&huart3, (void*) str, len, 100);
	}
}
void esp32_led_on(void) {
	char str[10];
	uint8_t len = sprintf(str, "LED:1#");
	HAL_UART_Transmit(&huart3, (void*) str, len, 100);
}
void esp32_led_off(void) {
	char str[10];
	uint8_t len = sprintf(str, "LED:0#");
	HAL_UART_Transmit(&huart3, (void*) str, len, 100);
}
void esp32_send_people(uint8_t people_cnt) {
	char str[10];
	uint8_t len = sprintf(str, "PEO:%d#", people_cnt);
	HAL_UART_Transmit(&huart3, (void*) str, len, 100);
}
void esp32_send_fingerID(uint16_t fingerID) {
	char str[10];
	uint8_t len = sprintf(str, "ID:%d#", fingerID);
	HAL_UART_Transmit(&huart3, (void*) str, len, 100);
}
void esp32_send_sleep(uint32_t sleep_period) {
	char str[10];
	uint8_t len = sprintf(str, "SLP:%lu#", sleep_period);
	HAL_UART_Transmit(&huart3, (void*) str, len, 100);
}
