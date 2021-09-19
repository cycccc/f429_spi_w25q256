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
 * 文件名称: bsp_w25qxx.h
 * 创建人员: CY
 * 创建日期: 2021-03-14
 * 文档描述: 
 *
 *----------------------------------版本信息------------------------------------
 * 实验平台
 *          |--
 * 版本代号: V1.0
 * 版本说明: 
 *          |-1.0
 * 	         |-2021-03-14
 * 	          |-初始版本
 *------------------------------------------------------------------------------
 */

#ifndef __BSP_W25QXX_H_
#define __BSP_W25QXX_H_

#include "main.h"

#include "spi.h"


//spi 定义----------------------------//
#define SPI_Handle        hspi1   
#define W25QXX_CS_PORT    GPIOA                ///> GPIOF | GPIO_PIN_6  是本机的Flash
#define W25QXX_CS_PIN     GPIO_PIN_4           ///> GPIOA | GPIO_PIN_4  是外接的Flash
#define W25QXX_WD_PORT    GPIOD
#define W25QXX_WD_PIN     GPIO_PIN_5 
#define W25QXX_HOLD_PORT  GPIOH 
#define W25QXX_HOLD_PIN   GPIO_PIN_4 
//-----------------------------------//


//w25qxx 系列指令表
#define W25X_WriteEnable		    0x06 
#define W25X_WriteDisable		    0x04 
#define W25X_ReadStatusReg1		  0x05 
#define W25X_ReadStatusReg2		  0x35 
#define W25X_ReadStatusReg3		  0x15 
#define W25X_WriteStatusReg1    0x01 
#define W25X_WriteStatusReg2    0x31 
#define W25X_WriteStatusReg3    0x11 
#define W25X_ReadData			      0x03 
#define W25X_FastReadData		    0x0B 
#define W25X_FastReadDual		    0x3B 
#define W25X_PageProgram		    0x02 
#define W25X_BlockErase			    0xD8 
#define W25X_SectorErase		    0x20 
#define W25X_ChipErase			    0xC7 
#define W25X_PowerDown			    0xB9 
#define W25X_ReleasePowerDown	  0xAB 
#define W25X_DeviceID			      0xAB 
#define W25X_ManufactDeviceID	  0x90 
#define W25X_JedecDeviceID		  0x9F 
#define W25X_Enable4ByteAddr    0xB7
#define W25X_Exit4ByteAddr      0xE9
/* Reset 指令 */
#define W25X_ResetEnable        0x66
#define W25X_ResetMemory        0x99
#define W25X_ExitQspiMode       0xff
#define W25X_EnterQspiMode      0x38




//W25X系列/Q系列芯片列表	    
#define W25Q80 	0XEF13 	
#define W25Q16 	0XEF14
#define W25Q32 	0XEF15
#define W25Q64 	0XEF16
#define W25Q128	0XEF17
#define W25Q256 0XEF18


//变量声明----------------------------
extern u16 W25Qxx_Type;
//函数定义----------------------------
#define W25QXX_CS_ON   HAL_GPIO_WritePin(W25QXX_CS_PORT,W25QXX_CS_PIN,GPIO_PIN_RESET)  //打开片选是拉低操作
#define W25QXX_CS_OFF  HAL_GPIO_WritePin(W25QXX_CS_PORT,W25QXX_CS_PIN,GPIO_PIN_SET)    //关闭片选是拉高操作

#define HOLD_AND_WD_PULLUP  {HAL_GPIO_WritePin(W25QXX_HOLD_PORT,W25QXX_HOLD_PIN,GPIO_PIN_SET);HAL_GPIO_WritePin(W25QXX_WD_PORT,W25QXX_WD_PIN,GPIO_PIN_SET);} //取消暂停和写保护
       

void W25QXX_Init(void); //初始化W25QXX并将W25Q256设置成4字节地址模式
void W25QXX_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead);  //读取SPI FLASH 在指定地址开始读取指定长度的数据
void W25QXX_Write_Page(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite); //SPI在一页(0~65535)内写入少于256个字节的数据
void W25QXX_Write_NoCheck(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite); //无检验写SPI FLASH
void W25QXX_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);  //写SPI FLASH 在指定地址开始写入指定长度的数据
void W25QXX_ChipErase(void);  //擦除整个芯片
void W25QXX_SectorErase(u32 Dst_Addr);  //擦除一个扇区

u8 W25QXX_Read_SR(u8 regno);
#endif

/********************************End of Head************************************/
