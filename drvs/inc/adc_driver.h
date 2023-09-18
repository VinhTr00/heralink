/*
 * adc_driver.h
 *
 *  Created on: Sep 8, 2023
 *      Author: vinhtran
 */

#ifndef _ADC_DRIVER_H_
#define _ADC_DRIVER_H_

#include <stm32g0xx_hal.h>
#include <stm32g0xx_hal_adc.h>

uint8_t ADC_Calibrate(ADC_HandleTypeDef *padc);
uint8_t ADC_Start(ADC_HandleTypeDef *padc, uint32_t *buffer, uint32_t len);

#endif /* _ADC_DRIVER_H_ */
