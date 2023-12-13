/*
 * my_keypad.c
 *
 *  Created on: Nov 29, 2023
 *      Author: HP
 */

#include <my_keypadTTP229.h>

#define KEYPAD_TIMEOUT	50 // 50ms

uint8_t key_buf[16];
uint16_t timer = KEYPAD_TIMEOUT * 100;

static bool time_out(void) {
	DelayUS(10);
	if (timer > 0) {
		timer--;
	}
	if (timer == 0)
		return 1;
	return 0;
}
static bool keypad_IsTouch(void) {
	timer = KEYPAD_TIMEOUT * 100;
	//------------DV start-----------------
	//read each 10us, end loop when over KEYPAD_TIMEOUT or read 0 signal
	while (HAL_GPIO_ReadPin(KEYPAD_PORT, KEYPAD_SDO_PIN)) {
		if (time_out())
			return 0;
	}
	//read each 10us, end loop when over KEYPAD_TIMEOUT or read 1 signal
	while (!HAL_GPIO_ReadPin(KEYPAD_PORT, KEYPAD_SDO_PIN)) {
		if (time_out())
			return 0;
	}
	//------------DV end-----------------
	DelayUS(10); // for TW
	return 1;
}
static void keypad_bit(uint8_t i) {
	HAL_GPIO_WritePin(KEYPAD_PORT, KEYPAD_SCL_PIN, 0);
	DelayUS(2);
	uint8_t bit = !HAL_GPIO_ReadPin(KEYPAD_PORT, KEYPAD_SDO_PIN);
	if (bit == 0) {
		key_buf[i] = 0;
	} else {
		key_buf[i]++;
	}
	HAL_GPIO_WritePin(KEYPAD_PORT, KEYPAD_SCL_PIN, 1);
	DelayUS(2);
}
static void keypad_scan() {
	for (uint8_t i = 0; i < 16; i++) {
		keypad_bit(i);
	}
	HAL_Delay(2); //for Tout
}
void keypad_init(void) {
	for (uint8_t i = 0; i < 16; i++) {
		key_buf[i] = 0;
	}
	HAL_GPIO_WritePin(KEYPAD_PORT, KEYPAD_SCL_PIN, 1);
}

void keypad_read(void) {
	if (keypad_IsTouch()) {
		keypad_scan();
	}
}
uint8_t keypad_IsPressed(void) {
	for (uint8_t i = 0; i < 15; i++) {
		if (key_buf[i] > 0)
			return i;
	}
	return UNPRESSED;
}
void keypad_ResetFlag(uint8_t id) {
	if (id > 15)
		return;
	key_buf[id] = 0;
}
