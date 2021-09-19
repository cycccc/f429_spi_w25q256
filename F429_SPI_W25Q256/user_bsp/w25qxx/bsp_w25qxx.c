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
 * 文件名称: bsp_w25qxx.c
 * 创建人员: CY
 * 创建日期: 2021-03-14
 * 文档描述: 
 *
 *----------------------------------版本信息------------------------------------
 * 版本代号: V1.0
 * 版本说明: 
 *          |-1.0
 * 	         |-2021-03-14
 * 	          |-初始版本
 *------------------------------------------------------------------------------
 */
#include "./bsp_w25qxx.h"


u16 W25Qxx_Type=W25Q256;	//默认是W25Q256


/**
 * 函数名称: W25QXX_ReadWriteOneByte
 * 功能描述: 读写一个字节
 * 参数说明: TxData: [输入]要写入的字节
 * 返回说明: 读取到的字节
 * 创建人员: CY
 * 创建日期: 2021-02-26
 *------------------*
 * 修改人员:
 * 修改日期:
 * 修改描述:
 *------------------*
 */
u8 W25QXX_ReadWriteOneByte(u8 TxData) {
    u8 Rxdata;
    HAL_SPI_TransmitReceive(&SPI_Handle,&TxData,&Rxdata,1, 1000);
    return Rxdata;          		    //返回收到的数据
}

/**
 * 函数名称: W25QXX_WriteEnable
 * 功能描述: 向FLASH发送 写使能 命令
 * 参数说明: None
 * 返回说明: None
 * 创建人员: CY
 * 创建日期: 2021-02-26
 *------------------*
 * 更多描述: 将WEL置位
 *------------------*
 */
void W25QXX_WriteEnable(void) {
    W25QXX_CS_ON;                             //使能器件
    W25QXX_ReadWriteOneByte(W25X_WriteEnable);     //发送写使能
    W25QXX_CS_OFF;                            //取消片选
}

/**
 * 函数名称: W25QXX_WriteDisable
 * 功能描述: W25Q256写禁止
 * 参数说明: None
 * 返回说明: None
 * 创建人员: CY
 * 创建日期: 2021-02-26
 *------------------*
 * 更多描述: 将WEL清零
 *------------------*
 */
void W25QXX_WriteDisable(void) {
    W25QXX_CS_ON;                            //使能器件
    W25QXX_ReadWriteOneByte(W25X_WriteDisable);  //发送写禁止指令
    W25QXX_CS_OFF;                            //取消片选
}

/**
 * 函数名称: W25QXX_Read_SR
 * 功能描述: 读取W25Q256的状态寄存器
 * 参数说明: regno: [输入] 状态寄存器号，范:1~3
 * 返回说明: 状态寄存器值
 * 创建人员: CY
 * 创建日期: 2021-02-26
 *------------------*
 * 更多描述:
 *           状态寄存器1：
 *           BIT7  6   5   4   3   2   1   0
 *           SPR   RV  TB BP2 BP1 BP0 WEL BUSY
 *           SPR:默认0,状态寄存器保护位,配合WP使用
 *           TB,BP2,BP1,BP0:FLASH区域写保护设置
 *           WEL:写使能锁定
 *           BUSY:忙标记位(1,忙;0,空闲)
 *           默认:0x00
 *           状态寄存器2：
 *           BIT7  6   5   4   3   2   1   0
 *           SUS   CMP LB3 LB2 LB1 (R) QE  SRP1
 *           状态寄存器3：
 *           BIT7      6    5    4   3   2   1   0
 *           HOLD/RST  DRV1 DRV0 (R) (R) WPS ADP ADS
 *------------------*
 */
