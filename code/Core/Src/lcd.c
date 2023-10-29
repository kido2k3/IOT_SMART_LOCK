#include "lcd.h"

#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_FUNCTIONSET 0x20
#define LCD_SETDDRAMADDR 0x80

/* Entry Mode */
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTDECREMENT 0x00

/* Display On/Off */
#define LCD_DISPLAYON 0x04
#define LCD_CURSOROFF 0x00

/* Function Set */
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_5x8DOTS 0x00

/* Backlight */
#define LCD_BACKLIGHT 0x08

/* Enable Bit */
#define ENABLE 0x04


/* Register Select Bit */
#define RS 0x01

/* Device I2C Address */
#define DEVICE_ADDR     (0x27 << 1)

I2C_HandleTypeDef *my_lcd = &hi2c1;

uint8_t dpFunction;
uint8_t dpControl;
uint8_t dpMode;
uint8_t dpRows;
uint8_t dpBacklight;

uint8_t idx = 0;
uint8_t line = 1;

 void SendCommand(uint8_t);
 void SendChar(uint8_t);
 void Send(uint8_t, uint8_t);
 void Write4Bits(uint8_t);
 void ExpanderWrite(uint8_t);
 void PulseEnable(uint8_t);
 void DelayInit(void);
 void DelayUS(uint32_t);
 void HD44780_Home();

void HD44780_Init() {
	dpRows = 2;

	dpBacklight = LCD_BACKLIGHT;

	dpFunction = LCD_4BITMODE | LCD_5x8DOTS | LCD_2LINE;

	/* Wait for initialization */
	DelayInit();
	HAL_Delay(50);

	ExpanderWrite(dpBacklight);
	HAL_Delay(1000);

	/* 4bit Mode */
	Write4Bits(0x03 << 4);
	DelayUS(4500);

	Write4Bits(0x03 << 4);
	DelayUS(4500);

	Write4Bits(0x03 << 4);
	DelayUS(4500);

	Write4Bits(0x02 << 4);
	DelayUS(100);

	/* Display Control */
	SendCommand(LCD_FUNCTIONSET | dpFunction);

	dpControl = LCD_DISPLAYON | LCD_CURSOROFF;
	//HD44780_Display();
	dpControl |= LCD_DISPLAYON;
	SendCommand(LCD_DISPLAYCONTROL | dpControl);
	HD44780_Clear();

	/* Display Mode */
	dpMode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	SendCommand(LCD_ENTRYMODESET | dpMode);
	DelayUS(4500);

	HD44780_Home();
}

void HD44780_Clear() {
	SendCommand(LCD_CLEARDISPLAY);
	DelayUS(2000);
}

void HD44780_Home() {
	SendCommand(LCD_RETURNHOME);
	DelayUS(2000);
}

void HD44780_SetCursor(uint8_t col, uint8_t row) {
	int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
	if (row >= dpRows) {
		row = dpRows - 1;
	}
	SendCommand(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

void HD44780_Display() {
	dpControl |= LCD_DISPLAYON;
	SendCommand(LCD_DISPLAYCONTROL | dpControl);
}

void LCD_display(const char c1[], const char c2[]) {
	switch (line) {
	case 1:
		if (*c1) {
			SendChar(c1[idx++]);
			if (idx >= strlen(c1)) {
				HD44780_SetCursor(0, 1);
				idx = 0;
				line = 2;
			}

		} else {
			HD44780_SetCursor(0, 1);
			line = 2;
		}

		break;
	case 2:
		if (*c2) {
			SendChar(c2[idx++]);
			if (idx >= strlen(c2)) {
				HD44780_SetCursor(0, 0);
				idx = 0;
				line = 1;
			}

		} else {
			HD44780_SetCursor(0, 0);
			line = 1;
		}
	default:
		break;
	}

}

 void SendCommand(uint8_t cmd) {
	Send(cmd, 0);
}

 void SendChar(uint8_t ch) {
	Send(ch, RS);
}

 void Send(uint8_t value, uint8_t mode) {
	uint8_t highnib = value & 0xF0;
	uint8_t lownib = (value << 4) & 0xF0;
	Write4Bits((highnib) | mode);
	Write4Bits((lownib) | mode);
}

 void Write4Bits(uint8_t value) {
	ExpanderWrite(value);
	PulseEnable(value);
}

 void ExpanderWrite(uint8_t _data) {
	uint8_t data = _data | dpBacklight;
	HAL_I2C_Master_Transmit(my_lcd, DEVICE_ADDR, (uint8_t*) &data, 1, 10);
}

 void PulseEnable(uint8_t _data) {
	ExpanderWrite(_data | ENABLE);
	DelayUS(20);

	ExpanderWrite(_data & ~ENABLE);
	DelayUS(20);
}

 void DelayInit(void) {
	CoreDebug->DEMCR &= ~CoreDebug_DEMCR_TRCENA_Msk;
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

	DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk; //~0x00000001;
	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk; //0x00000001;

	DWT->CYCCNT = 0;

	/* 3 NO OPERATION instructions */
	__ASM volatile ("NOP");
	__ASM volatile ("NOP");
	__ASM volatile ("NOP");
}

 void DelayUS(uint32_t us) {
	uint32_t cycles = (SystemCoreClock / 1000000L) * us;
	uint32_t start = DWT->CYCCNT;
	volatile uint32_t cnt;

	do {
		cnt = DWT->CYCCNT - start;
	} while (cnt < cycles);
}

