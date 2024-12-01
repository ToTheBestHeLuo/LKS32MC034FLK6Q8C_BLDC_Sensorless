/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc03x_gpio.h\n
 * 文件标识： 无 \n
 * 内容摘要： GPIO外设驱动程序头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021年11月10日     <td>1.0    <td>Yangzj      <td>创建
 * </table>
 */

#ifndef __lks32mc03x_GPIO_H
#define __lks32mc03x_GPIO_H

/* Includes ------------------------------------------------------------------*/
#include "lks32mc03x.h"
#include "basic.h"

/** 
 *@brief GPIO寄存器结构体句柄
 */
typedef struct
{
   __IO uint32_t PIE;    /*!< 输入使能 */
   __IO uint32_t POE;    /*!< 输出使能 */
   __IO uint32_t PDI;    /*!< 输入数据 */
   __IO uint32_t PDO;    /*!< 输出数据 */
   __IO uint32_t PUE;    /*!< 上拉使能 */
   __IO uint32_t null1;
   __IO uint32_t PODE;   /*!< 开漏使能 */
   __IO uint32_t null2;
   __IO uint32_t F3210;  /*!< 功能选择 GPIO_Pin_0-3 */
   __IO uint32_t F7654;  /*!< 功能选择 GPIO_Pin_4-7 */
   __IO uint32_t FBA98;  /*!< 功能选择 GPIO_Pin_8-11 */
   __IO uint32_t FFEDC;  /*!< 功能选择 GPIO_Pin_12-15 */
   __IO uint32_t BSRR;   /*!< 位置一操作 */
   __IO uint32_t BRR;    /*!< 位清零操作 */
} GPIO_TypeDef;

/** 
 *@brief EXTI寄存器结构体句柄
 */
typedef struct
{
   __IO uint32_t CR0;
   __IO uint32_t CR1;
   __IO uint32_t IE;
   __IO uint32_t IF;
   __IO uint32_t SEL;
} EXTI_TypeDef;

/**
 * GPIO0结构体基地址定义
 */
#ifndef GPIO0
#define GPIO0               ((GPIO_TypeDef *) GPIO0_BASE)
#endif

/**
 * GPIO1结构体基地址定义
 */
#ifndef GPIO1
#define GPIO1               ((GPIO_TypeDef *) GPIO1_BASE)
#endif


 /**
 * EXTI结构体基地址定义
 */
#ifndef EXTI
#define EXTI             ((EXTI_TypeDef *) EXTI_BASE)
#endif

 /**
 * EXTI触发信号定义
 */
typedef enum
{
   EXTI_Trigger_None    = 0x00, /**< 不触发*/
   EXTI_Trigger_Negedge = 0x01, /**< 下降沿触发*/
   EXTI_Trigger_Posedge = 0x02, /**< 上升沿触发*/
   EXTI_Trigger_Edge    = 0x03  /**< 上升沿、下降沿均触发*/
} EXTIMode_TypeDef;

/** 
 *@brief GPIO模式选择枚举
 */
typedef enum
{
   GPIO_Mode_IN  = 0x00, /**< GPIO输入模式*/
   GPIO_Mode_OUT = 0x01, /**< GPIO输出模式*/
   GPIO_Mode_ANA = 0x02, /**< GPIO禁止输入输出*/
	 GPIO_Mode_IO  = 0x03, /**< GPIO输入输出模式*/
} GPIOMode_TypeDef;

/** 
 *@brief GPIO输出模式选择枚举
 */
typedef enum
{
   GPIO_PuPd_NOPULL = 0x00, /**< 不配置上下拉电阻*/
   GPIO_PuPd_UP     = 0x01, /**< 上拉*/
} GPIOPuPd_TypeDef;

/** 
 *@brief GPIO寄存器写入量枚举
 */
typedef enum
{
   Bit_RESET = 0,
   Bit_SET
} BitAction;

/** 
 *@brief  GPIO功能配置结构体句柄
 */
typedef struct
{
   uint32_t          GPIO_Pin;     /*!< 要配置的Pad */                
   GPIOMode_TypeDef  GPIO_Mode;    /*!< GPIO模式:输入、输出、模拟 */
   GPIOPuPd_TypeDef  GPIO_PuPd;    /*!< 默认/上拉 */
   uint32_t          GPIO_PODEna;  /*!< 开漏 */
} GPIO_InitTypeDef;

