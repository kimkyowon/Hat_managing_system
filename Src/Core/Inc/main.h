/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#define LEDD1012_G_Pin GPIO_PIN_7
#define LEDD1012_G_GPIO_Port GPIOB
#define Heater_G_Pin GPIO_PIN_14
#define Heater_G_GPIO_Port GPIOC
#define UVLED_G_Pin GPIO_PIN_15
#define UVLED_G_GPIO_Port GPIOC
#define USBLED_Pin GPIO_PIN_0
#define USBLED_GPIO_Port GPIOA
#define SW1_Pin GPIO_PIN_1
#define SW1_GPIO_Port GPIOA
#define SW1_EXTI_IRQn EXTI0_1_IRQn
#define SW2_Pin GPIO_PIN_2
#define SW2_GPIO_Port GPIOA
#define SW2_EXTI_IRQn EXTI2_3_IRQn
#define EXTFAN_G_Pin GPIO_PIN_3
#define EXTFAN_G_GPIO_Port GPIOA
#define RGB_Green_G_Pin GPIO_PIN_4
#define RGB_Green_G_GPIO_Port GPIOA
#define RGB_Red_G_Pin GPIO_PIN_0
#define RGB_Red_G_GPIO_Port GPIOB
#define RGB_Blue_G_Pin GPIO_PIN_11
#define RGB_Blue_G_GPIO_Port GPIOA
#define LED12_G_Pin GPIO_PIN_3
#define LED12_G_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
