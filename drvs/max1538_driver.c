/*
 * max1538_driver.c
 *
 *  Created on: Sep 9, 2023
 *      Author: vinhtran
 */


#include "max1538_driver.h"


void Max1538_write_input(Max1538_t pMax){
	switch (pMax.state){
		case MAX1538_STATE_CHARGE_A:
			HAL_GPIO_WritePin(pMax.max1538_Port, pMax.CHG_Pin, 1);
			HAL_GPIO_WritePin(pMax.max1538_Port, pMax.BATSEL_Pin, 0);
			break;
		case MAX1538_STATE_CHARGE_B:
			HAL_GPIO_WritePin(pMax.max1538_Port, pMax.CHG_Pin, 1);
			HAL_GPIO_WritePin(pMax.max1538_Port, pMax.BATSEL_Pin, 1);
			break;
		case MAX1538_STATE_DISCHARGE_A:
			HAL_GPIO_WritePin(pMax.max1538_Port, pMax.CHG_Pin, 0);
			HAL_GPIO_WritePin(pMax.max1538_Port, pMax.BATSEL_Pin, 0);
			break;
		case MAX1538_STATE_DISCHARGE_B:
			HAL_GPIO_WritePin(pMax.max1538_Port, pMax.CHG_Pin, 0);
			HAL_GPIO_WritePin(pMax.max1538_Port, pMax.BATSEL_Pin, 1);
			break;
		default:
			break;
	}
}

