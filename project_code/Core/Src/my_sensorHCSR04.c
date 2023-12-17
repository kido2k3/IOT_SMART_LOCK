/*
 * my_sensor.c
 *
 *  Created on: Nov 29, 2023
 *      Author: HP
 */

#include <my_sensorHCSR04.h>

uint32_t IC_Val1 = 0;
uint32_t IC_Val2 = 0;
uint32_t Difference = 0;
uint8_t Is_First_Captured = 0;  // is the first value captured ?
uint32_t Distance = 0;

uint32_t IC_Val21 = 0;
uint32_t IC_Val22 = 0;
uint32_t Difference2 = 0;
uint8_t Is_First_Captured2 = 0;  // is the first value captured ?
uint32_t Distance2 = 0;
extern TIM_HandleTypeDef htim1;

void hcsr04_init(void) {
	HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);
	HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_4);
}

void hcsr04_read(void) {
	HAL_GPIO_WritePin(SOUND_SS_PORT, SOUND_SS_TRI1_PIN, GPIO_PIN_SET); // pull the TRIG pin HIGH
	HAL_GPIO_WritePin(SOUND_SS_PORT, SOUND_SS_TRI2_PIN, GPIO_PIN_SET); // pull the TRIG pin HIGH
	DelayUS(10);  // wait for 10 us
	HAL_GPIO_WritePin(SOUND_SS_PORT, SOUND_SS_TRI1_PIN, 0); // pull the TRIG pin low
	HAL_GPIO_WritePin(SOUND_SS_PORT, SOUND_SS_TRI2_PIN, 0); // pull the TRIG pin HIGH

	__HAL_TIM_ENABLE_IT(&htim1, TIM_IT_CC1);
	__HAL_TIM_ENABLE_IT(&htim1, TIM_IT_CC4);
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) // if the interrupt source is channel1
			{
		if (Is_First_Captured == 0) // if the first value is not captured
				{
			IC_Val1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1); // read the first value
			Is_First_Captured = 1;  // set the first captured as true
			// Now change the polarity to falling edge
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1,
					TIM_INPUTCHANNELPOLARITY_FALLING);
		}

		else if (Is_First_Captured == 1)   // if the first is already captured
				{
			IC_Val2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1); // read second value
			__HAL_TIM_SET_COUNTER(htim, 0);  // reset the counter

			if (IC_Val2 > IC_Val1) {
				Difference = IC_Val2 - IC_Val1;
			}

			else if (IC_Val1 > IC_Val2) {
				Difference = (0xffff - IC_Val1) + IC_Val2;
			}

			Distance = Difference * .034 / 2;
			Is_First_Captured = 0; // set it back to false

			// set polarity to rising edge
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1,
					TIM_INPUTCHANNELPOLARITY_RISING);
			__HAL_TIM_DISABLE_IT(&htim1, TIM_IT_CC1);
		}
	} else if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4) {

		if (Is_First_Captured2 == 0) // if the first value is not captured
				{
			IC_Val21 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_4); // read the first value
			Is_First_Captured2 = 1;  // set the first captured as true
			// Now change the polarity to falling edge
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_4,
					TIM_INPUTCHANNELPOLARITY_FALLING);
		}

		else if (Is_First_Captured2 == 1)   // if the first is already captured
				{
			IC_Val22 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_4); // read second value
			__HAL_TIM_SET_COUNTER(htim, 0);  // reset the counter

			if (IC_Val22 > IC_Val21) {
				Difference2 = IC_Val22 - IC_Val21;
			}

			else if (IC_Val21 > IC_Val22) {
				Difference2 = (0xffff - IC_Val21) + IC_Val22;
			}

			Distance2 = Difference2 * .034 / 2;
			Is_First_Captured2 = 0; // set it back to false

			// set polarity to rising edge
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_4,
					TIM_INPUTCHANNELPOLARITY_RISING);
			__HAL_TIM_DISABLE_IT(&htim1, TIM_IT_CC4);
		}

	}
}
