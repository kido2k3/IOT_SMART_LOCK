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
#include "my_password.h"
/* Command */

void LCD_Init();
void LCD_Clear();
void LCD_display(const char[], const char[]);
void lcd_displayPW(void);
void lcd_displayPW_change(void);
void lcd_displaySuccess(void);
void lcd_displayNormal(void);
void DelayUS(uint32_t us);
#endif /* INC_MY_LCD_H_ */