u8 W25QXX_Read_SR(u8 regno) {
    u8 byte=0,command=0;
    switch(regno) {
    case 1:
        command=W25X_ReadStatusReg1;    //读状态寄存器1指令
        break;
    case 2:
        command=W25X_ReadStatusReg2;    //读状态寄存器2指令
        break;
    case 3:
        command=W25X_ReadStatusReg3;    //读状态寄存器3指令
        break;
    default:
        command=W25X_ReadStatusReg1;
        break;
    }
    W25QXX_CS_ON;                            //使能器件
    W25QXX_ReadWriteOneByte(command);            //发送读取状态寄存器命令
    byte=W25QXX_ReadWriteOneByte(0Xff);          //读取一个字节
    W25QXX_CS_OFF;                            //取消片选
    return byte;
}

/**
 * 函数名称: W25QXX_Write_SR
 * 功能描述: 写W25Q256状态寄存器
 * 参数说明: regno: [输入] 状态寄存器号，范:1~3
 *    			 sr: [输入] 写入的值
 * 返回说明: None
 * 创建人员: CY
 * 创建日期: 2021-02-26
 *------------------*
 * 更多描述:
 *------------------*
 */
void W25QXX_Write_SR(u8 regno,u8 sr) {
    u8 command=0;
    switch(regno) {
    case 1:
        command=W25X_WriteStatusReg1;    //写状态寄存器1指令
        break;
    case 2:
        command=W25X_WriteStatusReg2;    //写状态寄存器2指令
        break;
    case 3:
        command=W25X_WriteStatusReg3;    //写状态寄存器3指令
        break;
    default:
        command=W25X_WriteStatusReg1;
        break;
    }
    W25QXX_CS_ON;                            //使能器件
    W25QXX_ReadWriteOneByte(command);            //发送写取状态寄存器命令
    W25QXX_ReadWriteOneByte(sr);                 //写入一个字节
    W25QXX_CS_OFF;                            //取消片选
}

/**
 * 函数名称: W25QXX_WaitBusy
 * 功能描述: 等待空闲
 * 参数说明: None
 * 返回说明: None
 * 创建人员: CY
 * 创建日期: 2021-02-26
 *------------------*
 * 更多描述:
 *
 *------------------*
 */
void W25QXX_WaitBusy(void) {
    while((W25QXX_Read_SR(1)&0x01)==0x01);   // 等待BUSY位清空
}

/**
 * 函数名称: W25QXX_ChipReset
 * 功能描述: 重置芯片函数
 * 参数说明: None
 * 返回说明: None
 * 创建人员: CY
 * 创建日期: 2021-03-04
 *------------------*
 * 更多描述:
 *           暂时好像没用
 *------------------*
 */
void W25QXX_ChipReset(void) {
    W25QXX_WriteEnable();                  //SET WEL
    W25QXX_WaitBusy();
    W25QXX_CS_ON;                            //使能器件
    W25QXX_ReadWriteOneByte(W25X_ResetEnable);        //发送重置命令
    W25QXX_CS_OFF;                            //取消片选
    W25QXX_WaitBusy();   				   //等待芯片重置结束
    W25QXX_CS_ON;                            //使能器件
    W25QXX_ReadWriteOneByte(W25X_ResetMemory);        //发送重置命令
    W25QXX_CS_OFF;                            //取消片选
    W25QXX_WaitBusy();   				   //等待芯片重置结束

}

/**
 * 函数名称: W25QXX_PowerDown
 * 功能描述: 进入掉电模式
 * 参数说明: None
 * 返回说明: None
 * 创建人员: CY
 * 创建日期: 2021-02-26
 *------------------*
 * 更多描述:
 *
 *------------------*
 */
void W25QXX_PowerDown(void) {
    W25QXX_CS_ON;                            //使能器件
    W25QXX_ReadWriteOneByte(W25X_PowerDown);     //发送掉电命令
    W25QXX_CS_OFF;                            //取消片选
    HAL_Delay(3);                            //等待TPD
}

/**
 * 函数名称: W25QXX_WAKEUP
 * 功能描述: 唤醒
 * 参数说明: None
 * 返回说明: None
 * 创建人员: CY
 * 创建日期: 2021-02-26
 *------------------*
 * 更多描述:
 *
 *------------------*
 */
