/*
 * my_sensor.h
 *
 *  Created on: Nov 29, 2023
 *      Author: HP
 */

#ifndef INC_MY_SENSORHCSR04_H_
#define INC_MY_SENSORHCSR04_H_

#include "my_define.h"
#include "my_lcd.h"

#define MAX_DISTANCE	50
void hcsr04_init(void);
void hcsr04_read(void); //cycle = 130ms
bool hcsr04_get_flag(void);
void hcsr04_get_data(uint32_t *kc, uint32_t *kc2);

#endif /* INC_MY_SENSORHCSR04_H_ */
