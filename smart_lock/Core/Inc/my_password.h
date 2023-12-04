/*
 * my_password.h
 *
 *  Created on: Nov 30, 2023
 *      Author: HP
 */

#ifndef INC_MY_PASSWORD_H_
#define INC_MY_PASSWORD_H_
#include "my_define.h"

bool pw_update(uint8_t number);
uint8_t pw_idxGet(void);
char* pw_ReturnInput(void);
bool pw_checkInPW(void);
#endif /* INC_MY_PASSWORD_H_ */
