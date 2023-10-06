/*
 * lcd.h
 *
 *  Created on: Oct 6, 2023
 *      Author: HP
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include"main.h"
#define SLAVE_ADDRESS_LCD 0x4E
#define TIME_OUT 100

typedef struct{
	I2C_HandleTypeDef* i2c;
} lcd_led;
extern lcd_led my_lcd;

void lcd_init();
void lcd_send_cmd(char cmd);
void lcd_send_string(char *str);
void lcd_put_cur(int row, int col);
void lcd_send_data (char data);
void lcd_clear();
#endif /* INC_LCD_H_ */
