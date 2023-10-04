/*
 * battery.h
 *
 *  Created on: Sep 28, 2023
 *      Author: vinhtran
 */

#ifndef _BATTERY_H_
#define _BATTERY_H_

#include <stdint.h>

#define OVER_VOLTAGE			20000	//mV
#define UNDER_VOLTAGE			12000	//mV

#define OVER_TEMPERATURE        100
#define UNDER_TEMPERATURE       10

typedef enum {
    BATTERY_1,
    BATTERY_2,
} BATTERY_INDEX_E;

#endif /* _BATTERY_H_ */
