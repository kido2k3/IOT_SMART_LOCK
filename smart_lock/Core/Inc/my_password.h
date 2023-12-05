/*
 * my_password.h
 *
 *  Created on: Nov 30, 2023
 *      Author: HP
 */

#ifndef INC_MY_PASSWORD_H_
#define INC_MY_PASSWORD_H_
#include "my_define.h"

#define LENGTH_OF_PASS	5
bool pw_update_change(uint8_t number);
bool pw_update(uint8_t number);
void pw_UpdatePass(void);
uint8_t pw_idxGet(void);
char* pw_ReturnInput(void);
bool pw_checkInPW(void);
bool pw_checkInPW_change(void);
void pw_ResetIdx(void);
#endif /* INC_MY_PASSWORD_H_ */
