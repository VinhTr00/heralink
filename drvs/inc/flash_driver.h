/*
 * flash_driver.h
 *
 *  Created on: Oct 5, 2023
 *      Author: vinhtran
 */

#ifndef _FLASH_DRIVER_H_
#define _FLASH_DRIVER_H_

#include <stdint.h>
#include "stm32g0xx.h"
//#include "stm32g0xx_hal_flash.h"

typedef struct 
{
	FLASH_EraseInitTypeDef eraseFlash;
	uint32_t TypeProgram;
	uint32_t Address;
	uint64_t dataConfig;
} FlashType_t;


void Flash_Lock(void);
void Flash_Unlock(void);
uint32_t Flash_Read(uint32_t address); 
void Flash_Write(FlashType_t handle, uint64_t data);
uint8_t Flash_Erase(FlashType_t handle);


#endif /* _FLASH_DRIVER_H_ */
