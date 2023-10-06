/*
 * fsm.h
 *
 *  Created on: Oct 6, 2023
 *      Author: HP
 */

#ifndef INC_FSM_H_
#define INC_FSM_H_

#include "software_timer.h"
#include "main.h"

#define FREQ 2000 // frequency of system is 2kHz
extern s_timer timer;// timer of system

#define TOGGLE_TIME 2000
typedef enum {led_on, led_off} state;


void my_intial(state*st);
void fsm_control(state*st);
#endif /* INC_FSM_H_ */