// GPIO 复用功能
#define AF0_GPIO          0       /*!< GPIO复用功能0，模拟功能 */
#define AF1_CMP           1       /*!< GPIO复用功能1，比较器结果输出或时钟输出功能 */
#define AF2_HALL          2       /*!< GPIO复用功能2，HALL功能 */
#define AF3_MCPWM         3       /*!< GPIO复用功能3，MCPWM功能：通道信号输出或停机信号输入 */
#define AF4_UART          4       /*!< GPIO复用功能4，UART功能 */
#define AF5_SPI           5       /*!< GPIO复用功能5，SPI功能，SPI时钟、片选、数据输出、数据输入 */
#define AF6_I2C           6       /*!< GPIO复用功能6，I2C功能，I2C时钟、I2C数据 */
#define AF7_TIMER0        7       /*!< GPIO复用功能7，Timer0功能：比较模式输出、捕获模式或外部时钟源输入，对应通道0/1 */
#define AF8_TIMER1        8       /*!< GPIO复用功能8，Timer1功能：比较模式输出、捕获模式或外部时钟源输入，对应通道0/1 */
#define AF9_ADC_TRIGGER   9       /*!< GPIO复用功能9，ADC采样触发信号输出，每发生一次ADC采样，ADC_TRIGGER信号反转一次 */

/*GPIO pin脚定义*/
#define GPIO_Pin_NONE     0       /*!<GPIO pin脚定义，无pin脚  */
#define GPIO_Pin_0        BIT0    /*!<GPIO pin脚定义，pin_0脚 */
#define GPIO_Pin_1        BIT1    /*!<GPIO pin脚定义，pin_1脚  */
#define GPIO_Pin_2        BIT2    /*!<GPIO pin脚定义，pin_2脚  */
#define GPIO_Pin_3        BIT3    /*!<GPIO pin脚定义，pin_3脚  */
#define GPIO_Pin_4        BIT4    /*!<GPIO pin脚定义，pin_4脚  */
#define GPIO_Pin_5        BIT5    /*!<GPIO pin脚定义，pin_5脚  */
#define GPIO_Pin_6        BIT6    /*!<GPIO pin脚定义，pin_6脚  */
#define GPIO_Pin_7        BIT7    /*!<GPIO pin脚定义，pin_7脚  */
#define GPIO_Pin_8        BIT8    /*!<GPIO pin脚定义，pin_8脚  */
#define GPIO_Pin_9        BIT9    /*!<GPIO pin脚定义，pin_9脚  */
#define GPIO_Pin_10       BIT10   /*!<GPIO pin脚定义，pin_10脚 */
#define GPIO_Pin_11       BIT11   /*!<GPIO pin脚定义，pin_11脚 */
#define GPIO_Pin_12       BIT12   /*!<GPIO pin脚定义，pin_12脚 */
#define GPIO_Pin_13       BIT13   /*!<GPIO pin脚定义，pin_13脚 */
#define GPIO_Pin_14       BIT14   /*!<GPIO pin脚定义，pin_14脚 */
#define GPIO_Pin_15       BIT15   /*!<GPIO pin脚定义，pin_15脚 */
#define GPIO_Pin_ALL      (uint32_t)0xFFFF /*!<GPIO pin脚定义，所有pin脚*/


/*GPIO复用功能pin脚定义*/
#define GPIO_PinSource_0   0      /*!<GPIO pin脚定义，pin_0脚 */
#define GPIO_PinSource_1   1      /*!<GPIO pin脚定义，pin_1脚 */
#define GPIO_PinSource_2   2      /*!<GPIO pin脚定义，pin_2脚 */
#define GPIO_PinSource_3   3      /*!<GPIO pin脚定义，pin_3脚 */
#define GPIO_PinSource_4   4      /*!<GPIO pin脚定义，pin_4脚 */
#define GPIO_PinSource_5   5      /*!<GPIO pin脚定义，pin_5脚 */
#define GPIO_PinSource_6   6      /*!<GPIO pin脚定义，pin_6脚 */
#define GPIO_PinSource_7   7      /*!<GPIO pin脚定义，pin_7脚 */
#define GPIO_PinSource_8   8      /*!<GPIO pin脚定义，pin_8脚 */
#define GPIO_PinSource_9   9      /*!<GPIO pin脚定义，pin_9脚 */
#define GPIO_PinSource_10 10      /*!<GPIO pin脚定义，pin_10脚 */
#define GPIO_PinSource_11 11      /*!<GPIO pin脚定义，pin_11脚 */
#define GPIO_PinSource_12 12      /*!<GPIO pin脚定义，pin_12脚 */
#define GPIO_PinSource_13 13      /*!<GPIO pin脚定义，pin_13脚 */
#define GPIO_PinSource_14 14      /*!<GPIO pin脚定义，pin_14脚 */
#define GPIO_PinSource_15 15      /*!<GPIO pin脚定义，pin_15脚 */

