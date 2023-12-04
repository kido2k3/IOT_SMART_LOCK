/*
 * my_password.c
 *
 *  Created on: Nov 30, 2023
 *      Author: HP
 */
#include "my_password.h"

#define LENGTH	5
char password[LENGTH + 1] = "74664";
char password_buf[LENGTH + 1] = "00000";

uint8_t pw_idx = 0;

bool pw_update(uint8_t number) {
	if (pw_idx >= LENGTH) {
		return 0;
	}
	password_buf[pw_idx++] = number + '0';
	return 1;
}
uint8_t pw_idxGet(void) {
	return pw_idx;
}
char* pw_ReturnInput(void) {
	return password_buf;
}

bool pw_checkInPW(void) {
	return strcmp(password, password_buf) != 0;
}
