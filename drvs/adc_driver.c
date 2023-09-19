/*
 * adc_driver.c
 *
 *  Created on: Sep 8, 2023
 *      Author: vinhtran
 */

#include "adc_driver.h"


uint8_t ADC_Calibrate(ADC_HandleTypeDef *padc)
{
	return HAL_ADCEx_Calibration_Start(padc);
}

uint8_t ADC_Start(ADC_HandleTypeDef *padc, uint32_t *buffer, uint32_t len)
{
	return HAL_ADC_Start_DMA(padc, buffer, len);
}

