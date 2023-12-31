/*
 * spi_slave.h
 *
 *  Created on: Sep 2, 2023
 *      Author: vinhtran
 */

#ifndef _SPI_SLAVE_H_
#define _SPI_SLAVE_H_

#include <stdint.h>

typedef enum {
	LOW_VOLTAGE_LOW_BYTE = 0x10,
	LOW_VOLTAGE_HIGH_BYTE,
	HIGH_CURRENT_LOW_BYTE,
	HIGH_CURRENT_HIGH_BYTE,
	BUZZER_ENABLE,
	BAT1_VOLTAGE_LOW_BYTE = 0x50,
	BAT1_VOLTAGE_HIGH_BYTE,
	BAT2_VOLTAGE_LOW_BYTE,
	BAT2_VOLTAGE_HIGH_BYTE,
	ADT_VOLTAGE_LOW_BYTE,
	ADT_VOLTAGE_HIGH_BYTE,
	SYS_VOLTAGE_LOW_BYTE,
	SYS_VOLTAGE_HIGH_BYTE,
	AIR_TEMPERATURE_LOW_BYTE,
	AIR_TEMPERATURE_HIGH_BYTE,
	RF1_TEMPERATURE_LOW_BYTE,
	RF1_TEMPERATURE_HIGH_BYTE,
	RF2_TEMPERATURE_LOW_BYTE,
	RF2_TEMPERATURE_HIGH_BYTE,
	BAT1_TEMPERATURE_LOW_BYTE,
	BAT1_TEMPERATURE_HIGH_BYTE,
	BAT2_TEMPERATURE_LOW_BYTE,
	BAT2_TEMPERATURE_HIGH_BYTE,
	SYS_CURRENT_LOW_BYTE,
	SYS_CURRENT_HIGH_BYTE,
	CHG_CURRENT_LOW_BYTE,
	CHG_CURRENT_HIGH_BYTE,
	MAX1538_MODE,
	BATTERY_USAGE,
	ADAPTER_STATUS,
	POWER_WARNING,
} SharedMemoryMap;

typedef enum {
	SLAVE_SPI_BUSY_MODE,
	SLAVE_SPI_IDLE_MODE,
} SlaveSPIMode;


void SlTask_init(void);
uint8_t SlTask_get_configuration(void);
uint8_t SlTask_set_configuration(void);

#endif /* _SPI_SLAVE_H_ */
