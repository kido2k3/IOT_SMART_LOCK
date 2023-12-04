/*
 * my_system.c
 *
 *  Created on: Nov 29, 2023
 *      Author: HP
 */

#include"my_system.h"

static void toggle_led(void) {
	HAL_GPIO_TogglePin(DEBUG_LED_PORT, DEBUG_LED_PIN);
}
static void test_lcd(uint8_t key) {

}
static void test_uart(uint8_t key) {
	uart_SendPressedKey(key);
	uart_SendInPW();
}
static void test_keypad(void) {
	uint8_t key = keypad_ReadFlag();
	if (key != UNPRESSED) {
		toggle_led();
		test_lcd(key);
		test_uart(key);
		keypad_ResetFlag();
	}
}
static void test_lock(void) {
	sch_add_task(lock_open, 0, 0);
	sch_add_task(lock_close, 5000, 0);
}
void init(void) {
	sch_init();
	//sch_add_task(toggle_led, 0, 1000);
	sch_add_task(test_lock, 0, 7000);
}

void loop(void) {
	sch_dispatch();
	test_keypad();
}

