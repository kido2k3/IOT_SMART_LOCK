/*
 * my_uart.h
 *
 *  Created on: Nov 29, 2023
 *      Author: HP
 */

#ifndef INC_MY_UART_H_
#define INC_MY_UART_H_

#include "my_password.h"
#include "my_define.h"

void uart_SendPressedKey(uint8_t key);
void uart_SendInPW(void);
#endif /* INC_MY_UART_H_ */
