/*
 * my_fsm.c
 *
 *  Created on: Nov 29, 2023
 *      Author: HP
 */

#include "my_fsm.h"
enum {
	release, pressed, long_pressed
} st_button;
enum {
	INIT,
	SLEEP,
	PASSWORD,
	WRONG,
	UNLOCK,
	CHANGE_PASS,
	GET_FINGER,
	ENROLL_NEW_FINGER
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
static void run_timer_sleep(void);
static bool time_out(void);
static void fsm_keypad(void);
static bool fsm_button(void);
static void check_esp32(void);
static void rm_timer_sleep(void);
static void led_alarm(void);

#define TIMER		3 //15s, 5s for testing
#define BLOCK_TIME	10//10s to block keypad and fingerprint
#define UNLOCK_TIME	5

uint16_t timer_for_st = TIMER;
// rise if there was wrong input, if count > 3 block input for 30s
uint8_t wrong_input_cnt = 0;
//
bool wrong_input_flag = 0;
// flag for refill pass. 0: nothing, 1: refill password
bool change_pass_flag = 0;
// flag for enroll new finger. 0: nothing, 1: refill password
bool enroll_finger_flag = 0;
// sleep count
uint32_t sleep_preiod = 0;

void fsm_lock(void) {
	switch (st_lock) {
	case INIT:
		switch_lock_to_sleep();
	case SLEEP:
		lock_close();
		fsm_keypad();
		fsm_button();
		check_esp32();
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
			sch_add_task(bz_alarm, 0, ONE_SECOND * 3);
			sch_add_task(led_alarm, 0, ONE_SECOND*3);
			wrong_input_flag = 1;
			timer_for_st = BLOCK_TIME;
			wrong_input_cnt = 0;
		}
		if (time_out()) {
			sch_remove_task(bz_alarm);
			sch_remove_task(led_alarm);
			switch_lock_to_sleep();
		}
		break;
	case UNLOCK:
		lock_open();
		if (time_out()) {
			esp32_send_lock(1);
			switch_lock_to_sleep();
		}
		fsm_button();
		break;
	case GET_FINGER:
		if (fp_search()) {
			esp32_send_fingerID(fg_get_id());
			sch_add_task(run_timer, 0, ONE_SECOND);
			switch_lock_to_unlock();
		} else {
			LCD_display("  INVALID FINGER", "");
			switch_lock_to_sleep();
		}
		sch_remove_task(fp_run_timer);
		break;
	case ENROLL_NEW_FINGER:
		if (fp_enroll()) {
			LCD_display("SUCCESFULLY", "");
		} else {
			LCD_display("  STH WENT", "   WRONG");
		}
		sch_remove_task(fp_run_timer);
		switch_lock_to_sleep();
		break;
	}
}
static bool fsm_button(void) {
	switch (st_button) {
	case release:
		if (is_button_pressed(0) == 1) {
			//todo
			switch (st_lock) {
			case SLEEP:
				rm_timer_sleep();
				sch_add_task(run_timer, 0, ONE_SECOND);
				switch_lock_to_unlock();
				break;
			case UNLOCK:
				timer_for_st = UNLOCK_TIME;
				break;
			default:
				break;
			}
		} else if (is_button_pressed(0) == ERROR)
			return 0;
		break;
	case pressed:
		if (!is_button_pressed(0)) {
			st_button = release;
		} else {
			return 0;
		}
		break;
	default:
		return 0;
	}
	return 1;
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
				rm_timer_sleep();
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
		switch (st_lock) {
		case SLEEP:
			rm_timer_sleep();
			reset_timer();
			LCD_display("FILL PASS", "");
			sch_add_task(run_timer, 0, ONE_SECOND);
			enroll_finger_flag = 1;
			st_lock = PASSWORD;
			break;
		default:
		}
		break;
	case 7:
		break;

	case 11:
		switch (st_lock) {
		case SLEEP:
			rm_timer_sleep();
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
		switch (st_lock) {
		case SLEEP:
			rm_timer_sleep();
			reset_timer();
			LCD_display("INSERT YOUR", "FINGER");
			sch_add_task(fp_run_timer, 0, ONE_SECOND / 10);
			st_lock = GET_FINGER;
		default:
		}

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
				} else if (enroll_finger_flag) {
					sch_remove_task(run_timer);
					sch_add_task(fp_run_timer, 0, ONE_SECOND / 10);
					LCD_display("   INSERT NEW", "    FINGER");
					pw_ResetIdx();
					enroll_finger_flag = 0;
					st_lock = ENROLL_NEW_FINGER;
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
	esp32_send_lock(0);
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
	run_timer_sleep();
	pw_ResetIdx();
	LCD_display("    WELCOME TO", "     MY ROOM");
	st_lock = SLEEP;
}
static void reset_timer(void) {
	timer_for_st = TIMER;
}
static void run_timer(void) {
	if (timer_for_st > 0) {
		timer_for_st--;
	}
	if (wrong_input_flag == 1) {
		char str[17];
		sprintf(str, "REMAIN %ds", timer_for_st);
		LCD_display("BLOCK INPUT", str);
	}
}
static void subfun_run_timer_sleep(void) {
	sleep_preiod++;
}
static void run_timer_sleep(void) {
	sleep_preiod = 0;
	sch_add_task(subfun_run_timer_sleep, 0, ONE_SECOND);
}
static void rm_timer_sleep(void) {
	sch_remove_task(subfun_run_timer_sleep);
	esp32_send_sleep(sleep_preiod);
}
static void check_esp32(void) {
	if (esp32_get_flag()) {
		rm_timer_sleep();
		sch_add_task(run_timer, 0, ONE_SECOND);
		switch_lock_to_unlock();
		esp32_reset_flag();
	}
}
static void led_alarm(void) {
	sch_add_task(esp32_led_on, 0, 0);
	sch_add_task(esp32_led_off, ONE_SECOND, 0);
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
