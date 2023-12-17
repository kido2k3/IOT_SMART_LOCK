/*
 * my_buzzer.c
 *
 *  Created on: Dec 13, 2023
 *      Author: HP
 */


#include"my_buzzer.h"

static void bz_on(void);
static void bz_off(void);

void bz_alarm(void){
	sch_add_task(bz_on, 0, 0);
	sch_add_task(bz_off, ONE_SECOND, 0);
}

static void bz_on(void){
	HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, 1);
}

static void bz_off(void){
	HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, 0);
}
