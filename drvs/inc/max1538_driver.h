/*
 * max1538_driver.h
 *
 *  Created on: Sep 9, 2023
 *      Author: vinhtran
 */

#ifndef _MAX1538_DRIVER_H_
#define _MAX1538_DRIVER_H_

#include <stm32g0xx_hal.h>

typedef enum {
	MAX1538_STATE_CHARGE_A,
	MAX1538_STATE_CHARGE_B,
	MAX1538_STATE_RELEARN_A,
	MAX1538_STATE_RELEARN_B,
	MAX1538_STATE_AC_ADAPTER,
	MAX1538_STATE_DISCHARGE_A,
	MAX1538_STATE_DISCHARGE_B,
	MAX1538_STATE_IDLE
} Max1538State;

typedef struct {
	GPIO_TypeDef *max1538_Port;
	uint16_t CHG_Pin;
	uint16_t BATSEL_Pin;
	Max1538State state;
} Max1538_t;

void Max1538_write_input(Max1538_t pMax);


#endif /* INC_MAX1538_DRIVER_H_ */