/*EXTI_IF 中断标志位定义*/
#define GPIO_P00_EXTI_IF  BIT0   /*!< GPIO0[0]/P0[0] 外部中断标志*/
#define GPIO_P02_EXTI_IF  BIT1   /*!< GPIO0[2]/P0[2] 外部中断标志*/
#define GPIO_P04_EXTI_IF  BIT2   /*!< GPIO0[4]/P0[4] 外部中断标志*/
#define GPIO_P05_EXTI_IF  BIT3   /*!< GPIO0[5]/P0[5] 外部中断标志*/
#define GPIO_P06_EXTI_IF  BIT4   /*!< GPIO0[6]/P0[6] 外部中断标志*/
#define GPIO_P07_EXTI_IF  BIT5   /*!< GPIO0[7]/P0[7] 外部中断标志*/
#define GPIO_P08_EXTI_IF  BIT6   /*!< GPIO0[8]/P0[8] 外部中断标志*/
#define GPIO_P09_EXTI_IF  BIT7   /*!< GPIO0[9]/P0[9] 外部中断标志*/
#define GPIO_P014_EXTI_IF BIT8   /*!< GPIO0[14]/P0[14] 外部中断标志*/
#define GPIO_P015_EXTI_IF BIT9   /*!< GPIO0[15]/P0[15] 外部中断标志*/
#define GPIO_P14_EXTI_IF  BIT10  /*!< GPIO1[4]/P1[4] 外部中断标志*/
#define GPIO_P15_EXTI_IF  BIT11  /*!< GPIO1[5]/P1[5] 外部中断标志*/
#define GPIO_P16_EXTI_IF  BIT12  /*!< GPIO1[6]/P1[6] 外部中断标志*/
#define GPIO_P17_EXTI_IF  BIT13  /*!< GPIO1[7]/P1[7] 外部中断标志*/
#define GPIO_P18_EXTI_IF  BIT14  /*!< GPIO1[8]/P1[8] 外部中断标志*/
#define GPIO_P19_EXTI_IF  BIT15  /*!< GPIO1[9]/P1[9] 外部中断标志*/

/*CLKO_SEL 时钟信号调试输出选择*/
#define CLKO_SEL_ADC BIT3   /*!< ADC 输出使能 24MHz */
#define CLKO_SEL_PLL BIT2   /*!< PLL 输出使能 48MHz 无法驱动负载 */
#define CLKO_SEL_HSI BIT1   /*!< HSI 输出使能 4MHz */
#define CLKO_SEL_LSI BIT0   /*!< LSI 输出使能 64kHz */

/* 初始化、配置函数 *********************************/
void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_InitStruct);
void GPIO_StructInit(GPIO_InitTypeDef *GPIO_InitStruct);

/* GPIO读写函数 *************************************/
uint32_t GPIO_ReadInputData    (GPIO_TypeDef *GPIOx);
uint32_t GPIO_ReadOutputData   (GPIO_TypeDef *GPIOx);
uint8_t  GPIO_ReadInputDataBit (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
uint8_t  GPIO_ReadOutputDataBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

void GPIO_Write     (GPIO_TypeDef *GPIOx, uint32_t Val);
void GPIO_SetBits   (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void GPIO_ResetBits (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void GPIO_WriteBit  (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, BitAction BitVal);

/* GPIO功能选择函数 ***************************/
void GPIO_PinAFConfig(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource, uint32_t GPIO_AF);

/* EXTI相关函数 ***************************/
void EXTI_Trigger_Config(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource, uint16_t EXTI_Trigger);
void EXTI_ClearIRQFlag(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource);
u8 EXTI_GetIRQFlag(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource);

#endif /*__lks32mc03x_GPIO_H */

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
