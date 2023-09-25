/*
 * battery_monitor.c
 *
 *  Created on: Sep 24, 2023
 *      Author: vinhtran
 */


/* Includes ------------------------------------------------------------------*/
#include "battery_monitor.h"
#include "cmsis_os.h"
#include "adc_convert.h"

/* Private typedef -----------------------------------------------------------*/
typedef struct 
{
    
};

/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static void BattController_main(void *argument);

/* Private functions ---------------------------------------------------------*/
void BattController_main(void *argument)
{
    while (1)
    {

    }
}

/* Public functions ---------------------------------------------------------*/
void BattControllerTask_init(void){
    osThreadId_t BattMonitorTask;
    const osThreadAttr_t BattMonitorTask_attr = {
        .name = "Battery Monitor",
        .priority = (osPriority_t) osPriorityNormal,
        .stack_size = 128 * 4
    };
    BattMonitorTask = osThreadNew(BattController_main, NULL, &BattMonitorTask_attr);
    (void) BattMonitorTask;
}