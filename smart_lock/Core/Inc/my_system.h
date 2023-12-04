/*
 * my_system.h
 *
 *  Created on: Nov 29, 2023
 *      Author: HP
 */

#ifndef INC_MY_SYSTEM_H_
#define INC_MY_SYSTEM_H_

#include"my_define.h"
#include "my_buzzer.h"
#include "my_fsm.h"
#include "my_scheduler.h"
#include "my_keypad.h"
#include"my_lcd.h"
#include"my_sensor.h"
#include"my_uart.h"
#include "my_lock.h"
void init(void);
void loop(void);
#endif /* INC_MY_SYSTEM_H_ */
