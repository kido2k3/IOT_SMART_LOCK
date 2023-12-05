/*
 * my_fsm.c
 *
 *  Created on: Nov 29, 2023
 *      Author: HP
 */

#include "my_fsm.h"

enum {
	INIT, SLEEP, PASSWORD, WRONG, UNLOCK, CHANGE_PASS
} st_lock;

uint8_t cal(uint8_t button_id) {
	return button_id / 4 + button_id % 4 + button_id / 4 * 2 + 1;
}
static void switch_lock_to_unlock(void);
static void switch_lock_to_password(void);
static void switch_lock_to_sleep(void);
static void switch_lock_to_wrong(void);
static void reset_timer(void);
static void run_timer(void);
static bool time_out(void);
static void fsm_keypad(void);

#define TIMER		15 //15s, 5s for testing
#define BLOCK_TIME	5//30s to block keypad and fingerprint
#define UNLOCK_TIME	10

uint16_t timer_for_st = TIMER;
// rise if there was wrong input, if count > 3 block input for 30s
uint8_t wrong_input_cnt = 0;
//
bool wrong_input_flag = 0;
// flag for refill pass. 0: nothing, 1: refill password
bool change_pass_flag = 0;

void fsm_lock(void) {
	switch (st_lock) {
	case INIT:
		switch_lock_to_sleep();
	case SLEEP:
		lock_close();
		fsm_keypad();
		break;
	case PASSWORD:
		// if over 15s not do anything, return to sleep
		if (time_out()) {
			switch_lock_to_sleep();
		}
		fsm_keypad();
		break;
	case CHANGE_PASS:
		// if over 15s not do anything, return to sleep
		if (time_out()) {
			switch_lock_to_sleep();
		}
		fsm_keypad();
		break;
	case WRONG:
		//
		if (wrong_input_cnt > 3) {
			wrong_input_flag = 1;
			timer_for_st = BLOCK_TIME;
			wrong_input_cnt = 0;
		}
		if (time_out()) {
			switch_lock_to_sleep();
		}
		break;
	case UNLOCK:
		lock_open();
		if (time_out()) {
			switch_lock_to_sleep();
		}
		break;
	}
}

static void fsm_keypad(void) {
	uint8_t key_id = keypad_IsPressed();
	switch (key_id) {
	case 0:
	case 1:
	case 2:
	case 4:
	case 5:
	case 6:
	case 8:
	case 9:
	case 10:
	case 13:
		uint8_t number;
		switch (st_lock) {
		case SLEEP:
			if (key_id == 13) {
				number = 0;
			} else {
				number = cal(key_id);
			}
			if (pw_update(number)) {
				switch_lock_to_password();
			}
			break;
		case PASSWORD:
			if (key_id == 13) {
				number = 0;
			} else {
				number = cal(key_id);
			}
			if (pw_update(number)) {
				reset_timer();
				lcd_displayPW();
			} else {
				switch_lock_to_wrong();
			}
			break;
		case CHANGE_PASS:
			if (key_id == 13) {
				number = 0;
			} else {
				number = cal(key_id);
			}
			if (change_pass_flag) {
				if (pw_update_change(number)) {
					reset_timer();
					lcd_displayPW_change();
				}
			} else {
				if (pw_update(number)) {
					reset_timer();
					lcd_displayPW();
				} else {
					switch_lock_to_wrong();
				}
			}
			break;
		default:
			break;
		}
		break;
	case 3:

		break;
	case 7:
		break;

	case 11:
		switch (st_lock) {
		case SLEEP:
			reset_timer();
			LCD_display("FILL OLD PASS", "");
			sch_add_task(run_timer, 0, ONE_SECOND);
			change_pass_flag = 1;
			st_lock = PASSWORD;
			break;
		default:
		}
		break;

	case 12:
		break;

	case 14:
		switch (st_lock) {
		case PASSWORD:
			if (!pw_checkInPW()) {
				switch_lock_to_wrong();
			} else {
				if (change_pass_flag) {
					reset_timer();
					LCD_display("FILL NEW PASS", "");
					pw_ResetIdx();
					st_lock = CHANGE_PASS;
				} else
					switch_lock_to_unlock();
			}
			break;
		case CHANGE_PASS:
			if (change_pass_flag) {
				LCD_display("REFILL PASS", "");
				pw_ResetIdx();
				change_pass_flag = 0;
			} else {
				if (pw_checkInPW_change()) {
					pw_UpdatePass();
					switch_lock_to_sleep();
					sch_add_task(lcd_displaySuccess, 0, 0);
					sch_add_task(lcd_displayNormal, ONE_SECOND, 0);
				} else {
					switch_lock_to_wrong();
				}
			}
			break;
		default:
		}
		break;

	case 15:
		break;
	default:
		break;
	}
	if (key_id != UNPRESSED) {
		keypad_ResetFlag(key_id);
	}
}
static void switch_lock_to_unlock(void) {
	LCD_display("    UNLOCK DOOR", "");
	timer_for_st = UNLOCK_TIME;
	wrong_input_cnt = 0;
	st_lock = UNLOCK;
}
static void switch_lock_to_wrong(void) {
	timer_for_st = 1;
	wrong_input_cnt++;
	LCD_display("INVALID INPUT", "PLEASE REFILL");
	st_lock = WRONG;
}
static void switch_lock_to_password(void) {
	reset_timer();
	lcd_displayPW();
	sch_add_task(run_timer, 0, ONE_SECOND);
	st_lock = PASSWORD;
}
static void switch_lock_to_sleep(void) {
	pw_ResetIdx();
	LCD_display("    WELCOME TO", "     MY ROOM");
	st_lock = SLEEP;
}
static void reset_timer(void) {
	timer_for_st = TIMER;
}
static void run_timer(void) {
	if (wrong_input_flag == 1) {
		char str[17];
		sprintf(str, "REMAIN %ds", timer_for_st);
		LCD_display("BLOCK INPUT", str);
	}
	if (timer_for_st > 0) {
		timer_for_st--;
	}
}
static bool time_out(void) {

	if (timer_for_st == 0) {
		if (wrong_input_flag == 1 && st_lock == WRONG) {
			wrong_input_flag = 0;
		}
		sch_remove_task(run_timer);
		return 1;
	}
	return 0;
}
