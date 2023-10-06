/*
 * flash_management.c
 *
 *  Created on: Oct 5, 2023
 *      Author: vinhtran
 */

/* Includes ------------------------------------------------------------------*/
#include "flash_management.h"
#include "main.h"
#include "cmsis_os.h"

/* Private typedef -----------------------------------------------------------*/
typedef struct 
{
    
};

/* Private define ------------------------------------------------------------*/
#define NUMBER_BYTE_CONFIG						5

#define FLASH_USER_START_ADDR                   0x0801F800
#define FLASH_USER_END_ADDR                    	0x0801FFFF

#define LOW_VOLTAGE_LOW_BYTE_DEFAULT_VALUE		0x10
#define LOW_VOLTAGE_HIGH_BYTE_DEFAULT_VALUE		0x27
#define HIGH_CURRENT_LOW_BYTE_DEFAULT_VALUE		0x10
#define HIGH_CURRENT_HIGH_BYTE_DEFAULT_VALUE	0x27
#define BUZZER_ENABLE_DEFAULT_VALUE				0x01

/* Private variables ---------------------------------------------------------*/
static FlashType_t FlashHandle;
uint8_t buffer_t[NUMBER_BYTE_CONFIG] = {0x10,0x27,0x10,0x27,0x01};
uint8_t buffer_value[NUMBER_BYTE_CONFIG];

/* Private function prototypes -----------------------------------------------*/
static void FlashTask_main(void * argument);
static void FlashInit(void);
static uint32_t FlashGetPage(uint32_t addr);
static void Flash_write_storage(FlashType_t handle);
static void FlashData_encode(FlashType_t *handle, uint8_t *buffer);
static void FlashData_decode(FlashType_t handle, uint8_t *buffer);

/* Private functions ---------------------------------------------------------*/
void FlashInit(void)
{
	FlashHandle.Address = FLASH_USER_START_ADDR;
	FlashHandle.TypeProgram = FLASH_TYPEPROGRAM_DOUBLEWORD;
    FlashHandle.eraseFlash.TypeErase = FLASH_TYPEERASE_PAGES;
    FlashHandle.eraseFlash.Page = FlashGetPage(FLASH_USER_START_ADDR);
    FlashHandle.eraseFlash.NbPages = FlashGetPage(FLASH_USER_END_ADDR) - FlashGetPage(FLASH_USER_START_ADDR) + 1;
    FlashHandle.dataConfig = Flash_Read(FLASH_USER_START_ADDR);

}

void FlashData_encode(FlashType_t *handle, uint8_t *buffer)
{
    uint64_t data = 0;
    uint8_t counter = 0;
    while (counter < NUMBER_BYTE_CONFIG)
    {
        data = (data << 8) | buffer[counter++];
    }
    handle->dataConfig = data;
}

static void FlashData_decode(FlashType_t handle, uint8_t *buffer)
{
	uint8_t counter = NUMBER_BYTE_CONFIG;
	uint64_t data = handle.dataConfig;
	while (counter > 0)
	{
		buffer[--counter] = (uint8_t)data;
		data = data >> 8;
	}
}

void Flash_write_storage(FlashType_t handle)
{
	Flash_Unlock();
    Flash_Erase(handle);
    Flash_Write(handle, handle.dataConfig);
    Flash_Lock();
}

uint32_t FlashGetPage(uint32_t addr)
{
  return (addr - FLASH_BASE) / FLASH_PAGE_SIZE;
}

void Blink_led(uint32_t ms){
	HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
	osDelay(ms);
}

void FlashTask_main(void * argument)
{
    FlashData_encode(&FlashHandle, buffer_t);
    FlashData_decode(FlashHandle, buffer_value);
    while (1)
    {

    }
}

/* Public functions ---------------------------------------------------------*/
void FlashTask_init(void)
{
	osThreadId_t FlashTask;
    const osThreadAttr_t FlashTask_attr = {
        .name = "Flash Task",
        .priority = (osPriority_t) osPriorityHigh,
        .stack_size = 128 * 4
    };
	FlashTask = osThreadNew(FlashTask_main, NULL, &FlashTask_attr);
	(void)FlashTask;
	FlashInit();
}





