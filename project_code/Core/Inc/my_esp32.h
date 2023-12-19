/*
 * my_esp32.h
 *
 *  Created on: Dec 19, 2023
 *      Author: HP
 */

#ifndef INC_MY_ESP32_H_
#define INC_MY_ESP32_H_

#include"my_define.h"
#include "my_uart.h"

void esp32_init(void);
void esp32_send_sleep(uint32_t sleep_period);
void esp32_send_people(uint8_t people_cnt);
bool esp32_get_flag(void);
void esp32_reset_flag(void);
void esp32_send_lock(bool lock_status);
void esp32_send_fingerID(uint16_t fingerID);
void esp32_receive_data(uint8_t uart_data3);
void esp32_led_off(void);
void esp32_led_on(void);
#endif /* INC_MY_ESP32_H_ */
