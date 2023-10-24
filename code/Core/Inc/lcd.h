/*
 * lcd.h
 *
 *  Created on: Oct 6, 2023
 *      Author: HP
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "main.h"
#define SLAVE_ADDRESS_LCD 0x4E
#define TIME_OUT 100

typedef struct
{
	I2C_HandleTypeDef *i2c;
	int address;
} lcd_led;
extern lcd_led my_lcd;

int lcd_display(lcd_led *my_lcd, char *line1, char *line2);
int lcd_erase(lcd_led *my_lcd);
int lcd_init(lcd_led *my_lcd, int address, I2C_HandleTypeDef *i2c);