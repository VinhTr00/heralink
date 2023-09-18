/*
 * battery_controller.h
 *
 *  Created on: Sep 9, 2023
 *      Author: vinhtran
 */

#ifndef _BATTERY_CONTROLLER_H_
#define _BATTERY_CONTROLLER_H_

#include "max1538.h"

typedef enum {
	BATTERY_CONTROLLER_CHARGE_BAT1,
	BATTERY_CONTROLLER_CHARGE_BAT2,
	BATTERY_CONTROLLER_DISCHARGE_BAT1,
	BATTERY_CONTROLLER_DISCHARGE_BAT2,
	BATTERY_CONTROLLER_AC_ADAPTER_SEARCH
} BatteryControllerState;

typedef enum {
	BATSEL_MODE_AUTO,
	BATSEL_MODE_BAT1,
	BATSEL_MODE_BAT2
} BatselMode;

int BattControllerTask_init(void);

#endif /* _BATTERY_CONTROLLER_H_ */
