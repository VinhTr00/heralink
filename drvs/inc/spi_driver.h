/*
 * spi_driver.h
 *
 *  Created on: Sep 5, 2023
 *      Author: vinhtran
 */

#ifndef _SPI_DRIVER_H_
#define _SPI_DRIVER_H_

#include <stdint.h>
#include <stm32g0xx_hal.h>

typedef struct {
	GPIO_TypeDef *CS_port;
	uint16_t CS_Pin;
	SPI_HandleTypeDef *hspi;
} SPIHandle;

uint8_t spi_read_write(SPIHandle *spi, uint8_t *TxBuff, uint8_t *RxBuff, uint16_t len);
uint8_t spi_read(SPIHandle *spi, uint8_t *RxBuff, uint16_t len);
void spi_set_cs(SPIHandle *spi, GPIO_PinState PinState);



#endif /* _SPI_DRIVER_H_ */
