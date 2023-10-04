/*
 * max1538_driver.c
 *
 *  Created on: Sep 9, 2023
 *      Author: vinhtran
 */

/* Includes ------------------------------------------------------------------*/
#include "max1538_driver.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define UNDERVOL_BATT_A		4650 //mV
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static void Max1538_write_input(Max1538_t *pMax);
static uint8_t Max1538_read_state(Max1538_t pxMax);
static BATSEL_MODE_E Max1538_read_batsel(Max1538_t pxMax);

/* Private functions ---------------------------------------------------------*/
void Max1538_write_input(Max1538_t *pMax)
{
	switch (pMax->target_state)
	{
		case MAX1538_STATE_CHARGE_A:
			HAL_GPIO_WritePin(pMax->max1538_Port, pMax->MaxCHG, 1);
			HAL_GPIO_WritePin(pMax->max1538_Port, pMax->MaxBATSEL, 0);
			break;
		case MAX1538_STATE_CHARGE_B:
			HAL_GPIO_WritePin(pMax->max1538_Port, pMax->MaxCHG, 1);
			HAL_GPIO_WritePin(pMax->max1538_Port, pMax->MaxBATSEL, 1);
			break;
		case MAX1538_STATE_DISCHARGE_A:
			HAL_GPIO_WritePin(pMax->max1538_Port, pMax->MaxCHG, 0);
			HAL_GPIO_WritePin(pMax->max1538_Port, pMax->MaxBATSEL, 0);
			break;
		case MAX1538_STATE_DISCHARGE_B:
			HAL_GPIO_WritePin(pMax->max1538_Port, pMax->MaxCHG, 0);
			HAL_GPIO_WritePin(pMax->max1538_Port, pMax->MaxBATSEL, 1);
			break;
		case MAX1538_STATE_AC_ADAPTER:
			HAL_GPIO_WritePin(pMax->max1538_Port, pMax->MaxCHG, 0);
			HAL_GPIO_WritePin(pMax->max1538_Port, pMax->MaxBATSEL, 0);
		default:
			break;
	}
}

uint8_t Max1538_read_state(Max1538_t pxMax)
{
	uint8_t out0 = HAL_GPIO_ReadPin(pxMax.max1538_out_Port, pxMax.MaxOUT0);
	uint8_t out1 = HAL_GPIO_ReadPin(pxMax.max1538_out_Port, pxMax.MaxOUT1);
	uint8_t out2 = HAL_GPIO_ReadPin(pxMax.max1538_out_Port, pxMax.MaxOUT2);
	
	return ((out2 << 2) | (out1 << 1) | out0);
}

BATSEL_MODE_E Max1538_read_batsel(Max1538_t pxMax)
{
	uint8_t batsel1 = HAL_GPIO_ReadPin(pxMax.batsel_Port, pxMax.BATSEL1_Button);
	uint8_t batsel2 = HAL_GPIO_ReadPin(pxMax.batsel_Port, pxMax.BATSEL2_Button);
	if (batsel1 == 1)
	{
		return BATSEL_MODE_BAT1;
	}
	else if (batsel2 == 1)
	{
		return BATSEL_MODE_BAT2;
	}
	return BATSEL_MODE_AUTO;
}

/* Public functions ---------------------------------------------------------*/
void Max1538_set_state(Max1538_t* pMax)
{
	Max1538_write_input(pMax);
}

MAX1538_STATE_E Max1538_get_state(Max1538_t* pMax, uint16_t voltage_battA)
{
	MAX1538_STATE_E temp_state = Max1538_read_state(*pMax);
	if (temp_state == 0)
	{
		if (voltage_battA > UNDERVOL_BATT_A)
		{
			temp_state = MAX1538_STATE_DISCHARGE_A;
		}
		else 
		{
			temp_state = MAX1538_STATE_IDLE;
		}
	}
	else {
		temp_state = temp_state + 1;
	}
	pMax->current_state = temp_state;
	return temp_state;
}

BATSEL_MODE_E Max1538_get_mode_batsel(Max1538_t *pMax)
{
	BATSEL_MODE_E temp_mode = Max1538_read_batsel(*pMax);
	pMax->mode = temp_mode;
	return temp_mode;
}
