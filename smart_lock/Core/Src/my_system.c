/*
 * my_system.c
 *
 *  Created on: Nov 29, 2023
 *      Author: HP
 */

#include"my_system.h"

#ifdef TESTING

static void toggle_led(void) {
	HAL_GPIO_TogglePin(DEBUG_LED_PORT, DEBUG_LED_PIN);
}
static void test_lcd(uint8_t key) {
	char str[3];
	sprintf(str, "%d", key);
	LCD_Clear();
	LCD_display("KEY PRESS", str);
}
static void test_uart(uint8_t key) {
	uart_SendPressedKey(key);
	uart_SendInPW();
}

static void test_keypad(void) {
	uint8_t key = keypad_IsPressed();
	if (key != UNPRESSED) {
		toggle_led();
		keypad_ResetFlag(key);
		test_uart(key);
		test_lcd(key);
	}
}
static void test_lock(void) {
	sch_add_task(lock_open, 0, 0);
	sch_add_task(lock_close, 5000, 0);
}
#endif
void init(void) {
//	sch_init();
//	LCD_Init();
//	LCD_Clear();
//	keypad_init();
//	sch_add_task(keypad_read, 0, 75);
//	sch_add_task(fsm_lock, 0, 10);
	fp_init();
}

void loop(void) {
	//sch_dispatch();

}

