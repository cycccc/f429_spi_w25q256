/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#define  _PRINTF_OPEN
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "fatfs.h"
#include "sdio.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Flash Write==== */
#define FILE_NAME           "1.HTT"           //"All_8889_Pic_NOR.bin"
//"1.HTT"
//"1.txt"
//"NOR.bin"
#define WRITE_DATA_ADDRESS   0
/* =============== */
/* Flash Read==== */
#define READ_DATA_ADDRESS   0
#define READ_DATA_NUMBER    100
/* ======== */

uint8_t usbFlag=0;
uint32_t address = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
uint32_t FileCopy_SD_To_Flash(char * File_Name, u32 WriteDataAddress);
void Flash_ReadData(uint32_t ReadAddress,uint32_t ReadNum);
void Flash_ChipErase(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_SPI5_Init();
  MX_SDIO_SD_Init();
  MX_FATFS_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
    //����Ұ���F429��SDIOΪSD_Cardģʽ
    SD_Card_Model();

    HOLD_AND_WD_PULLUP;

    led_white;

    user_printf("W25Q256 Flash���Կ�ʼ...");

    W25QXX_Init();

    user_printf("id = 0x%X",W25Qxx_Type);
    user_printf("�밴 KEY1 ����SD����Flash�ĸ���");
    user_printf("�밴 KEY2 ����Flash�����ݵĶ�ȡ");
    user_printf("�밴 KEY1 + KEY2 ����FlashȫƬ����");

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1)
    {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET)
        {
            for(;;)
            {
                if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
                {
                    usbFlag = 1;
                    break;
                }
                if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET)
                {
                    for(;;)
                    {
                        if((HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET) && (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET))
                        {
                            usbFlag = 3;
                            break;
                        }
                    }
                    break;
                }
            }
        }
        else if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET)
        {
            for(;;)
            {
                if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET)
                {
                    usbFlag = 2;
                    break;
                }
                if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET)
                {
                    for(;;)
                    {
                        if((HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET) && (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET))
                        {
                            usbFlag = 3;
                            break;
                        }
                    }
                    break;
                }
            }
        }
        if(usbFlag == 1)
        {
            led_blue;
            address = FileCopy_SD_To_Flash(FILE_NAME,WRITE_DATA_ADDRESS);
            if(address == 0)
            {
                led_red;
            }
            else
            {
                led_green;
            }

            usbFlag = 0;
        }
        if(usbFlag == 2)
        {
            led_blue;
            Flash_ReadData(READ_DATA_ADDRESS,READ_DATA_NUMBER);
            led_green;
            usbFlag = 0;
        }
        if(usbFlag == 3)
        {
            led_blue;
            Flash_ChipErase();
            led_green;
            usbFlag = 0;
        }
    }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 15;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 8;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
/**
 * ��������: FileCopy_SD_To_Flash
 * ��������: ��SD���и���һ���ļ���Flash�У���������У��
 * ����˵��: File_Name: [����] Ҫ���Ƶ��ļ�����ȫ������Ҫ���ļ���ʽ ����XXXX.XXX
 * ����˵��: 0:����other:ΪFlash�Ѿ����˵ĵ�ַ
 *           Ҫд�����ļ�����������ַ��ʼд����Ȼ���ǰ���ˢ��
 * ������Ա: CY
 * ��������: 2021-03-01
 *------------------*
 * ��������:
 *
 *------------------*
 */
