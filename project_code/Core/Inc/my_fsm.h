/*
 * my_fsm.h
 *
 *  Created on: Nov 29, 2023
 *      Author: HP
 */

#ifndef INC_MY_FSM_H_
#define INC_MY_FSM_H_

#include <my_sensorHCSR04.h>
#include "my_keypadTTP229.h"
#include"my_define.h"
#include "my_buzzer.h"
#include "my_scheduler.h"
#include"my_lcd.h"
#include"my_uart.h"
#include "my_lock.h"
#include "my_fingerprintAS608.h"
#include "my_button.h"
#include "my_esp32.h"
void fsm_lock(void);
void fsm_sensor(void);

#endif /* INC_MY_FSM_H_ */