void W25QXX_WAKEUP(void) {
    W25QXX_CS_ON;                                //使能器件
    W25QXX_ReadWriteOneByte(W25X_ReleasePowerDown);  //  send W25X_PowerDown command 0xAB
    W25QXX_CS_OFF;                                //取消片选
    HAL_Delay(3);                                //等待TRES1
}

/**
 * 函数名称: W25QXX_ReadID
 * 功能描述: 读取芯片ID
 * 参数说明: None
 * 返回说明: 芯片型号
 * 创建人员: CY
 * 创建日期: 2021-02-26
 *------------------*
 * 更多描述:
 *           返回值如下:
 *           0XEF13,表示芯片型号为W25Q80
 *           0XEF14,表示芯片型号为W25Q16
 *           0XEF15,表示芯片型号为W25Q32
 *           0XEF16,表示芯片型号为W25Q64
 *           0XEF17,表示芯片型号为W25Q128
 *           0XEF18,表示芯片型号为W25Q256
 *------------------*
 */
u16 W25QXX_ReadID(void) {
#if (1)
    u16 Temp = 0;
    W25QXX_CS_ON;
    W25QXX_ReadWriteOneByte(0x90);//发送读取ID命令
    W25QXX_ReadWriteOneByte(0x00);
    W25QXX_ReadWriteOneByte(0x00);
    W25QXX_ReadWriteOneByte(0x00);
    Temp|=W25QXX_ReadWriteOneByte(0xFF)<<8;
    Temp|=W25QXX_ReadWriteOneByte(0xFF);
    W25QXX_CS_OFF;
    return Temp;
#else
    return W25Q128;
#endif
}



//初始化SPI FLASH的IO口


/**
 * 函数名称: W25QXX_Init
 * 功能描述: 初始化W25QXX并将W25Q256设置成4字节地址模式
 * 参数说明: None
 * 返回说明: None
 * 创建人员: CY
 * 创建日期: 2021-02-26
 *------------------*
 * 更多描述:
 *           4Kbytes为一个Sector
 *           16个Sector为1个Block
 *           W25Q256
 *           容量为32M字节,共有512个Block,8192个Sector
 *------------------*
 */
void W25QXX_Init(void) {
    u8 temp;
    W25QXX_CS_OFF;			                //SPI FLASH不选中
    W25Qxx_Type=W25QXX_ReadID();	        //读取FLASH ID.
    if(W25Qxx_Type==W25Q256) {              //SPI FLASH为W25Q256
        temp=W25QXX_Read_SR(3);              //读取状态寄存器3，判断地址模式
        if((temp&0X01)==0) {		        //如果不是4字节地址模式,则进入4字节地址模式
            W25QXX_CS_ON; 			        //选中
            W25QXX_ReadWriteOneByte(W25X_Enable4ByteAddr);//发送进入4字节地址模式指令
            W25QXX_CS_OFF;       		        //取消片选
        }
    }
}

/**
 * 函数名称: W25QXX_Read
 * 功能描述: 读取SPI FLASH 在指定地址开始读取指定长度的数据
 * 参数说明: pBuffer: [输出] 数据存储区
 *			     ReadAddr: [输入] 开始读取的地址(24bit)
 *			     NumByteToRead: [输入] 要读取的字节数(最大65535)
 * 返回说明: None
 * 创建人员: CY
 * 创建日期: 2021-02-26
 *------------------*
 * 更多描述:
 *
 *------------------*
 */
void W25QXX_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead) {
    u16 i;
    W25QXX_CS_ON;                            //使能器件
    W25QXX_ReadWriteOneByte(W25X_ReadData);      //发送读取命令
    if(W25Qxx_Type==W25Q256) {              //如果是W25Q256的话地址为4字节的，要发送最高8位
        W25QXX_ReadWriteOneByte((u8)((ReadAddr)>>24));
    }
    W25QXX_ReadWriteOneByte((u8)((ReadAddr)>>16));   //发送24bit地址
    W25QXX_ReadWriteOneByte((u8)((ReadAddr)>>8));
    W25QXX_ReadWriteOneByte((u8)ReadAddr);
    for(i=0; i<NumByteToRead; i++) {
        pBuffer[i]=W25QXX_ReadWriteOneByte(0XFF);    //循环读数
    }
    W25QXX_CS_OFF;
}

