/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief �ļ����ƣ� lks32mc03x_gpio.h\n
 * �ļ���ʶ�� �� \n
 * ����ժҪ�� GPIO������������ͷ�ļ� \n
 * ����˵���� �� \n
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��11��10��     <td>1.0    <td>Yangzj      <td>����
 * </table>
 */

#ifndef __lks32mc03x_GPIO_H
#define __lks32mc03x_GPIO_H

/* Includes ------------------------------------------------------------------*/
#include "lks32mc03x.h"
#include "basic.h"

/** 
 *@brief GPIO�Ĵ����ṹ����
 */
typedef struct
{
   __IO uint32_t PIE;    /*!< ����ʹ�� */
   __IO uint32_t POE;    /*!< ���ʹ�� */
   __IO uint32_t PDI;    /*!< �������� */
   __IO uint32_t PDO;    /*!< ������� */
   __IO uint32_t PUE;    /*!< ����ʹ�� */
   __IO uint32_t null1;
   __IO uint32_t PODE;   /*!< ��©ʹ�� */
   __IO uint32_t null2;
   __IO uint32_t F3210;  /*!< ����ѡ�� GPIO_Pin_0-3 */
   __IO uint32_t F7654;  /*!< ����ѡ�� GPIO_Pin_4-7 */
   __IO uint32_t FBA98;  /*!< ����ѡ�� GPIO_Pin_8-11 */
   __IO uint32_t FFEDC;  /*!< ����ѡ�� GPIO_Pin_12-15 */
   __IO uint32_t BSRR;   /*!< λ��һ���� */
   __IO uint32_t BRR;    /*!< λ������� */
} GPIO_TypeDef;

/** 
 *@brief EXTI�Ĵ����ṹ����
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
 * GPIO0�ṹ�����ַ����
 */
#ifndef GPIO0
#define GPIO0               ((GPIO_TypeDef *) GPIO0_BASE)
#endif

/**
 * GPIO1�ṹ�����ַ����
 */
#ifndef GPIO1
#define GPIO1               ((GPIO_TypeDef *) GPIO1_BASE)
#endif


 /**
 * EXTI�ṹ�����ַ����
 */
#ifndef EXTI
#define EXTI             ((EXTI_TypeDef *) EXTI_BASE)
#endif

 /**
 * EXTI�����źŶ���
 */
typedef enum
{
   EXTI_Trigger_None    = 0x00, /**< ������*/
   EXTI_Trigger_Negedge = 0x01, /**< �½��ش���*/
   EXTI_Trigger_Posedge = 0x02, /**< �����ش���*/
   EXTI_Trigger_Edge    = 0x03  /**< �����ء��½��ؾ�����*/
} EXTIMode_TypeDef;

/** 
 *@brief GPIOģʽѡ��ö��
 */
typedef enum
{
   GPIO_Mode_IN  = 0x00, /**< GPIO����ģʽ*/
   GPIO_Mode_OUT = 0x01, /**< GPIO���ģʽ*/
   GPIO_Mode_ANA = 0x02, /**< GPIO��ֹ�������*/
	 GPIO_Mode_IO  = 0x03, /**< GPIO�������ģʽ*/
} GPIOMode_TypeDef;

/** 
 *@brief GPIO���ģʽѡ��ö��
 */
typedef enum
{
   GPIO_PuPd_NOPULL = 0x00, /**< ����������������*/
   GPIO_PuPd_UP     = 0x01, /**< ����*/
} GPIOPuPd_TypeDef;

/** 
 *@brief GPIO�Ĵ���д����ö��
 */
typedef enum
{
   Bit_RESET = 0,
   Bit_SET
} BitAction;

/** 
 *@brief  GPIO�������ýṹ����
 */
typedef struct
{
   uint32_t          GPIO_Pin;     /*!< Ҫ���õ�Pad */                
   GPIOMode_TypeDef  GPIO_Mode;    /*!< GPIOģʽ:���롢�����ģ�� */
   GPIOPuPd_TypeDef  GPIO_PuPd;    /*!< Ĭ��/���� */
   uint32_t          GPIO_PODEna;  /*!< ��© */
} GPIO_InitTypeDef;

