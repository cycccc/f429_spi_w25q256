/**
 *******************************Copyright (c)************************************
 *
 *                   (c) Copyright 2021, CY, China, QD.
 *                           All Rights Reserved
 *
 *                           By(�Ͼ�������ӿƼ����޹�˾)
 *                           http://www.njwfx.com
 *
 *----------------------------------�ļ���Ϣ------------------------------------
 * �ļ�����: bsp_printf.h
 * ������Ա: CY
 * ��������: 2021-02-17
 * �ĵ�����: �����ض���printf��ӡ��printf�궨������
 *
 *----------------------------------�汾��Ϣ------------------------------------
 * ʵ��ƽ̨
 *          |--Ұ��  STM32 F429 ������   ��ս��V2��
 * �汾����: V2.1
 * �汾˵��: 
 *          |-2.1
 *	         |-2020-10-08
 *	          |-�޸Ĵ��ı��ı���ΪGB2312
 *	          |-�޸��˴��������ʽ���Ǹ�Ϊ��ǰ���ض���C��ķ�ʽ
 *	          |-������һЩC���ͷ�ļ�
 *	          |-�����printf �����ӡ�� STM32CUBEIDE �ڲ�SWV�������
 *          |-2.0
 * 	         |-2020-10-04
 * 	          |-�޸��˴��������ʵ�ʷ�ʽ��������C���е�printf��Ϊ�����ʹ���Զ����printf��Ϊ���
 * 	          |-ȡ���˶�������Ƿ���������
 *          |-1.0
 * 	         |-2021-02-17
 * 	          |-��ʼ�汾
 *------------------------------------------------------------------------------
 */

#ifndef __BSP_PRINTF_H_
#define __BSP_PRINTF_H_


//----����ͷ�ļ�--------
#include "../typedef/bsp_typedef.h"

#ifndef   CY_EX_DEFINE        //���û�н���defineͷ�ļ��ⲿ����
#define   CY_IN_DEFINE        //�����ڲ�����
// �����ض�����Ҫ��main.c�ж���---->>#define  _PRINTF_OPEN<<   //
/*---------------------------------------*/
#define   USART                 huart1         //���崮�����ĸ�����
#define   PRINTF_ON                              //���������ǲ��Ǵ�ӡ
//#define   __ITM_DEBUG_ON__                     //����printf��ӡʱ��ʹ��IDE�ڲ�ITM���д�ӡ

#endif	/* CY_IN_DEFINE */

//***************���ڵ��ض���**************//
#ifdef _PRINTF_OPEN
extern UART_HandleTypeDef USART;

#ifdef __GNUC__		/* GCC���߱����� */
#if defined(__ITM_DEBUG_ON__)	/* STM32CUBEIDE�ڲ�ITM���� */
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
#ifdef __CC_ARM /* ARMCC���߱����� */
int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&USART, (uint8_t*)&ch, 1, 0xFFFF);
    return ch;
}
#endif	/* __CC_ARM */
#ifdef __ICCARM__ /* IAR���߱����� */
int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&USART, (uint8_t*)&ch, 1, 0xFFFF);
    return ch;
}
#endif  /* __ICCARM__ */



#endif	/* _PRINTF_OPEN */
//***********************************//

//*********DEBUG_LOG���ڴ�ӡ�ĺ궨��*****************//
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
//***************���ڴ�ӡ�궨�����**************//


#endif

/********************************End of Head************************************/

