/*
 * scheduler.h
 *
 *  Created on: Nov 29, 2023
 *      Author: HP
 */

#ifndef INC_MY_SCHEDULER_H_
#define INC_MY_SCHEDULER_H_

#include <my_keypadTTP229.h>
#include"my_define.h"
#include "my_lcd.h"
#include<stdlib.h>

#define ONE_SECOND	1000

void sch_update(void);
void sch_init(void);
bool sch_dispatch(void);
bool sch_add_task(void (*pTask)(), uint32_t delay, uint32_t period);
void sch_remove_task(void (*pTask)());
#endif /* INC_MY_SCHEDULER_H_ */
