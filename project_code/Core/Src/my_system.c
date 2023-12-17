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

#ifdef TESTING


static void test_lcd(uint8_t key) {
	char str[3];
	sprintf(str, "%d", key);
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




extern UART_HandleTypeDef huart2;


void init(void) {
	sch_init();
	LCD_Init();
	LCD_Clear();
	keypad_init();
	button_init();
	fp_init();
	hcsr04_init();
	sch_add_task(hcsr04_read, 0, 130);
	sch_add_task(button_read, 0, 50);
	sch_add_task(keypad_read, 0, 75);
	sch_add_task(fsm_lock, 0, 10);
	sch_add_task(toggle_led, 0, ONE_SECOND);
}


void loop(void) {
	sch_dispatch();
}


