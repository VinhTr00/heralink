/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOF
#define BAT1_VOL_Pin GPIO_PIN_0
#define BAT1_VOL_GPIO_Port GPIOA
#define BAT2_VOL_Pin GPIO_PIN_1
#define BAT2_VOL_GPIO_Port GPIOA
#define SYS_VOL_Pin GPIO_PIN_2
#define SYS_VOL_GPIO_Port GPIOA
#define SYS_CUR_Pin GPIO_PIN_4
#define SYS_CUR_GPIO_Port GPIOA
#define LED_GREEN_Pin GPIO_PIN_5
#define LED_GREEN_GPIO_Port GPIOA
#define ADT_VOL_Pin GPIO_PIN_6
#define ADT_VOL_GPIO_Port GPIOA
#define AIR_TEMP_Pin GPIO_PIN_7
#define AIR_TEMP_GPIO_Port GPIOA
#define BAT2_TEMP_Pin GPIO_PIN_0
#define BAT2_TEMP_GPIO_Port GPIOB
#define BAT1_TEMP_Pin GPIO_PIN_1
#define BAT1_TEMP_GPIO_Port GPIOB
#define RF2_TEMP_Pin GPIO_PIN_2
#define RF2_TEMP_GPIO_Port GPIOB
#define RF1_TEMP_Pin GPIO_PIN_10
#define RF1_TEMP_GPIO_Port GPIOB
#define MAX_OUT0_Pin GPIO_PIN_13
#define MAX_OUT0_GPIO_Port GPIOB
#define MAX_OUT1_Pin GPIO_PIN_14
#define MAX_OUT1_GPIO_Port GPIOB
#define MAX_OUT2_Pin GPIO_PIN_15
#define MAX_OUT2_GPIO_Port GPIOB
#define BUZZER_PWM_Pin GPIO_PIN_8
#define BUZZER_PWM_GPIO_Port GPIOA
#define FAN1_PWM_Pin GPIO_PIN_9
#define FAN1_PWM_GPIO_Port GPIOA
#define SPI1_NSS_Pin GPIO_PIN_9
#define SPI1_NSS_GPIO_Port GPIOD
#define SPI1_NSS_EXTI_IRQn EXTI4_15_IRQn
#define FAN2_PWM_Pin GPIO_PIN_10
#define FAN2_PWM_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define MAX_BATSEL_Pin GPIO_PIN_0
#define MAX_BATSEL_GPIO_Port GPIOD
#define MAX_RELEARN_Pin GPIO_PIN_1
#define MAX_RELEARN_GPIO_Port GPIOD
#define MAX_CHG_Pin GPIO_PIN_2
#define MAX_CHG_GPIO_Port GPIOD
#define BATSEL1_BT_Pin GPIO_PIN_3
#define BATSEL1_BT_GPIO_Port GPIOD
#define BATSEL2_BT_Pin GPIO_PIN_4
#define BATSEL2_BT_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
