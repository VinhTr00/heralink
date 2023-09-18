/*
 * adc_convert.h
 *
 *  Created on: Sep 5, 2023
 *      Author: vinhtran
 */

#ifndef _ADC_CONVERT_H_
#define _ADC_CONVERT_H_

#include "adc_driver.h"

typedef enum {
	ADC_TEMP_AIR,
	ADC_TEMP_RF1,
	ADC_TEMP_RF2,
	ADC_TEMP_BAT1,
	ADC_TEMP_BAT2,
	ADC_VOLT_BAT1,
	ADC_VOLT_BAT2,
	ADC_VOLT_ADAPTER,
	ADC_VOLT_SYS,
	ADC_VOLT_VREFINT,
	ADC_CUR_SYS,
	ADC_CUR_CHARGE
} ADCRawID;

typedef enum {
	TEMPERATURE_AIR,
	TEMPERATURE_RF1,
	TEMPERATURE_RF2,
	TEMPERATURE_BAT1,
	TEMPERATURE_BAT2
} TemperatureID;

typedef enum {
	VOLTAGE_BAT1,
	VOLTAGE_BAT2,
	VOLTAGE_ADAPTER,
	VOLTAGE_SYS,
	VOLTAGE_VREFINT
} VoltageID;

typedef enum {
	CURRENT_SYS,
	CURRENT_CHARGE
} CurrentID;


int AdcTask_init(void);
uint16_t AdcGet_voltage(VoltageID id);
uint16_t AdcGet_temperature(TemperatureID id);
uint16_t AdcGet_current(CurrentID id);



#endif /* INC_ADC_CONVERT_H_ */
