/*
 * my_keypad.h
 *
 *  Created on: Nov 29, 2023
 *      Author: HP
 */

#ifndef INC_MY_KEYPAD_H_
#define INC_MY_KEYPAD_H_

#include"my_define.h"

#define UNPRESSED 0xff
extern uint8_t keyPressed;

void keypad_init(void);
#endif /* INC_MY_KEYPAD_H_ */
