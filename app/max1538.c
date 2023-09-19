/*
 * max1538.c
 *
 *  Created on: Sep 9, 2023
 *      Author: vinhtran
 */

#include "max1538.h"
#include "gpio.h"

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

