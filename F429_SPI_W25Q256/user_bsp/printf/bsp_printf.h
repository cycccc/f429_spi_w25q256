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
 * 文件名称: bsp_printf.h
 * 创建人员: CY
 * 创建日期: 2021-02-17
 * 文档描述: 串口重定向printf打印，printf宏定义设置
 *
 *----------------------------------版本信息------------------------------------
 * 实验平台
 *          |--野火  STM32 F429 开发板   挑战者V2版
 * 版本代号: V2.1
 * 版本说明: 
 *          |-2.1
 *	         |-2020-10-08
 *	          |-修改此文本的编码为GB2312
 *	          |-修改了串口输出方式还是改为以前的重定向C库的方式
 *	          |-加入了一些C库的头文件
 *	          |-添加了printf 输出打印到 STM32CUBEIDE 内部SWV调试面板
 *          |-2.0
 * 	         |-2020-10-04
 * 	          |-修改了串口输出的实际方式，不在以C库中的printf作为输出，使用自定义的printf作为输出
 * 	          |-取消了定义变量是否在内在外
 *          |-1.0
 * 	         |-2021-02-17
 * 	          |-初始版本
 *------------------------------------------------------------------------------
 */

#ifndef __BSP_PRINTF_H_
#define __BSP_PRINTF_H_


//----包含头文件--------
#include "../typedef/bsp_typedef.h"

#ifndef   CY_EX_DEFINE        //如果没有进行define头文件外部定义
#define   CY_IN_DEFINE        //进行内部定义
// 串口重定向需要在main.c中定义---->>#define  _PRINTF_OPEN<<   //
/*---------------------------------------*/
#define   USART                 huart1         //定义串口是哪个串口
#define   PRINTF_ON                              //决定串口是不是打印
//#define   __ITM_DEBUG_ON__                     //决定printf打印时否使以IDE内部ITM进行打印

#endif	/* CY_IN_DEFINE */

//***************串口的重定向**************//
#ifdef _PRINTF_OPEN
extern UART_HandleTypeDef USART;

#ifdef __GNUC__		/* GCC工具编译链 */
#if defined(__ITM_DEBUG_ON__)	/* STM32CUBEIDE内部ITM调试 */
int _write(int fd, char *ptr, int len)
{
    uint32_t i = 0;

    for(i = 0; i < len; i++)
    {
        ITM_SendChar(*(ptr++));
    }

    return len;
}
#else
int _write(int fd, char *ptr, int len)
{
    HAL_UART_Transmit(&USART, (uint8_t*)ptr, len, 0xFFFF);
    return len;
}
#endif	/* __ITM_DEBUG_ON__ */
#endif  /* __GNUC__	 */
#ifdef __CC_ARM /* ARMCC工具编译链 */
int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&USART, (uint8_t*)&ch, 1, 0xFFFF);
    return ch;
}
#endif	/* __CC_ARM */
#ifdef __ICCARM__ /* IAR工具编译链 */
int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&USART, (uint8_t*)&ch, 1, 0xFFFF);
    return ch;
}
#endif  /* __ICCARM__ */



#endif	/* _PRINTF_OPEN */
//***********************************//

//*********DEBUG_LOG串口打印的宏定义*****************//
#if defined(PRINTF_ON)
  #define USER_MAIN_DEBUG
#endif /* PRINTF_ON_OFF */

#ifdef USER_MAIN_DEBUG
#define user_printf(format, ...)                         printf("File:%s; Line=%d;"" -> " format "\r\n",__FILE__,__LINE__, ##__VA_ARGS__)
#define user_info(format, ...)                      printf("info:" format "\r\n", ##__VA_ARGS__)
#define cy_printf(type,message,expression,handler,...)	 do { if (expression) {printf(type"--->"message"\r\n",##__VA_ARGS__); handler;}} while(0)
#else
#define user_printf(format, ...)
#define user_info(format, ...)
#define cy_printf(type,message,expression,handler,...)
#endif
//***************串口打印宏定义结束**************//


#endif

/********************************End of Head************************************/

