/*
 * adc_convert.c
 *
 *  Created on: Sep 5, 2023
 *      Author: vinhtran
 */

#include "adc_convert.h"
#include "adc.h"
#include "cmsis_os.h"

#define VREFINT_CAL 	*(uint16_t *)(0x1FFF75AA)
#define VDDA            3.0f

static void AdcTask_main(void *argument);
static void AdcTask_convert(void);

osThreadId_t AdcTask;

uint16_t adc_raw_results[12];
uint16_t  voltage_results[5]; //mV
uint16_t temperature_results[5];
int16_t current_results[4];


int AdcTask_init(void)
{
    const osThreadAttr_t AdcTask_attributes = {
        .name = "AdcTask",
        .priority = (osPriority_t) osPriorityNormal1,
        .stack_size = 128 * 4
    };
	AdcTask = osThreadNew(AdcTask_main, NULL, &AdcTask_attributes);
	(void)AdcTask;

    ADC_Calibrate(&hadc1);
    ADC_Start(&hadc1, (uint32_t *)adc_raw_results, 5);

    return 1;
}

uint16_t AdcGet_voltage(VoltageID id)
{
	return voltage_results[id];
}

uint16_t AdcGet_temperature(TemperatureID id)
{
    return temperature_results[id];
}

uint16_t AdcGet_current(CurrentID id)
{
    return current_results[id];
}

static void AdcTask_main(void *argument){
//	static uint8_t counting_adc = 1;
//	static uint16_t temp = 0;
    while (1)
    {
//    	if (adc_raw_results[0] > adc_max) adc_max = adc_raw_results[0];
//    	if (adc_raw_results[0] < adc_min) adc_min = adc_raw_results[0];
//    	if (counting_adc < 20){
//    		temp += adc_raw_results[0];
//    		counting_adc++;
//    	}
//    	if (counting_adc == 20){
//    		adc_tb = temp/20;
//    		counting_adc = 0;
//    		temp = 0;
//    	}
        // vref_volt = VDDA*VREFINT_CAL/adc_raw_results[2];
        // voltage_results[VOLTAGE_BAT1] = adc_raw_results[0]*vref_volt*11*1000/4095;
        AdcTask_convert();
        osDelay(1000);
    }
}

static void AdcTask_convert(void){
    voltage_results[VOLTAGE_VREFINT] = VDDA*VREFINT_CAL*1000/adc_raw_results[2];

    for (uint8_t i = VOLTAGE_BAT1; i < VOLTAGE_ADAPTER ; i++){
        voltage_results[i] = adc_raw_results[i]*voltage_results[VOLTAGE_VREFINT]*11/4095;
    }
    /*
    for (uint8_t i = TEMPERATURE_AIR; i < TEMPERATURE_BAT2 + 1; i++){
        temperature_results[i] = adc_raw_results[ADC_TEMP_AIR + i];
    }

    for (uint8_t i = CURRENT_BAT1; i < CURRENT_CHARGE + 1; i++){
        current_results[i] = adc_raw_results[ADC_CUR_BAT1 + i];
    }
    */
}
