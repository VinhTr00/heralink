/*
 * battery_controller.c
 *
 *  Created on: Sep 9, 2023
 *      Author: vinhtran
 */

/* Includes ------------------------------------------------------------------*/
#include "battery_controller.h"
#include "cmsis_os.h"
#include "adc_convert.h"
#include "gpio.h"
#include "max1538.h"
#include <stdbool.h>

/* Private typedef -----------------------------------------------------------*/
typedef struct 
{
	MAX1538_STATE_E max1538_state;
	MAX1538_STATE_E max1538_target_state;
	BATSEL_MODE_E batsel_mode;
	BATTERY_CONTROLLER_STATE_E control_state;
	adc_shared_memory_t data;

} BattController_t;

/* Private define ------------------------------------------------------------*/
#define OVER_VOLTAGE			20000	//mV
#define UNDER_VOLTAGE			12500	//mV
#define VBAT_MAX				16800	//mV
#define V_THRESHOLD				6000	//mV
#define V_HYS					100		//mV	
#define T_DELAY_FULLBATT 		4		//s
#define T_DELAY_FULLCHARGE		4		//s


/* Private variables ---------------------------------------------------------*/
static BattController_t BattControl;

/* Private function prototypes -----------------------------------------------*/
static void BattController_main(void *argument);
static void BattControllerApp_update(BattController_t* handle);
static void BattControllerSM_run(BattController_t* handle);
static void BattController_AutoMode(BattController_t* handle);


/* Private functions ---------------------------------------------------------*/
void BattController_main(void *argument){
	while (1){
		BattControllerApp_update(&BattControl);
		
		osDelay(pdMS_TO_TICKS(1000));
	}
}

void BattControllerApp_update(BattController_t* handle){
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
	/* update mode of batsel */
	handle->batsel_mode = Max1538_release_mode_batsel();
}

void BattControllerSM_run(BattController_t* handle){
	uint16_t vol_bat1 = handle->data.voltage_results[VOLTAGE_BAT1];
	uint16_t vol_bat2 = handle->data.voltage_results[VOLTAGE_BAT2];
	uint16_t vol_adap = handle->data.voltage_results[VOLTAGE_ADAPTER];
	static uint8_t t_delayFullBatt = 0;
	if (handle->batsel_mode == BATSEL_MODE_AUTO)
	{
		if (vol_adap >= UNDER_VOLTAGE){
			if ( (vol_bat1 > (V_THRESHOLD + V_HYS)) && (vol_bat1 < VBAT_MAX) && (vol_bat1 < vol_bat2) ){
				handle->control_state = BATTERY_CONTROLLER_CHARGE_BAT1;
			}
			else if ( (vol_bat2 > (V_THRESHOLD + V_HYS)) && (vol_bat2 < VBAT_MAX) && (vol_bat1 > vol_bat2) ){
				handle->control_state = BATTERY_CONTROLLER_CHARGE_BAT2;
			}
			// TODO: add Ibatt1 < Ibatt_threshold trong t_delayFullCharge 
			if ( (vol_bat1 < V_THRESHOLD) || ( (VBAT_MAX - vol_bat1 < 10) && (handle->control_state == BATTERY_CONTROLLER_CHARGE_BAT1) ) ){
				t_delayFullBatt++;
				if (t_delayFullBatt == T_DELAY_FULLBATT){
					handle->control_state = BATTERY_CONTROLLER_AC_ADAPTER_SEARCH;
				}
			}
			// TODO: add Ibatt2 < Ibatt_threshold trong t_delayFullCharge 
			else if ( (vol_bat2 < V_THRESHOLD) || ( (VBAT_MAX - vol_bat2 < 10) && (handle->control_state == BATTERY_CONTROLLER_CHARGE_BAT2) ) ){
				t_delayFullBatt++;
				if (t_delayFullBatt == T_DELAY_FULLBATT){
					handle->control_state = BATTERY_CONTROLLER_AC_ADAPTER_SEARCH;
				}
			}
		}
		else {
			if (vol)
		}
	}
}

/* Public functions ---------------------------------------------------------*/
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

