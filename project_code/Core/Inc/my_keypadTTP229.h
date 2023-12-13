/*
 * my_keypad.h
 *
 *  Created on: Nov 29, 2023
 *      Author: HP
 */

#ifndef INC_MY_KEYPADTTP229_H_
#define INC_MY_KEYPADTTP229_H_

#include"my_define.h"
#include "my_lcd.h"

#define UNPRESSED	0xff

void keypad_init(void);
void keypad_read(void);
uint8_t keypad_IsPressed(void);
void keypad_ResetFlag(uint8_t id);
#endif /* INC_MY_KEYPADTTP229_H_ */
