/*
 * fsm.c
 *
 *  Created on: Oct 6, 2023
 *      Author: HP
 */

#include "fsm.h"
s_timer timer;
void my_intial(state *st) {
	init_timer(&timer, FREQ);
	set_timer(&timer, 2000);
	st = led_on;
}
void fsm_control(state *st) {
	switch (*st) {
	case led_on:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
		if (!timer.st) {
			*st = led_off;
			set_timer(&timer, TOGGLE_TIME);
		}
		break;
	case led_off:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
		if (!timer.st) {
			*st = led_on;
			set_timer(&timer, TOGGLE_TIME);
		}
		break;
	default:
		break;
	}
}
