/*
 * my_lock.c
 *
 *  Created on: Dec 4, 2023
 *      Author: HP
 */

#include "my_lock.h"


void lock_open(void){
	HAL_GPIO_WritePin(LOCK_PORT, LOCK_PIN, 1);
}

void lock_close(void){
	HAL_GPIO_WritePin(LOCK_PORT, LOCK_PIN, 0);
}