// GPIO ���ù���
#define AF0_GPIO          0       /*!< GPIO���ù���0��ģ�⹦�� */
#define AF1_CMP           1       /*!< GPIO���ù���1���Ƚ�����������ʱ��������� */
#define AF2_HALL          2       /*!< GPIO���ù���2��HALL���� */
#define AF3_MCPWM         3       /*!< GPIO���ù���3��MCPWM���ܣ�ͨ���ź������ͣ���ź����� */
#define AF4_UART          4       /*!< GPIO���ù���4��UART���� */
#define AF5_SPI           5       /*!< GPIO���ù���5��SPI���ܣ�SPIʱ�ӡ�Ƭѡ������������������� */
#define AF6_I2C           6       /*!< GPIO���ù���6��I2C���ܣ�I2Cʱ�ӡ�I2C���� */
#define AF7_TIMER0        7       /*!< GPIO���ù���7��Timer0���ܣ��Ƚ�ģʽ���������ģʽ���ⲿʱ��Դ���룬��Ӧͨ��0/1 */
#define AF8_TIMER1        8       /*!< GPIO���ù���8��Timer1���ܣ��Ƚ�ģʽ���������ģʽ���ⲿʱ��Դ���룬��Ӧͨ��0/1 */
#define AF9_ADC_TRIGGER   9       /*!< GPIO���ù���9��ADC���������ź������ÿ����һ��ADC������ADC_TRIGGER�źŷ�תһ�� */

/*GPIO pin�Ŷ���*/
#define GPIO_Pin_NONE     0       /*!<GPIO pin�Ŷ��壬��pin��  */
#define GPIO_Pin_0        BIT0    /*!<GPIO pin�Ŷ��壬pin_0�� */
#define GPIO_Pin_1        BIT1    /*!<GPIO pin�Ŷ��壬pin_1��  */
#define GPIO_Pin_2        BIT2    /*!<GPIO pin�Ŷ��壬pin_2��  */
#define GPIO_Pin_3        BIT3    /*!<GPIO pin�Ŷ��壬pin_3��  */
#define GPIO_Pin_4        BIT4    /*!<GPIO pin�Ŷ��壬pin_4��  */
#define GPIO_Pin_5        BIT5    /*!<GPIO pin�Ŷ��壬pin_5��  */
#define GPIO_Pin_6        BIT6    /*!<GPIO pin�Ŷ��壬pin_6��  */
#define GPIO_Pin_7        BIT7    /*!<GPIO pin�Ŷ��壬pin_7��  */
#define GPIO_Pin_8        BIT8    /*!<GPIO pin�Ŷ��壬pin_8��  */
#define GPIO_Pin_9        BIT9    /*!<GPIO pin�Ŷ��壬pin_9��  */
#define GPIO_Pin_10       BIT10   /*!<GPIO pin�Ŷ��壬pin_10�� */
#define GPIO_Pin_11       BIT11   /*!<GPIO pin�Ŷ��壬pin_11�� */
#define GPIO_Pin_12       BIT12   /*!<GPIO pin�Ŷ��壬pin_12�� */
#define GPIO_Pin_13       BIT13   /*!<GPIO pin�Ŷ��壬pin_13�� */
#define GPIO_Pin_14       BIT14   /*!<GPIO pin�Ŷ��壬pin_14�� */
#define GPIO_Pin_15       BIT15   /*!<GPIO pin�Ŷ��壬pin_15�� */
#define GPIO_Pin_ALL      (uint32_t)0xFFFF /*!<GPIO pin�Ŷ��壬����pin��*/


/*GPIO���ù���pin�Ŷ���*/
#define GPIO_PinSource_0   0      /*!<GPIO pin�Ŷ��壬pin_0�� */
#define GPIO_PinSource_1   1      /*!<GPIO pin�Ŷ��壬pin_1�� */
#define GPIO_PinSource_2   2      /*!<GPIO pin�Ŷ��壬pin_2�� */
#define GPIO_PinSource_3   3      /*!<GPIO pin�Ŷ��壬pin_3�� */
#define GPIO_PinSource_4   4      /*!<GPIO pin�Ŷ��壬pin_4�� */
#define GPIO_PinSource_5   5      /*!<GPIO pin�Ŷ��壬pin_5�� */
#define GPIO_PinSource_6   6      /*!<GPIO pin�Ŷ��壬pin_6�� */
#define GPIO_PinSource_7   7      /*!<GPIO pin�Ŷ��壬pin_7�� */
#define GPIO_PinSource_8   8      /*!<GPIO pin�Ŷ��壬pin_8�� */
#define GPIO_PinSource_9   9      /*!<GPIO pin�Ŷ��壬pin_9�� */
#define GPIO_PinSource_10 10      /*!<GPIO pin�Ŷ��壬pin_10�� */
#define GPIO_PinSource_11 11      /*!<GPIO pin�Ŷ��壬pin_11�� */
#define GPIO_PinSource_12 12      /*!<GPIO pin�Ŷ��壬pin_12�� */
#define GPIO_PinSource_13 13      /*!<GPIO pin�Ŷ��壬pin_13�� */
#define GPIO_PinSource_14 14      /*!<GPIO pin�Ŷ��壬pin_14�� */
#define GPIO_PinSource_15 15      /*!<GPIO pin�Ŷ��壬pin_15�� */

