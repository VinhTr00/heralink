/*
 * max1538.c
 *
 *  Created on: Sep 9, 2023
 *      Author: vinhtran
 */

/* Includes ------------------------------------------------------------------*/
#include "max1538.h"
#include "max1538_driver.h"
#include "gpio.h"
#include "adc_convert.h"
#include "cmsis_os.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static Max1538_t max1538 = {
	.max1538_Port = GPIOD,
	.max1538_out_Port = GPIOB,
	.batsel_Port = GPIOD,
	.BATSEL1_Button = BATSEL1_BT_Pin,
	.BATSEL2_Button = BATSEL2_BT_Pin,
	.MaxCHG = MAX_CHG_Pin,
	.MaxBATSEL = MAX_BATSEL_Pin,
	.MaxRELRN = MAX_RELEARN_Pin,
	.MaxOUT0 = MAX_OUT0_Pin,
	.MaxOUT1 = MAX_OUT1_Pin,
	.MaxOUT2 = MAX_OUT2_Pin,
};

/* Private function prototypes -----------------------------------------------*/
static void Max1538Task_main(void *argument);
static void Max1538Task_update(Max1538_t *pMax);

/* Private functions ---------------------------------------------------------*/
void Max1538Task_update(Max1538_t *pMax)
{
	uint16_t volA = AdcGet_voltage(VOLTAGE_BAT1);
	Max1538_get_mode_batsel(pMax);
	Max1538_get_state(pMax, volA);	
}

void Max1538Task_main(void *argument){
	static MAX1538_STATE_E temp_target_state;
	while (1)
	{
		Max1538Task_update(&max1538);
		if (temp_target_state != max1538.target_state){
			Max1538_set_state(&max1538);
			temp_target_state = max1538.target_state;
		}
		osDelay(pdMS_TO_TICKS(500));
	}
}

/* Public functions ---------------------------------------------------------*/
void Max1538_init(void)
{
	osThreadId_t Max1538Task;
    const osThreadAttr_t Max1538Task_attributes = {
        .name = "Max1538 Task",
        .priority = (osPriority_t) osPriorityHigh,
        .stack_size = 128 * 4
    };
	Max1538Task = osThreadNew(Max1538Task_main, NULL, &Max1538Task_attributes);
	(void)Max1538Task;
}

BATSEL_MODE_E Max1538_release_mode_batsel(void){
	return max1538.mode;
}

MAX1538_STATE_E Max1538_release_state(void){
	return max1538.current_state;
}
 
void Max1538_configure_state(MAX1538_STATE_E state){
	max1538.target_state = state;
}