uint32_t FileCopy_SD_To_Flash(char * File_Name, u32 WriteDataAddress)
{

    int WRITE_SIZE = 4096 ;
    FRESULT res;

    //��д��SD����
    res = f_mount(&SDFatFS, SDPath, 1);
    if (res != FR_OK)
    {
        user_printf("error ��f_mount_SD: res = %d",res);
        return 0;
    }
    //sd �ļ�ƴ��
    char* user_sd_path = (char*)malloc(sizeof(SDPath)+sizeof(File_Name));
    if(user_sd_path==NULL)
    {
        user_printf("error ��user_sd_pathδ����ɹ�!");
        f_mount(NULL,SDPath,1);  /* ����ʹ���ļ�ϵͳ��ȡ�������ļ�ϵͳ */
        return 0;
    }
    memset(user_sd_path,0,sizeof(SDPath)+sizeof(File_Name));
    memcpy(user_sd_path,SDPath,sizeof(SDPath));
    strcat(user_sd_path,File_Name);

    res = f_open(&SDFile, user_sd_path, FA_READ);
    if (res != FR_OK)
    {
        user_printf("error ��f_open_SD: res = %d",res);
        f_close(&SDFile);  /* ���ٶ�д���ر��ļ� */
        if(user_sd_path!=NULL)free(user_sd_path); //�ͷŶѿռ�
        f_mount(NULL,SDPath,1);  /* ����ʹ���ļ�ϵͳ��ȡ�������ļ�ϵͳ */
        return 0;
    }
    //ȷ���ļ���С
    uint32_t file_size = f_size(&SDFile);
    user_printf("file_size = %d",file_size);
    if(file_size == 0)
    {
        f_close(&SDFile);
        if(user_sd_path!=NULL)free(user_sd_path); //�ͷŶѿռ�
        f_mount(NULL,SDPath,1);  /* ����ʹ���ļ�ϵͳ��ȡ�������ļ�ϵͳ */
        return 0;
    }
    //�����ļ�-------------------
    user_printf("SPI Flash����д���ļ�...");
    uint32_t byteswritten = 0;
    uint32_t Address = WriteDataAddress;

    uint8_t* read_buffer = (uint8_t*)malloc(WRITE_SIZE);
    if(read_buffer==NULL)
    {
        user_printf("error ��read_bufferδ����ɹ�!");
        f_close(&SDFile);  /* ���ٶ�д���ر��ļ� */
        if(user_sd_path!=NULL)free(user_sd_path); //�ͷŶѿռ�
        f_mount(NULL,SDPath,1);  /* ����ʹ���ļ�ϵͳ��ȡ�������ļ�ϵͳ */
        return 0;
    }
    memset(read_buffer,0,WRITE_SIZE);

    for(;;)
    {
        res = f_read(&SDFile,read_buffer,WRITE_SIZE,(void*)&byteswritten);
        if(res != FR_OK )
        {
            user_printf("error ��f_read_SD: res = %d",res);
            f_close(&SDFile);  /* ���ٶ�д���ر��ļ� */
            if(user_sd_path!=NULL)free(user_sd_path); //�ͷŶѿռ�
            if(read_buffer!=NULL)free(read_buffer);
            f_mount(NULL,SDPath,1);  /* ����ʹ���ļ�ϵͳ��ȡ�������ļ�ϵͳ */
            return 0;
        }
        W25QXX_Write(read_buffer,Address,byteswritten);		//��SPI Flash��,д��BUFF_SIZE���ȵ�����
        memset(read_buffer,0,WRITE_SIZE);
        Address += byteswritten;  //��ַ������
        if(byteswritten != WRITE_SIZE)
        {
            break;
        }
    }
    //��������-------------------
    if(Address != file_size)
    {
        user_printf("SPI Flashд��ʧ��!!!!!");
        f_close(&SDFile);  /* ���ٶ�д���ر��ļ� */
        if(user_sd_path!=NULL)free(user_sd_path); //�ͷŶѿռ�
        if(read_buffer!=NULL)free(read_buffer);
        f_mount(NULL,SDPath,1);  /* ����ʹ���ļ�ϵͳ��ȡ�������ļ�ϵͳ */
        return 0;
    }
    else
    {
        user_printf("SPI Flashд�����,��ʼУ��...");
        //---------------------------
        if(read_buffer!=NULL)free(read_buffer);  //�ͷŶѿռ�
        //У���ļ�-------------------
        user_printf("SPI Flash����У���ļ�...");
        uint8_t txbuff[1] = {0};
        uint8_t rxbuff[1] = {0};
        uint32_t Verify_Address = 0;

        f_rewind(&SDFile);

        for(;;)
        {
            res = f_read(&SDFile,txbuff,1,(void*)&byteswritten);
            if(res != FR_OK)
            {
                user_printf("error ��f_read_SD: res = %d",res);
                f_close(&SDFile);  /* ���ٶ�д���ر��ļ� */
                if(user_sd_path!=NULL)free(user_sd_path); //�ͷŶѿռ�
                f_mount(NULL,SDPath,1);  /* ����ʹ���ļ�ϵͳ��ȡ�������ļ�ϵͳ */
                return 0;
            }
            else if(byteswritten != 1)
            {
                break;
            }
            W25QXX_Read(rxbuff,Verify_Address,byteswritten);
            if(txbuff[0] == rxbuff[0])
            {
                txbuff[0] = 0;
                rxbuff[0] = 0;
                Verify_Address += byteswritten;  //��ַ������
            }
            else
            {
                user_printf("SPI Flash�ļ���Դ�ļ���ͬ!!!");
                f_close(&SDFile);  /* ���ٶ�д���ر��ļ� */
                if(user_sd_path!=NULL)free(user_sd_path); //�ͷŶѿռ�
                f_mount(NULL,SDPath,1);  /* ����ʹ���ļ�ϵͳ��ȡ�������ļ�ϵͳ */
                return 0;
            }
        }
        user_printf("SPI FlashУ��ͨ��!!!");
        //У�����-------------------
        f_close(&SDFile);  /* ���ٶ�д���ر��ļ� */
        if(user_sd_path!=NULL)free(user_sd_path); //�ͷŶѿռ�
        f_mount(NULL,SDPath,1);  /* ����ʹ���ļ�ϵͳ��ȡ�������ļ�ϵͳ */

        user_printf("�������ĵ�ַ�� %d",Address);

        return Address;
    }

}


/**
 * ��������: Flash_ChipErase
 * ��������: ����ȫƬ����
 * ����˵��: None
 * ����˵��: None
 * ������Ա: CY
 * ��������: 2021-03-22
 * ��������:
 *
 */
void Flash_ChipErase(void)
{
    user_printf("��ʼ����оƬ����...");
    W25QXX_ChipErase();
    user_printf("оƬ��������!!!");
}

/**
 * ��������: Flash_ReadData
 * ��������:
 * ����˵��: ReadAddress: [����] flash��ȡ��ʼ��ַ
 *			     ReadNum: [����] ���������ݳ���
 * ����˵��: None
 * ������Ա: CY
 * ��������: 2021-03-01
 *------------------*
 * ��������:
 *
 *------------------*
 */
void Flash_ReadData(uint32_t ReadAddress,uint32_t ReadNum)
{

    if(ReadNum > 200)
    {
        ReadNum = 200;
    }
    uint8_t* rxbuff = (uint8_t*)malloc(ReadNum);
    memset(rxbuff,0,ReadNum);

    W25QXX_Read(rxbuff,ReadAddress,ReadNum);

    user_printf("����������Ϊ:");
    user_printf("%s",rxbuff);
    user_printf("16���Ƶ�����Ϊ:");
    for(uint32_t i=0; i<ReadNum; i++)
    {
        printf("rxbuff[%d] = 0x%02X \n",i,rxbuff[i]);
    }

    free(rxbuff);

}
/* USER CODE END 4 */

 /**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM7 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM7) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
