/*
 * battery_controller.h
 *
 *  Created on: Sep 9, 2023
 *      Author: vinhtran
 */

#ifndef _BATTERY_CONTROLLER_H_
#define _BATTERY_CONTROLLER_H_

#include "shared_resource.h"

typedef enum {
	BATTERY_CONTROLLER_CHARGE_BAT1,
	BATTERY_CONTROLLER_CHARGE_BAT2,
	BATTERY_CONTROLLER_DISCHARGE_BAT1,
	BATTERY_CONTROLLER_DISCHARGE_BAT2,
	BATTERY_CONTROLLER_AC_ADAPTER_SEARCH
} BATTERY_CONTROLLER_STATE_E;

void BattControllerTask_init(void);

#endif /* _BATTERY_CONTROLLER_H_ */
