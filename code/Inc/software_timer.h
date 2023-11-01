/*
 * software_timer.h
 *
 *  Created on: Sep 20, 2023
 *      Author: HP
 */

#ifndef MYLIB_SOFTWARE_TIMER_H_
#define MYLIB_SOFTWARE_TIMER_H_
#include<stdint.h>
typedef struct{
	uint8_t st;
	unsigned long count;
	unsigned freq;
}s_timer;
extern s_timer my_timer[2];
void init_timer( s_timer* timer, const unsigned freq);
void set_timer( s_timer* timer, const unsigned long time);
void run_timer( s_timer* timer);


#endif /* MYLIB_SOFTWARE_TIMER_H_ */
