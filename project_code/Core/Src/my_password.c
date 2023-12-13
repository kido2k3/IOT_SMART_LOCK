/*
 * my_password.c
 *
 *  Created on: Nov 30, 2023
 *      Author: HP
 */
#include "my_password.h"

char password[LENGTH_OF_PASS + 1] = "74664";
char change_pass[LENGTH_OF_PASS + 1] = "74664";
char password_buf[17] = "";

uint8_t pw_idx = 0;
bool pw_update_change(uint8_t number) {
	if (pw_idx >= LENGTH_OF_PASS) {
		return 0;
	}
	change_pass[pw_idx++] = number + '0';
	return 1;
}

bool pw_update(uint8_t number) {
	if (pw_idx >= 16) {
		return 0;
	}
	password_buf[pw_idx++] = number + '0';
	password_buf[pw_idx] = '\0';
	return 1;
}
uint8_t pw_idxGet(void) {
	return pw_idx;
}
char* pw_ReturnInput(void) {
	return password_buf;
}
bool pw_checkInPW_change(void) {
	return strcmp(change_pass, password_buf) == 0;
}
bool pw_checkInPW(void) {
	return strcmp(password, password_buf) == 0;
}
void pw_ResetIdx(void) {
	pw_idx = 0;
}
void pw_UpdatePass(void) {
	strcpy(password, change_pass);
}
