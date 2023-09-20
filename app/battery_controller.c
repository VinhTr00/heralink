/*
 * battery_controller.c
 *
 *  Created on: Sep 9, 2023
 *      Author: vinhtran
 */

#include "battery_controller.h"
#include "cmsis_os.h"
#include "adc_convert.h"
#include "gpio.h"
#include "max1538.h"

#include <stdbool.h>

#define OVER_VOLTAGE	13
#define UNDER_VOLTAGE	5
#define VBAT_MAX		12.5f
#define V_THRESHOLD		6

typedef struct 
{
	MAX1538_STATE_E max1538_state;
	MAX1538_STATE_E max1538_target_state;
	BATTERY_CONTROLLER_STATE_E state;
	adc_shared_memory_t data;
} BattController_t;

static BattController_t BattControl;
static void BattController_main(void *argument);
static void BattControllerApp_update(BattController_t* handle);

bool flag_OVC = false, flag_OVV = false;

int BattControllerTask_init(void){
	osThreadId_t BattControllerTask;
    const osThreadAttr_t BattControlTask_attributes = {
        .name = "BattControlTask",
        .priority = (osPriority_t) osPriorityNormal,
        .stack_size = 128 * 4
    };
    BattControllerTask = osThreadNew(BattController_main, NULL, &BattControlTask_attributes);
	(void)BattControllerTask;

	return 1;
}

static void BattController_main(void *argument){
	while (1){
		BattControllerApp_update(&BattControl);

		osDelay(pdMS_TO_TICKS(1000));
	}
}

static void BattControllerApp_update(BattController_t* handle){
	/* update voltage batt A and batt B */
	for (VoltageID i = VOLTAGE_BAT1; i < VOLTAGE_ADAPTER + 1; i++){
		handle->data.voltage_results[i] = AdcGet_voltage(i);
	}

	/* update current */
	for (CurrentID i = CURRENT_SYS; i < CURRENT_CHARGE + 1; i++){
		handle->data.current_results[i] = AdcGet_current(i);
	}
	/* update state of max1538 */
	handle->max1538_state = Max1538_release_state();
}
