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


osThreadId_t BattControllerTask;
bool flag_OVC = false, flag_OVV = false;

static void BattController_main(void *argument);
static void BattControllerApp_update(void);

int BattControllerTask_init(void){
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
		float voltage = AdcGet_voltage(VOLTAGE_BAT1)/1000.0;
		if (voltage > OVER_VOLTAGE) {
			flag_OVV = true;
		}
		else if (voltage > VBAT_MAX){
			flag_OVV = false;
			Max1538_set_state(MAX1538_STATE_CHARGE_B);
		}
		else if (voltage > V_THRESHOLD)
		{
			Max1538_set_state(MAX1538_STATE_CHARGE_A);
		}
		osDelay(2000);
	}
}

static void BattControllerApp_update(void){

}
