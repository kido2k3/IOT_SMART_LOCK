/*
 * my_lcd.h
 *
 *  Created on: Nov 29, 2023
 *      Author: HP
 */

#ifndef INC_MY_LCD_H_
#define INC_MY_LCD_H_

#include "stm32f1xx_hal.h"
#include <string.h>
#include "my_define.h"
/* Command */

void LCD_Init();
void LCD_Clear();
void LCD_display(const char[], const char[]);

#endif /* INC_MY_LCD_H_ */
