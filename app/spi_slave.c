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
#include "spi_driver.h"
#include "adc_convert.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define LEN_BUFFER 30

/* Private function prototypes -----------------------------------------------*/
static void SlTask_main(void *argument);
static void SlTask_encode(uint8_t *packet);
static uint8_t SlDecode_register(uint8_t *RxData);

/* Private variables ---------------------------------------------------------*/
static SPIHandle spi_handle = {
		.CS_Pin = SPI1_NSS_Pin,
		.CS_port = SPI1_NSS_GPIO_Port,
		.hspi = &hspi1
};
static uint8_t TxBuffer[LEN_BUFFER], RxBuffer[LEN_BUFFER], shared_memory[200], dummy_read_write[LEN_BUFFER];
uint64_t counter_error = 0;
static bool spi_ready = false;

osEventFlagsId_t Slave_ready_id;

static enum {
	WRITE_FLAG,
	READ_FLAG
};

void SlTask_init(void)
{
	osThreadId_t SlaveTask;
	const osThreadAttr_t SlaveTask_attributes = {
	  .name = "SlaveTask",
	  .priority = (osPriority_t) osPriorityNormal,
	  .stack_size = 128 * 4
	};
	SlaveTask = osThreadNew(SlTask_main, NULL, &SlaveTask_attributes);
	Slave_ready_id = osEventFlagsNew(NULL);
	(void)SlaveTask;
}

static void SlTask_main(void *argument)
{
//	spi_read(&spi_handle, RxBuffer, 1);
//	spi_read_write(&spi_handle, dummy_read_write, RxBuffer, 1);
	uint8_t *tempBuffer, len;
	while (1){
		/* Test */
		osEventFlagsWait(Slave_ready_id, 0xDD, osFlagsWaitAny, osWaitForever);
		SlTask_encode(shared_memory);
		uint8_t flag_decode = SlDecode_register(&RxBuffer[0]);
		if (flag_decode == WRITE_FLAG){
			for (uint8_t i = LOW_VOLTAGE_LOW_BYTE; i < BUZZER_ENABLE + 1; i++){
				if (RxBuffer[0] == i){
					tempBuffer = &shared_memory[i];
					len = 2;
					spi_read_write(&spi_handle, dummy_read_write, tempBuffer, len);
					break;
				}
			}
		}
		else {
			for (uint8_t i = BAT1_VOLTAGE_LOW_BYTE; i < POWER_WARNING + 1; i++){
				if (RxBuffer[0] == i){
					tempBuffer = &shared_memory[i];
					len = POWER_WARNING + 1 - i;
					spi_read_write(&spi_handle, tempBuffer, dummy_read_write, len);
					break;
				}
			}
			for (uint8_t i = LOW_VOLTAGE_LOW_BYTE; i < BUZZER_ENABLE + 1; i++){
				if (RxBuffer[0] == i){
					tempBuffer = &shared_memory[i];
					len = BUZZER_ENABLE + 1 - i;
					spi_read_write(&spi_handle, tempBuffer, dummy_read_write, len);
					break;
				}
			}
		}
	}
}

static void SlTask_encode(uint8_t *packet)
{
	uint8_t index_packet = BAT1_VOLTAGE_LOW_BYTE;
	for (uint8_t i = BAT1_VOLTAGE_LOW_BYTE; i <= SYS_VOLTAGE_HIGH_BYTE; i+=2)
	{
		packet[i] = AdcGet_voltage(index_packet - BAT1_VOLTAGE_LOW_BYTE);
		packet[i+1] = AdcGet_voltage(index_packet - BAT1_VOLTAGE_LOW_BYTE) >> 8;
		index_packet++;
	}
	index_packet = AIR_TEMPERATURE_LOW_BYTE;
	for (uint8_t i = AIR_TEMPERATURE_LOW_BYTE; i <= BAT2_TEMPERATURE_HIGH_BYTE; i+=2)
	{
		packet[i]= AdcGet_temperature(index_packet - AIR_TEMPERATURE_LOW_BYTE);
		packet[i+1] = AdcGet_temperature(index_packet - AIR_TEMPERATURE_LOW_BYTE) >> 8;
		index_packet++;
	}
	index_packet = SYS_CURRENT_LOW_BYTE;
	for (uint8_t i = SYS_CURRENT_LOW_BYTE; i <= CHG_CURRENT_HIGH_BYTE; i+=2)
	{
		packet[i]= AdcGet_current(index_packet - SYS_CURRENT_LOW_BYTE);
		packet[i+1] = AdcGet_current(index_packet - SYS_CURRENT_LOW_BYTE) >> 8;
		index_packet++;
	}
}

static uint8_t SlDecode_register(uint8_t *RxData){
	uint8_t tempData = *RxData & 0x7F;
	if (tempData == *RxData){
		return READ_FLAG;
	}
	else {
		return WRITE_FLAG;
	}
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

void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)
{
	spi_ready = false;
	memset(RxBuffer, 0, LEN_BUFFER);
	HAL_SPI_DMAStop(spi_handle.hspi);
	__HAL_RCC_SPI1_FORCE_RESET();
	__HAL_RCC_SPI1_RELEASE_RESET();
//	spi_read_write(&spi_handle, (uint8_t *)TxBuffer, &RxBuffer[0], 1);
}


void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{
	spi_ready = true;
	osEventFlagsSet(Slave_ready_id, 0xDD);
	spi_read_write(&spi_handle, &dummy_read_write, &RxBuffer[0], 1);

}


