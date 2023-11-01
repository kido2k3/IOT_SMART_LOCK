#ifndef LIQUIDCRYSTAL_I2C_H_
#define LIQUIDCRYSTAL_I2C_H_

#include "stm32f1xx_hal.h"
#include <string.h>
#include "port.h"
/* Command */

void LCD_Init();
void LCD_Clear();
void LCD_display(const char[], const char[]);

#endif /* LIQUIDCRYSTAL_I2C_H_ */
