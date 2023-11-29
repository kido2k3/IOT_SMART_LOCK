/*
 * scheduler.h
 *
 *  Created on: Nov 29, 2023
 *      Author: HP
 */

#ifndef INC_MY_SCHEDULER_H_
#define INC_MY_SCHEDULER_H_

#include"my_define.h"
#include<stdlib.h>
void sch_update(void);
void sch_init(void);
bool sch_dispatch(void);
bool sch_add_task(void (*pTask)(), uint16_t delay, uint16_t period);
#endif /* INC_MY_SCHEDULER_H_ */