/**
 * 函数名称: W25QXX_Write_Page
 * 功能描述: SPI在一页(0~65535)内写入少于256个字节的数据
 * 参数说明: pBuffer: [输入] 数据存储区
 *    			 WriteAddr: [输入] 开始写入的地址(24bit)
 *			     NumByteToWrite: [输入] 要写入的字节数(最大256),该数不应该超过该页的剩余字节数!!!
 * 返回说明: None
 * 创建人员: CY
 * 创建日期: 2021-02-26
 *------------------*
 * 更多描述:
 *           在指定地址开始写入最大256字节的数据
 *------------------*
 */
void W25QXX_Write_Page(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite) {
    u16 i;
    W25QXX_WriteEnable();                  //SET WEL
    W25QXX_CS_ON;                            //使能器件
    W25QXX_ReadWriteOneByte(W25X_PageProgram);   //发送写页命令
    if(W25Qxx_Type==W25Q256) {              //如果是W25Q256的话地址为4字节的，要发送最高8位
        W25QXX_ReadWriteOneByte((u8)((WriteAddr)>>24));
    }
    W25QXX_ReadWriteOneByte((u8)((WriteAddr)>>16)); //发送24bit地址
    W25QXX_ReadWriteOneByte((u8)((WriteAddr)>>8));
    W25QXX_ReadWriteOneByte((u8)WriteAddr);
    for(i=0; i<NumByteToWrite; i++) {
        W25QXX_ReadWriteOneByte(pBuffer[i]);   //循环写数
    }
    W25QXX_CS_OFF;                            //取消片选
    W25QXX_WaitBusy();					   //等待写入结束
}

/**
 * 函数名称: W25QXX_Write_NoCheck
 * 功能描述: 无检验写SPI FLASH
 * 参数说明: pBuffer: [输入] 数据存储区
 *		     	 WriteAddr: [输入] 开始写入的地址(24bit)
 *		    	 NumByteToWrite: [输入] 要写入的字节数(最大65535)
 * 返回说明: None
 * 创建人员: CY
 * 创建日期: 2021-02-26
 *------------------*
 * 更多描述:
 *           无检验写SPI FLASH
 *           必须确保所写的地址范围内的数据全部为0XFF,否则在非0XFF处写入的数据将失败!
 *           具有自动换页功能
 *           在指定地址开始写入指定长度的数据,但是要确保地址不越界!
 *------------------*
 */
void W25QXX_Write_NoCheck(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite) {
    u16 pageremain;
    pageremain=256-WriteAddr%256; //单页剩余的字节数
    if(NumByteToWrite<=pageremain) {
        pageremain=NumByteToWrite;//不大于256个字节
    }

    while(1) {
        W25QXX_Write_Page(pBuffer,WriteAddr,pageremain);
        if(NumByteToWrite==pageremain) {
            break;//写入结束了
        } else {  //NumByteToWrite>pageremain
            pBuffer+=pageremain;
            WriteAddr+=pageremain;

            NumByteToWrite-=pageremain;			  //减去已经写入了的字节数
            if(NumByteToWrite>256) {
                pageremain=256; //一次可以写入256个字节
            } else {
                pageremain=NumByteToWrite; 	  //不够256个字节了
            }
        }
    }
}

/**
 * 函数名称: W25QXX_Write
 * 功能描述: 写SPI FLASH 在指定地址开始写入指定长度的数据
 * 参数说明: pBuffer: [输入] 数据存储区
 *			     WriteAddr: [输入] 开始写入的地址(24bit)
 *		    	 NumByteToWrite: [输入] 要写入的字节数(最大65535)
 * 返回说明: None
 * 创建人员: CY
 * 创建日期: 2021-02-26
 *------------------*
 * 更多描述:
 *           写SPI FLASH
 *           在指定地址开始写入指定长度的数据
 *           该函数带擦除操作!
 *------------------*
 */
