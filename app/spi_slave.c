/*
 * spi_slave.c
 *
 *  Created on: Sep 2, 2023
 *      Author: vinhtran
 */

#include "gpio.h"
#include "spi.h"
#include "cmsis_os.h"
#include "spi_slave.h"
#include "adc_convert.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define LEN_BUFFER 30

/* Private function prototypes -----------------------------------------------*/
static void SlTask_main(void *argument);
static void SlTask_encode(uint8_t *packet);
/* Private variables ---------------------------------------------------------*/
static SPIHandle spi_handle = {
		.CS_Pin = SPI1_NSS_Pin,
		.CS_port = SPI1_NSS_GPIO_Port,
		.hspi = &hspi1
};
static uint8_t RxBuffer[LEN_BUFFER], shared_memory[200];
uint8_t TxBuffer[LEN_BUFFER];

uint64_t counter_error = 0;
uint16_t bat1_vol;
static bool spi_ready = false;

osThreadId_t SlaveTask;
osEventFlagsId_t Slave_ready_id;

int SlTask_init(void)
{
	const osThreadAttr_t SlaveTask_attributes = {
	  .name = "SlaveTask",
	  .priority = (osPriority_t) osPriorityNormal,
	  .stack_size = 128 * 10
	};
	SlaveTask = osThreadNew(SlTask_main, NULL, &SlaveTask_attributes);
	Slave_ready_id = osEventFlagsNew(NULL);
	(void)SlaveTask;

	return 1;
}

static void SlTask_main(void *argument)
{
	spi_read(&spi_handle, RxBuffer, 1);
//	spi_read_write(&spi_handle, (uint8_t *)TxBuffer, &RxBuffer[0], 1);
	uint8_t *tempBuffer = shared_memory;
	while (1){
//		if (RxBuffer[0] == 0x)
//		bat1_vol = AdcGet_voltage(VOLTAGE_BAT1);
//		TxBuffer[BAT1_VOLTAGE_LOW_BYTE - BAT1_CURRENT_LOW_BYTE] = bat1_vol;
//		TxBuffer[BAT1_VOLTAGE_HIGH_BYTE - BAT1_CURRENT_LOW_BYTE] = bat1_vol >> 8;
//		sprintf((char *)TxBuffer, "Slave send: %d", counter);
//		osDelay(1000);

		/* Test */
		SlTask_encode(shared_memory);
		osEventFlagsWait(Slave_ready_id, 0xDD, osFlagsWaitAny, osWaitForever);
		for (uint8_t  i = BAT1_VOLTAGE_LOW_BYTE; i < POWER_WARNING + 1; i++){
			if (RxBuffer[0] == i){
				tempBuffer = &shared_memory[i];
				uint8_t len = POWER_WARNING - i;
				spi_read_write(&spi_handle, tempBuffer, shared_memory, len);
//				HAL_SPI_Transmit_DMA(&spi_handle, tempBuffer, len);
				break;
			}
		}
	}
}

static void SlTask_encode(uint8_t *packet)
{
	uint8_t index_packet = BAT1_VOLTAGE_LOW_BYTE;
	for (uint8_t i = BAT1_VOLTAGE_LOW_BYTE; i <= SYS_VOLTAGE_HIGH_BYTE + 1; i+=2)
	{
		packet[i] = AdcGet_voltage(index_packet - BAT1_VOLTAGE_LOW_BYTE);
		packet[i+1] = AdcGet_voltage(index_packet - BAT1_VOLTAGE_LOW_BYTE) >> 8;
		index_packet++;
	}
	index_packet = AIR_TEMPERATURE_LOW_BYTE;
	for (uint8_t i = AIR_TEMPERATURE_LOW_BYTE; i <= BAT2_TEMPERATURE_HIGH_BYTE + 1; i+=2)
	{
		packet[i]= AdcGet_temperature(index_packet - AIR_TEMPERATURE_LOW_BYTE);
		packet[i+1] = AdcGet_temperature(index_packet - AIR_TEMPERATURE_LOW_BYTE) >> 8;
		index_packet++;
	}
	index_packet = SYS_CURRENT_LOW_BYTE;
	for (uint8_t i = SYS_CURRENT_LOW_BYTE; i <= CHG_CURRENT_HIGH_BYTE + 1; i+=2)
	{
		packet[i]= AdcGet_current(index_packet - SYS_CURRENT_LOW_BYTE);
		packet[i+1] = AdcGet_current(index_packet - SYS_CURRENT_LOW_BYTE) >> 8;
		index_packet++;
	}
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi){

}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
//	spi_read_write(&spi_handle, (uint8_t *)TxBuffer, &RxBuffer[myIndex], 1);
//	myIndex++;

}

void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
	counter_error++;
//	while (HAL_GPIO_ReadPin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin) == 1)
//	{
//
//	}
//	HAL_SPI_DMAStop(spi_handle.hspi);
//	__HAL_RCC_SPI1_FORCE_RESET();
//	__HAL_RCC_SPI1_RELEASE_RESET();
//	spi_read_write(&spi_handle, (uint8_t *)TxBuffer, (uint8_t *)RxBuffer, LEN_BUFFER);
}

void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin){
	spi_ready = false;
	memset(RxBuffer, 0, LEN_BUFFER);
	HAL_SPI_DMAStop(spi_handle.hspi);
	__HAL_RCC_SPI1_FORCE_RESET();
	__HAL_RCC_SPI1_RELEASE_RESET();
	spi_read_write(&spi_handle, (uint8_t *)TxBuffer, &RxBuffer[0], 1);
}


void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin){
	spi_ready = true;
	osEventFlagsSet(Slave_ready_id, 0xDD);
//	spi_read_write(&spi_handle, &TxBuffer[index], &RxBuffer[index], 1);

}


