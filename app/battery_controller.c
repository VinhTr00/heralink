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
#include "battery.h"
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

#define VBAT_MAX				16800	//mV
#define V_THRESHOLD				13000	//mV
#define V_HYS					100		//mV	
#define T_DELAY_FULLBATT 		4		//s
#define T_DELAY_FULLCHARGE		4		//s


/* Private variables ---------------------------------------------------------*/
static BattController_t BattControl = {
	.control_state = BATTERY_CONTROLLER_AC_ADAPTER_SEARCH
};

/* Private function prototypes -----------------------------------------------*/
static void BattController_main(void* argument);
static void BattControllerApp_update(BattController_t* handle);
static void BattControllerSM_run(BattController_t* handle);
// static void BattController_AutoMode(BattController_t* handle);


/* Private functions ---------------------------------------------------------*/
void BattController_main(void *argument){
	while (1){
		BattControllerApp_update(&BattControl);
		BattControllerSM_run(&BattControl);
		osDelay(pdMS_TO_TICKS(500));
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
	static uint8_t temp_controlState = 0;
	static uint8_t flag_charge = 0;
	static uint8_t flag_discharge = 0;
	if (handle->batsel_mode == BATSEL_MODE_AUTO)
	{
		if (vol_adap >= UNDER_VOLTAGE)
		{
			flag_discharge = 0;
			if (flag_charge == 0)
			{
				if ((vol_bat1 < vol_bat2 || vol_bat2 < UNDER_VOLTAGE)  && vol_bat1 > (V_THRESHOLD + V_HYS) && (VBAT_MAX - vol_bat1 > 100) )
				{
					flag_charge = 1;
					handle->control_state = BATTERY_CONTROLLER_CHARGE_BAT1;
				}
				else if ((vol_bat1 > vol_bat2 || vol_bat1 < UNDER_VOLTAGE) && vol_bat2 > (V_THRESHOLD + V_HYS) && (VBAT_MAX - vol_bat2 > 100))
				{
					flag_charge = 2;
					handle->control_state = BATTERY_CONTROLLER_CHARGE_BAT2;
				}
				else
				{
					handle->control_state = BATTERY_CONTROLLER_AC_ADAPTER_SEARCH;
				}
			}
			// TODO: add Ibatt1 < Ibatt_threshold trong t_delayFullCharge 
			if ( ( (vol_bat1 < UNDER_VOLTAGE) ||  (VBAT_MAX - vol_bat1 < 100) ) && (flag_charge == 1) )
			{
				t_delayFullBatt++;
				if (t_delayFullBatt == T_DELAY_FULLBATT)
				{
					handle->control_state = BATTERY_CONTROLLER_AC_ADAPTER_SEARCH;
					t_delayFullBatt = 0;
					flag_charge = 0;
				}
			}
			// TODO: add Ibatt2 < Ibatt_threshold trong t_delayFullCharge 
			else if ( ( (vol_bat2 < UNDER_VOLTAGE) ||  (VBAT_MAX - vol_bat2 < 100) ) && (flag_charge == 2) )
			{
				t_delayFullBatt++;
				if (t_delayFullBatt == T_DELAY_FULLBATT)
				{
					handle->control_state = BATTERY_CONTROLLER_AC_ADAPTER_SEARCH;
					t_delayFullBatt = 0;
					flag_charge = 0;
				}
			}
		}
		else 
		{
			flag_charge = 0;
			if (flag_discharge == 0)
			{
				if ((vol_bat1 < vol_bat2 || vol_bat2 < UNDER_VOLTAGE) && vol_bat1 > (V_THRESHOLD + V_HYS))
				{
					flag_discharge = 1;
					handle->control_state = BATTERY_CONTROLLER_DISCHARGE_BAT1;
				}
				else if ((vol_bat2 < vol_bat1 || vol_bat1 < UNDER_VOLTAGE) && vol_bat2 > (V_THRESHOLD + V_HYS))
				{
					flag_discharge = 2;
					handle->control_state = BATTERY_CONTROLLER_DISCHARGE_BAT2;
				}
				else 
				{
					handle->control_state = BATTERY_CONTROLLER_AC_ADAPTER_SEARCH;
				}
			}
			if (flag_discharge == 1 && vol_bat1 < UNDER_VOLTAGE) flag_discharge = 0;
			else if (flag_discharge == 2 && vol_bat2 < UNDER_VOLTAGE) flag_discharge = 0;
		}
	}
	else if (handle->batsel_mode == BATSEL_MODE_BAT1)
	{
		flag_discharge = 0;
		flag_charge = 0;
		if (vol_adap >= UNDER_VOLTAGE)
		{
			if ( (vol_bat1 > (V_THRESHOLD + V_HYS)) && (vol_bat1 < VBAT_MAX))
			{
				handle->control_state = BATTERY_CONTROLLER_CHARGE_BAT1;
			}
			else if ( (vol_bat1 < UNDER_VOLTAGE) || (VBAT_MAX - vol_bat1 < 10) )
			{
				handle->control_state = BATTERY_CONTROLLER_AC_ADAPTER_SEARCH;
			}
		}
		else 
		{
			handle->control_state = BATTERY_CONTROLLER_DISCHARGE_BAT1;
		}
	}
	else 
	{
		flag_discharge = 0;
		flag_charge = 0;
		if (vol_adap >= UNDER_VOLTAGE)
		{
			if ( (vol_bat2 > (V_THRESHOLD + V_HYS)) && (vol_bat2 < VBAT_MAX))
			{
				handle->control_state = BATTERY_CONTROLLER_CHARGE_BAT2;
			}
			else if ( (vol_bat2 < UNDER_VOLTAGE) || (VBAT_MAX - vol_bat2 < 10) )
			{
				handle->control_state = BATTERY_CONTROLLER_AC_ADAPTER_SEARCH;
			}
		}
		else 
		{
			handle->control_state = BATTERY_CONTROLLER_DISCHARGE_BAT2;
		}
	}
	if (temp_controlState != handle->control_state)
	{
		switch (handle->control_state)
		{
			case BATTERY_CONTROLLER_CHARGE_BAT1:
				Max1538_configure_state(MAX1538_STATE_CHARGE_A);
				break;
			case BATTERY_CONTROLLER_CHARGE_BAT2:
				Max1538_configure_state(MAX1538_STATE_CHARGE_B);
				break;
			case BATTERY_CONTROLLER_DISCHARGE_BAT1:
				Max1538_configure_state(MAX1538_STATE_DISCHARGE_A);
				break;
			case BATTERY_CONTROLLER_DISCHARGE_BAT2:
				Max1538_configure_state(MAX1538_STATE_DISCHARGE_B);
				break;
			case BATTERY_CONTROLLER_AC_ADAPTER_SEARCH:
				Max1538_configure_state(MAX1538_STATE_AC_ADAPTER);
				break;
			default:
				break;
		}
		temp_controlState = handle->control_state;
	}
}

/* Public functions ---------------------------------------------------------*/
void BattControllerTask_init(void){
	osThreadId_t BattControllerTask;
    const osThreadAttr_t BattControlTask_attr = {
        .name = "BattControlTask",
        .priority = (osPriority_t) osPriorityNormal,
        .stack_size = 128 * 4
    };
    BattControllerTask = osThreadNew(BattController_main, NULL, &BattControlTask_attr);
	(void)BattControllerTask;
}
