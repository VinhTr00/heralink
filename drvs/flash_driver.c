/*
 * flash_driver.c
 *
 *  Created on: Oct 5, 2023
 *      Author: vinhtran
 */


#include "flash_driver.h"
#include "stm32g0xx_hal.h"

void Flash_Lock(void)
{
	HAL_FLASH_Lock();
}
void Flash_Unlock(void)
{
	HAL_FLASH_Unlock();
}

uint32_t Flash_Read(uint32_t address)
{
	return (*(__IO uint32_t*) address);
}

void Flash_Write(FlashType_t handle, uint64_t data)
{
	HAL_FLASH_Program(handle.TypeProgram, handle.Address, data);
}

uint8_t Flash_Erase(FlashType_t handle)
{
	uint32_t pageError;
	return HAL_FLASHEx_Erase(&handle.eraseFlash, &pageError);
}


