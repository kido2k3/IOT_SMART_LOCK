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
static void test_keypad(void){
	if(keyPressed == 5){
		toggle_led();
		keyPressed = UNPRESSED;
	}
}
void init(void) {
	sch_init();
	keypad_init();
	//sch_add_task(toggle_led, 2000, 0);
}

void loop(void) {
	sch_dispatch();
	test_keypad();
}

