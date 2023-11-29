/*
 * my_fsm.c
 *
 *  Created on: Nov 29, 2023
 *      Author: HP
 */

#include "my_fsm.h"

enum {
	SLEEP, PASSWORD, WRONG_INPUT, UNLOCK
} st_lock;
inline int cal(int button_id) {
	return button_id / 4 + button_id % 4 + button_id / 4 * 2 + 1;
}
static void fsm_keypad(void) {
	uint8_t button_id = keypad_ReadFlag();
	if (button_id == UNPRESSED)
		return;
	switch (button_id) {
	case 0:
	case 1:
	case 2:
	case 4:
	case 5:
	case 6:
	case 8:
	case 9:
	case 10:
	case 12:
		switch (st_lock) {
		case SLEEP:
			uint8_t number;
			if (button_id == 12) {
				number = 0;
			} else {
				number = cal(button_id);
			}
			pw_update(number);
			st_lock = PASSWORD;
			break;
		default:

		}
		break;
	case 3:
		break;
	case 7:
		break;
	case 11:
		break;
	case 13:
		break;
	case 14:
		break;
	case 15:
		break;
	}
	keypad_ResetFlag();
}
void fsm_lock(void) {
	switch (st_lock) {
	case SLEEP:
		fsm_keypad();
		break;
	case PASSWORD:

		break;
	case WRONG_INPUT:

		break;
	case UNLOCK:

		break;
	}
}