u8 W25QXX_BUFFER[4096];
void W25QXX_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite) {
    u32 secpos;
    u16 secoff;
    u16 secremain;
    u16 i;
    u8 * W25Q256_BUF;
    W25Q256_BUF=W25QXX_BUFFER;
    secpos=WriteAddr/4096;//扇区地址
    secoff=WriteAddr%4096;//在扇区内的偏移
    secremain=4096-secoff;//扇区剩余空间大小
    if(NumByteToWrite<=secremain) {
        secremain=NumByteToWrite;//不大于4096个字节
    }
    while(1) {
        W25QXX_Read(W25Q256_BUF,secpos*4096,4096);//读出整个扇区的内容
        for(i=0; i<secremain; i++) { //校验数据
            if(W25Q256_BUF[secoff+i]!=0XFF) {
                break;//需要擦除
            }
        }
        if(i<secremain) { //需要擦除
            W25QXX_SectorErase(secpos);//擦除这个扇区
            for(i=0; i<secremain; i++) { //复制
                W25Q256_BUF[i+secoff]=pBuffer[i];
            }
            W25QXX_Write_NoCheck(W25Q256_BUF,secpos*4096,4096);//写入整个扇区

        } else {
            W25QXX_Write_NoCheck(pBuffer,WriteAddr,secremain);//写已经擦除了的,直接写入扇区剩余区间.
        }
        if(NumByteToWrite==secremain) {
            break;//写入结束了
        } else { //写入未结束
            secpos++;//扇区地址增1
            secoff=0;//偏移位置为0

            pBuffer+=secremain;  //指针偏移
            WriteAddr+=secremain;//写地址偏移
            NumByteToWrite-=secremain;				//字节数递减
            if(NumByteToWrite>4096)secremain=4096;	//下一个扇区还是写不完
            else secremain=NumByteToWrite;			//下一个扇区可以写完了
        }
    };
}

/**
 * 函数名称: W25QXX_ChipErase
 * 功能描述: 擦除整个芯片
 * 参数说明: None
 * 返回说明: None
 * 创建人员: CY
 * 创建日期: 2021-02-26
 *------------------*
 * 更多描述:
 *           等待时间超长...
 *------------------*
 */
void W25QXX_ChipErase(void) {
    W25QXX_WriteEnable();                  //SET WEL
    W25QXX_WaitBusy();
    W25QXX_CS_ON;                            //使能器件
    W25QXX_ReadWriteOneByte(W25X_ChipErase);        //发送片擦除命令
    W25QXX_CS_OFF;                            //取消片选
    W25QXX_WaitBusy();   				   //等待芯片擦除结束
}

/**
 * 函数名称: W25QXX_SectorErase
 * 功能描述: 擦除一个扇区
 * 参数说明: Dst_Addr: [输入] 扇区地址 根据实际容量设置
 * 返回说明: None
 * 创建人员: CY
 * 创建日期: 2021-02-26
 *------------------*
 * 更多描述:
 *           擦除一个扇区的最少时间:150ms
 *------------------*
 */
void W25QXX_SectorErase(u32 Dst_Addr) {
    Dst_Addr*=4096;
    W25QXX_WriteEnable();                  //SET WEL
    W25QXX_WaitBusy();
    W25QXX_CS_ON;                            //使能器件
    W25QXX_ReadWriteOneByte(W25X_SectorErase);   //发送扇区擦除指令
    if(W25Qxx_Type==W25Q256) {              //如果是W25Q256的话地址为4字节的，要发送最高8位
        W25QXX_ReadWriteOneByte((u8)((Dst_Addr)>>24));
    }
    W25QXX_ReadWriteOneByte((u8)((Dst_Addr)>>16));  //发送24bit地址
    W25QXX_ReadWriteOneByte((u8)((Dst_Addr)>>8));
    W25QXX_ReadWriteOneByte((u8)Dst_Addr);
    W25QXX_CS_OFF;                            //取消片选
    W25QXX_WaitBusy();   				    //等待擦除完成
}

/********************************End of File************************************/