/*EXTI_IF �жϱ�־λ����*/
#define GPIO_P00_EXTI_IF  BIT0   /*!< GPIO0[0]/P0[0] �ⲿ�жϱ�־*/
#define GPIO_P02_EXTI_IF  BIT1   /*!< GPIO0[2]/P0[2] �ⲿ�жϱ�־*/
#define GPIO_P04_EXTI_IF  BIT2   /*!< GPIO0[4]/P0[4] �ⲿ�жϱ�־*/
#define GPIO_P05_EXTI_IF  BIT3   /*!< GPIO0[5]/P0[5] �ⲿ�жϱ�־*/
#define GPIO_P06_EXTI_IF  BIT4   /*!< GPIO0[6]/P0[6] �ⲿ�жϱ�־*/
#define GPIO_P07_EXTI_IF  BIT5   /*!< GPIO0[7]/P0[7] �ⲿ�жϱ�־*/
#define GPIO_P08_EXTI_IF  BIT6   /*!< GPIO0[8]/P0[8] �ⲿ�жϱ�־*/
#define GPIO_P09_EXTI_IF  BIT7   /*!< GPIO0[9]/P0[9] �ⲿ�жϱ�־*/
#define GPIO_P014_EXTI_IF BIT8   /*!< GPIO0[14]/P0[14] �ⲿ�жϱ�־*/
#define GPIO_P015_EXTI_IF BIT9   /*!< GPIO0[15]/P0[15] �ⲿ�жϱ�־*/
#define GPIO_P14_EXTI_IF  BIT10  /*!< GPIO1[4]/P1[4] �ⲿ�жϱ�־*/
#define GPIO_P15_EXTI_IF  BIT11  /*!< GPIO1[5]/P1[5] �ⲿ�жϱ�־*/
#define GPIO_P16_EXTI_IF  BIT12  /*!< GPIO1[6]/P1[6] �ⲿ�жϱ�־*/
#define GPIO_P17_EXTI_IF  BIT13  /*!< GPIO1[7]/P1[7] �ⲿ�жϱ�־*/
#define GPIO_P18_EXTI_IF  BIT14  /*!< GPIO1[8]/P1[8] �ⲿ�жϱ�־*/
#define GPIO_P19_EXTI_IF  BIT15  /*!< GPIO1[9]/P1[9] �ⲿ�жϱ�־*/

/*CLKO_SEL ʱ���źŵ������ѡ��*/
#define CLKO_SEL_ADC BIT3   /*!< ADC ���ʹ�� 24MHz */
#define CLKO_SEL_PLL BIT2   /*!< PLL ���ʹ�� 48MHz �޷��������� */
#define CLKO_SEL_HSI BIT1   /*!< HSI ���ʹ�� 4MHz */
#define CLKO_SEL_LSI BIT0   /*!< LSI ���ʹ�� 64kHz */

/* ��ʼ�������ú��� *********************************/
void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_InitStruct);
void GPIO_StructInit(GPIO_InitTypeDef *GPIO_InitStruct);

/* GPIO��д���� *************************************/
uint32_t GPIO_ReadInputData    (GPIO_TypeDef *GPIOx);
uint32_t GPIO_ReadOutputData   (GPIO_TypeDef *GPIOx);
uint8_t  GPIO_ReadInputDataBit (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
uint8_t  GPIO_ReadOutputDataBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

void GPIO_Write     (GPIO_TypeDef *GPIOx, uint32_t Val);
void GPIO_SetBits   (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void GPIO_ResetBits (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void GPIO_WriteBit  (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, BitAction BitVal);

/* GPIO����ѡ���� ***************************/
void GPIO_PinAFConfig(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource, uint32_t GPIO_AF);

/* EXTI��غ��� ***************************/
void EXTI_Trigger_Config(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource, uint16_t EXTI_Trigger);
void EXTI_ClearIRQFlag(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource);
u8 EXTI_GetIRQFlag(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource);

#endif /*__lks32mc03x_GPIO_H */

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
