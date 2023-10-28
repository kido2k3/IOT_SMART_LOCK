#include "lcd.h"

I2C_HandleTypeDef *myLCD = &hi2c1;
/* Command */
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_DISPLAYCONTROL 0x08
#define LCD_FUNCTIONSET 0x20
#define LCD_ENTRYMODESET 0x04
#define LCD_SETDDRAMADDR 0x80
/* Backlight */
#define LCD_BACKLIGHT 0x08
/* Function Set */
#define LCD_4BITMODE 0x00
#define LCD_1LINE 0x00
#define LCD_2LINE 0x08
#define LCD_5x8DOTS 0x00

/* Display On/Off */
#define LCD_DISPLAYON 0x04
#define LCD_CURSOROFF 0x00
#define LCD_BLINKOFF 0x00
/* Entry Mode */
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTDECREMENT 0x00
/* Device I2C Address */
#define DEVICE_ADDR (0x27 << 1)
/* Enable Bit */
#define ENABLE 0x04
/* Register Select Bit */
#define RS 0x01

// variable
uint8_t dpFunction;
uint8_t dpControl;
uint8_t dpMode;
uint8_t dpRows;
uint8_t dpBacklight;

uint8_t idx = 0;
uint8_t line = 1;

void LCD_Init()
{

	dpRows = 2;

	dpBacklight = LCD_BACKLIGHT;

	dpFunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS | LCD_2LINE;

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

	dpControl = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
	dpControl |= LCD_DISPLAYON;
	SendCommand(LCD_DISPLAYCONTROL | dpControl);
	LCD_Clear();

	/* Display Mode */
	dpMode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	SendCommand(LCD_ENTRYMODESET | dpMode);
	DelayUS(4500);

	LCD_Home();
}

void LCD_Clear()
{
	SendCommand(LCD_CLEARDISPLAY);
	DelayUS(2000);
}
void LCD_Home()
{
	SendCommand(LCD_RETURNHOME);
	DelayUS(2000);
}

 void Write4Bits(uint8_t value)
{
	ExpanderWrite(value);
	PulseEnable(value);
}
 void PulseEnable(uint8_t _data)
{
	ExpanderWrite(_data | ENABLE);
	DelayUS(20);

	ExpanderWrite(_data & ~ENABLE);
	DelayUS(20);
}

 void ExpanderWrite(uint8_t _data)
{
	uint8_t data = _data | dpBacklight;
	HAL_I2C_Master_Transmit(myLCD, DEVICE_ADDR, (uint8_t *)&data, 1, 10);
}

// Delay
 void DelayInit(void)
{
	CoreDebug->DEMCR &= ~CoreDebug_DEMCR_TRCENA_Msk;
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

	DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk; //~0x00000001;
	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;  // 0x00000001;

	DWT->CYCCNT = 0;

	/* 3 NO OPERATION instructions */
	__ASM volatile("NOP");
	__ASM volatile("NOP");
	__ASM volatile("NOP");
}

 void DelayUS(uint32_t us)
{
	uint32_t cycles = (SystemCoreClock / 1000000L) * us;
	uint32_t start = DWT->CYCCNT;
	volatile uint32_t cnt;

	do
	{
		cnt = DWT->CYCCNT - start;
	} while (cnt < cycles);
}

// Send
 void SendCommand(uint8_t cmd)
{
	Send(cmd, 0);
}
 void SendChar(uint8_t ch)
{
	Send(ch, RS);
}
 void Send(uint8_t value, uint8_t mode)
{
	uint8_t highnib = value & 0xF0;
	uint8_t lownib = (value << 4) & 0xF0;
	Write4Bits((highnib) | mode);
	Write4Bits((lownib) | mode);
}

// Cursor
void LCD_SetCursor(uint8_t col, uint8_t row)
{
	int row_offsets[] = {0x00, 0x40, 0x14, 0x54};
	if (row >= dpRows)
	{
		row = dpRows - 1;
	}
	SendCommand(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

// Display
void LCD_display(const char line1[], const char line2[])
{
	switch (line)
	{
	case 1:
		if (*line1)
		{
			SendChar(line1[idx++]);
			if (idx >= strlen(line1))
			{
				LCD_SetCursor(0, 1);
				idx = 0;
				line = 2;
			}
		}
		else
		{
			LCD_SetCursor(0, 1);
			line = 2;
		}

		break;
	case 2:
		if (*line2)
		{
			SendChar(line2[idx++]);
			if (idx >= strlen(line2))
			{
				LCD_SetCursor(0, 0);
				idx = 0;
				line = 1;
			}
		}
		else
		{
			LCD_SetCursor(0, 0);
			line = 1;
		}
	default:
		break;
	}
}
