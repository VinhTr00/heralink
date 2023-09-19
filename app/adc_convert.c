/*
 * adc_convert.c
 *
 *  Created on: Sep 5, 2023
 *      Author: vinhtran
 */

#include "adc_convert.h"
#include "adc.h"
#include "cmsis_os.h"

#define VREFINT_CAL 		*(uint16_t *)(0x1FFF75AA)
#define VDDA            	3.0f
#define VOLTAGE_SCALE		11
#define ADC_FULL_SCALE		4095

typedef struct {
	uint16_t adc_raw_results[12];
	uint16_t  voltage_results[5]; //mV
	uint16_t temperature_results[5];
	int16_t current_results[2];
} adc_shared_memory_t;

static void AdcTask_main(void *argument);
static void AdcTask_convert(adc_shared_memory_t *pHandle);

static adc_shared_memory_t handle_adc;

int AdcTask_init(void)
{
	osThreadId_t AdcTask;
    const osThreadAttr_t AdcTask_attributes = {
        .name = "AdcTask",
        .priority = (osPriority_t) osPriorityNormal1,
        .stack_size = 128 * 4
    };
	AdcTask = osThreadNew(AdcTask_main, NULL, &AdcTask_attributes);
	(void)AdcTask;

    ADC_Calibrate(&hadc1);
    ADC_Start(&hadc1, (uint32_t *)handle_adc.adc_raw_results, 5);

    return 1;
}

uint16_t AdcGet_voltage(VoltageID id)
{
	return handle_adc.voltage_results[id];
}

uint16_t AdcGet_temperature(TemperatureID id)
{
    return handle_adc.temperature_results[id];
}

uint16_t AdcGet_current(CurrentID id)
{
    return handle_adc.current_results[id];
}

static void AdcTask_main(void *argument){
    while (1)
    {
        AdcTask_convert(&handle_adc);
        osDelay(1000);
    }
}

static void AdcTask_convert(adc_shared_memory_t *pHandle){
    pHandle->voltage_results[VOLTAGE_VREFINT] = VDDA*VREFINT_CAL*1000/pHandle->adc_raw_results[4];

    for (uint8_t i = VOLTAGE_BAT1; i < VOLTAGE_ADAPTER ; i++){
        pHandle->voltage_results[i] = pHandle->adc_raw_results[i] * pHandle->voltage_results[VOLTAGE_VREFINT] * VOLTAGE_SCALE/ADC_FULL_SCALE;
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
