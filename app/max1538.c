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
		.BATSEL_Pin = MAX_BATSEL_Pin,
		.CHG_Pin = MAX_CHG_Pin,
		.state = MAX1538_STATE_IDLE
};

void Max1538_set_state(Max1538State state){
	max1538.state = state;
	Max1538_write_input(max1538);
}
