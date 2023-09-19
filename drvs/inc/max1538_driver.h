/*
 * max1538_driver.h
 *
 *  Created on: Sep 9, 2023
 *      Author: vinhtran
 */

#ifndef _MAX1538_DRIVER_H_
#define _MAX1538_DRIVER_H_

#include <stm32g0xx_hal.h>

typedef enum 
{
	MAX1538_STATE_IDLE,
	MAX1538_STATE_DISCHARGE_A = 0,
	MAX1538_STATE_DISCHARGE_B,
	MAX1538_STATE_AC_ADAPTER,
	MAX1538_STATE_AIRLINE,
	MAX1538_STATE_RELEARN_A,
	MAX1538_STATE_RELEARN_B,
	MAX1538_STATE_CHARGE_A,
	MAX1538_STATE_CHARGE_B,
} MAX1538_STATE_E;

typedef enum 
{
	BATSEL_MODE_AUTO,
	BATSEL_MODE_BAT1,
	BATSEL_MODE_BAT2, 
} BATSEL_MODE_E;

typedef struct 
{
	GPIO_TypeDef *max1538_Port;
	GPIO_TypeDef *max1538_out_Port;
	GPIO_TypeDef *batsel_Port;
	uint16_t BATSEL1_Button;
	uint16_t BATSEL2_Button;
	uint16_t MaxCHG;
	uint16_t MaxBATSEL;
	uint16_t MaxRELRN;
	uint16_t MaxOUT0;
	uint16_t MaxOUT1;
	uint16_t MaxOUT2;
	MAX1538_STATE_E current_state;
	MAX1538_STATE_E target_state;
	BATSEL_MODE_E mode;
} Max1538_t;

uint8_t Max1538_set_state(Max1538_t* pMax, MAX1538_STATE_E state);
MAX1538_STATE_E Max1538_get_state(Max1538_t pMax, uint16_t voltage_battA);
BATSEL_MODE_E Max1538_get_mode(Max1538_t *pMax);

#endif /* _MAX1538_DRIVER_H_ */
