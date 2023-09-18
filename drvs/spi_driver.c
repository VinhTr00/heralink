/*
 * spi_driver.c
 *
 *  Created on: Sep 5, 2023
 *      Author: vinhtran
 */


#include "spi_driver.h"

uint8_t spi_read(SPIHandle *spi, uint8_t *RxBuff, uint16_t len)
{
	return HAL_SPI_Receive_DMA(spi->hspi, RxBuff, len);
}

uint8_t spi_read_write(SPIHandle *spi, uint8_t *TxBuff, uint8_t *RxBuff, uint16_t len)
{
	return HAL_SPI_TransmitReceive_DMA(spi->hspi, TxBuff, RxBuff, len);
}

void spi_set_cs(SPIHandle *spi, GPIO_PinState PinState)
{
	HAL_GPIO_WritePin(spi->CS_port, spi->CS_Pin, PinState);
}
