/*
 * my_fsm.c
 *
 *  Created on: Nov 29, 2023
 *      Author: HP
 */

#include "my_fsm.h"


enum{
	SLEEP,
	HANDLE_BUTTON,
	ALARM,
	UNLOCK
}st_lock;
