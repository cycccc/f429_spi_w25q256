/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "../user_bsp/printf/bsp_printf.h"
#include "../user_bsp/w25qxx/bsp_w25qxx.h"
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
/* USER CODE BEGIN Private defines */

//LED define----------------------//
#define led_red   {HAL_GPIO_WritePin(GPIOH,GPIO_PIN_10,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOH,GPIO_PIN_11,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOH,GPIO_PIN_12,GPIO_PIN_SET);}
#define led_green {HAL_GPIO_WritePin(GPIOH,GPIO_PIN_10,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOH,GPIO_PIN_11,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOH,GPIO_PIN_12,GPIO_PIN_SET);}
#define led_blue  {HAL_GPIO_WritePin(GPIOH,GPIO_PIN_10,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOH,GPIO_PIN_11,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOH,GPIO_PIN_12,GPIO_PIN_RESET);}
#define led_black {HAL_GPIO_WritePin(GPIOH,GPIO_PIN_10,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOH,GPIO_PIN_11,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOH,GPIO_PIN_12,GPIO_PIN_SET);}
#define led_white {HAL_GPIO_WritePin(GPIOH,GPIO_PIN_10,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOH,GPIO_PIN_11,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOH,GPIO_PIN_12,GPIO_PIN_RESET);}
//--------------------------------//

//SD_Card-------------------------//
#define SD_Card_Model()   {HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_RESET);    /*����WiFiģ��*/                   \
                             HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);     /*����PA8,��FATFS��Ϊ���Ѿ�����*/\
                          }
//--------------------------------//
                      

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
