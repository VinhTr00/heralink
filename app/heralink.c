/*
 * heralink.c
 *
 *  Created on: Sep 18, 2023
 *      Author: Admin
 */


#include "heralink.h"
#include "battery_controller.h"
#include "spi_slave.h"
#include "max1538.h"
#include "adc_convert.h"

int heralink_main_init (void)
{
	AdcTask_init();
	SlTask_init();
	BattControllerTask_init();

	return 1;
}
