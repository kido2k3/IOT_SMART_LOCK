/*
 * software_timer.c
 *
 *  Created on: Sep 20, 2023
 *      Author: HP
 */

#include"software_timer.h"
void init_timer( s_timer *timer, const unsigned freq) {
	timer->freq=freq;
}

void set_timer( s_timer *timer, const unsigned long time)/*time unit is ms*/ {
	timer->count = time/1000.0*timer->freq;
	timer->st = 1;
}
void run_timer( s_timer *timer) {
	if (timer->count > 0) {
		timer->count--;
		if (timer->count < 1) {
			timer->st = 0;
		}
	}
}

