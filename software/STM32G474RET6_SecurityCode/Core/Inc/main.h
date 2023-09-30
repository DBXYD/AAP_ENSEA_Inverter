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
#include "stm32g4xx_hal.h"

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
#define Pwr_Enable_U_Pin GPIO_PIN_13
#define Pwr_Enable_U_GPIO_Port GPIOC
#define Pwr_Enable_V_Pin GPIO_PIN_14
#define Pwr_Enable_V_GPIO_Port GPIOC
#define Pwr_Enable_W_Pin GPIO_PIN_15
#define Pwr_Enable_W_GPIO_Port GPIOC
#define NRST_Pin GPIO_PIN_10
#define NRST_GPIO_Port GPIOG
#define USR_BTN_2_Pin GPIO_PIN_4
#define USR_BTN_2_GPIO_Port GPIOA
#define ENC_BTN_Pin GPIO_PIN_5
#define ENC_BTN_GPIO_Port GPIOA
#define ENC_BTN_EXTI_IRQn EXTI9_5_IRQn
#define ENC_BTN_A_Pin GPIO_PIN_6
#define ENC_BTN_A_GPIO_Port GPIOA
#define ENC_BTN_B_Pin GPIO_PIN_7
#define ENC_BTN_B_GPIO_Port GPIOA
#define Nucleo_NRST_Pin GPIO_PIN_0
#define Nucleo_NRST_GPIO_Port GPIOB
#define USR_LED_1_Pin GPIO_PIN_15
#define USR_LED_1_GPIO_Port GPIOA
#define USR_LED_2_Pin GPIO_PIN_10
#define USR_LED_2_GPIO_Port GPIOC
#define USR_LED_3_Pin GPIO_PIN_11
#define USR_LED_3_GPIO_Port GPIOC
#define USR_LED_4_Pin GPIO_PIN_12
#define USR_LED_4_GPIO_Port GPIOC
#define USR_BTN_1_Pin GPIO_PIN_2
#define USR_BTN_1_GPIO_Port GPIOD
#define ISO_PWM_BREAK_Pin GPIO_PIN_5
#define ISO_PWM_BREAK_GPIO_Port GPIOB
#define Soft_NRST_Pin GPIO_PIN_7
#define Soft_NRST_GPIO_Port GPIOB
#define Soft_NRST_EXTI_IRQn EXTI9_5_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
