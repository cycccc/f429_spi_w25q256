/**
 *******************************Copyright (c)************************************
 *
 *                   (c) Copyright 2021, CY, China, QD.
 *                           All Rights Reserved
 *
 *                           By(南京万福祥电子科技有限公司)
 *                           http://www.njwfx.com
 *
 *----------------------------------文件信息------------------------------------
 * 文件名称: bsp_typedef.h
 * 创建人员: CY
 * 创建日期: 2021-02-10
 * 文档描述: 自己的宏定义归总
 *
 *----------------------------------版本信息------------------------------------
 * 版本代号: V1.0
 * 版本说明:
 *          |-1.0
 * 	         |-2021-02-10
 * 	          |-初始版本
 *------------------------------------------------------------------------------
 */

#ifndef __BSP_TYPEDEF_H_
#define __BSP_TYPEDEF_H_

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#ifdef STM32F103xE
    #include "core_cm3.h"
    #include "stm32f1xx_hal.h"
#endif /* STM32F103xE */

#ifdef STM32F429xx
   #include "core_cm4.h"
   #include "stm32f4xx_hal.h"
#endif /* STM32F429xx */



typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;  /*!< Read Only */
typedef const int16_t sc16;  /*!< Read Only */
typedef const int8_t sc8;   /*!< Read Only */

typedef __IO int32_t  vs32;
typedef __IO int16_t  vs16;
typedef __IO int8_t   vs8;

typedef __I int32_t vsc32;  /*!< Read Only */
typedef __I int16_t vsc16;  /*!< Read Only */
typedef __I int8_t vsc8;   /*!< Read Only */

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;  /*!< Read Only */
typedef const uint16_t uc16;  /*!< Read Only */
typedef const uint8_t uc8;   /*!< Read Only */

typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

typedef __I uint32_t vuc32;  /*!< Read Only */
typedef __I uint16_t vuc16;  /*!< Read Only */
typedef __I uint8_t vuc8;   /*!< Read Only */

#define USER_WARNING_REF(x) (void)x; // 防止编译出现未使用警告

// gpio函数重定义 ---> 方便标准库移植
#define GPIO_ReadInputDataBit(gbio_x, gbio_pin_x)  HAL_GPIO_ReadPin(gbio_x, gbio_pin_x)
#define GPIO_SetBits(gbio_x, gbio_pin_x)           HAL_GPIO_WritePin(gbio_x, gbio_pin_x, GPIO_PIN_SET)
#define GPIO_ResetBits(gbio_x, gbio_pin_x)         HAL_GPIO_WritePin(gbio_x, gbio_pin_x, GPIO_PIN_RESET)

// 引脚重定义 ---> 方便标准库移植
#define GPIO_Pin_0   GPIO_PIN_0
#define GPIO_Pin_1   GPIO_PIN_1
#define GPIO_Pin_2   GPIO_PIN_2
#define GPIO_Pin_3   GPIO_PIN_3
#define GPIO_Pin_4   GPIO_PIN_4
#define GPIO_Pin_5   GPIO_PIN_5
#define GPIO_Pin_6   GPIO_PIN_6
#define GPIO_Pin_7   GPIO_PIN_7
#define GPIO_Pin_8   GPIO_PIN_8
#define GPIO_Pin_9   GPIO_PIN_9
#define GPIO_Pin_10  GPIO_PIN_10
#define GPIO_Pin_11  GPIO_PIN_11
#define GPIO_Pin_12  GPIO_PIN_12
#define GPIO_Pin_13  GPIO_PIN_13
#define GPIO_Pin_14  GPIO_PIN_14
#define GPIO_Pin_15  GPIO_PIN_15
#define GPIO_Pin_16  GPIO_PIN_16
#define GPIO_Pin_17  GPIO_PIN_17





#endif

/********************************End of Head************************************/

