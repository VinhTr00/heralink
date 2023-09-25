/*
 * battery_monitor.h
 *
 *  Created on: Sep 24, 2023
 *      Author: vinhtran
 */

#ifndef _BATTERY_MONITOR_H_
#define _BATTERY_MONITOR_H_

#include <stdint.h>

typedef enum {
    BATTERY_STATE_WORK,
    BATTERY_STATE_ALERT,
} BATTERY_STATE_E;

typedef enum {
    POWER_WARNING_FLAG_OK,
    POWER_WARNING_FLAG_OVER_CURRENT,
    POWER_WARNING_FLAG_OVER_VOLTAGE,
    POWER_WARNING_FLAG_UNDER_VOLTAGE,
    POWER_WARNING_FLAG_OVER_TEMPERATURE,
    POWER_WARNING_FLAG_UNDER_TEMPERATURE,
} POWER_WARNING_FLAGS_E;

void BattMonitorTask_init(void);


#endif /* _BATTERY_MONITOR_H_ */
