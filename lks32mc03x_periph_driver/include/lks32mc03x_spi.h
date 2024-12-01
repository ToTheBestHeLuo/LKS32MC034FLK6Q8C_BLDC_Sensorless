 /**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief �ļ����ƣ� lks32mc03x_spi.h\n
 * �ļ���ʶ�� �� \n
 * ����ժҪ�� SPI����ͷ�ļ� \n
 * ����˵���� �� \n
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��11��10��   <td>1.0     <td>Yangzj       <td>����
 * </table>
 */
 
#ifndef __LKS32MC03x_SPI_H
#define __LKS32MC03x_SPI_H


/* Includes ------------------------------------------------------------------*/
#include "lks32mc03x_lib.h"

 /** 
 *@brief SPIģʽ����ö��
 */
typedef enum
{
   SPI_Master = 0x01, /**< SPI��ģʽ */
   SPI_Slave  = 0x00  /**< SPI��ģʽ */
}SPI_Mode;

 /** 
 *@brief SPI����ģʽ����ö��
 */
typedef enum
{
   SPI_Full    = 0x0, /**< SPIȫ˫�� */
   SPI_Half_Tx = 0x2, /**< SPI��˫�������� */
   SPI_Half_Rx = 0x3  /**< SPI��˫�������� */
}SPI_Duplex;

/** 
 *@brief SPI�Ĵ����ṹ����
 */
typedef struct
{
   __IO uint32_t CFG;     /**< SPI���ƼĴ��� */
   __IO uint32_t IE;      /**< SPI�жϼĴ��� */
   __IO uint32_t BAUD;    /**< SPI�����ʿ��ƼĴ��� */
   __IO uint32_t TX_DATA; /**< SPI�������ݼĴ��� */
   __IO uint32_t RX_DATA; /**< SPI�������ݼĴ��� */
   __IO uint32_t SIZE;    /**< SPI�������ݳ��ȼĴ��� */
}SPI_TypeDef;

/**
 * SPI�ṹ�����ַ����
 */
#ifndef   SPI
#define   SPI     ((SPI_TypeDef *) SPI_BASE)
#endif

 /** 
 *@brief SPI��ʼ���ṹ��������ʼ��ʱ�붨��þ��������������ַ������
 */
typedef struct
{
   /** 
    * @brief ȫ˫������˫������ģʽѡ��0��ȫ˫����2����˫�������ͣ�3����˫��������  \n
    * @see SPI_Duplex     
    */ 
   SPI_Duplex Duplex;       /**< ��˫��ģʽ����*/
   uint8_t    CS;           /**< SPI ���豸�£�Ƭѡ�ź���Դ��0:Slave ģʽ�£�Ƭѡ�źź�Ϊ��Чֵ 1:Slave ģʽ�£�Ƭѡ�ź����� Master �豸*/
   /** 
    * @brief ����ģʽѡ��0����ģʽ��1����ģʽ  \n
    * @see SPI_Mode     
    */
   SPI_Mode   Mode;         /**< SPI ����ģʽѡ��*/
   uint8_t    CPHA;         /**< SPI ��λѡ��*/
   uint8_t    CPOL;         /**< SPI ����ѡ��*/
   uint8_t    ENDIAN;       /**< SPI ģ�鴫��˳��*/
   uint8_t    EN;           /**< SPI Enable Signal, 0: disable;1: enable*/
   /** 
   * @brief SPI�ж�ʹ�ܣ�DISABLE���ر������ж�  \n
   * @see SPI_IRQEna_Enable     \n  
   * @see SPI_IRQEna_TranDone   \n  
   * @see SPI_IRQEna_SSErr      \n  
   * @see SPI_IRQEna_DataOver    
   */
   uint8_t    IRQEna;       /**< SPI �ж�ʹ�ܡ�*/
   uint8_t    TRANS_TRIG;   /**< ���䴥��ѡ��*/

   uint8_t    TRANS_MODE;   /**< SPI ���ݰ��Ʒ�ʽ��0 DMA ��ʽ��*/
   uint8_t    BAUD;         /**< SPI ���䲨��������, SPI �����ٶ� = ϵͳʱ�� / (2*(BAUD + 1)),��СΪ3 */

   uint8_t    BITSIZE;      /**< SPI���������ֽڳ��ȼĴ�����8-16 */
}SPI_InitTypeDef;

#define SPI_FIRSTSEND_LSB 1    /**< ��λ�ȴ� */
#define SPI_FIRSTSEND_MSB 0    /**< ��λ�ȴ� */

#define SPI_DMA_ENABLE     0   /**< ʹ��DMA���� */
#define SPI_DMA_DISABLE    1   /**< ��ֹDMA���� */

#define SPI_DMA_CARRY      0   /**< SPI��DMA���� */
#define SPI_MCU_CARRY      1   /**< SPI��MCU���� */

/*�ж�ʹ�ܶ���*/
#define SPI_IRQEna_Enable              BIT7            /**<�ж�ʹ�ܶ��壬SPI�ж�ʹ�� */
#define SPI_IRQEna_TranDone            BIT6            /**<�ж�ʹ�ܶ��壬��������ж� */
#define SPI_IRQEna_SSErr               BIT5            /**<�ж�ʹ�ܶ��壬�����쳣�¼��ж� */
#define SPI_IRQEna_DataOver            BIT4            /**<�ж�ʹ�ܶ��壬��������¼��ж� */

/*�жϱ�־����*/
#define SPI_IF_TranDone                BIT2            /**<�жϱ�־���壬��������жϱ�־λ */
#define SPI_IF_SSErr                   BIT1            /**<�жϱ�־���壬�����쳣�жϱ�־λ */
#define SPI_IF_DataOver                BIT0            /**<�жϱ�־���壬��������жϱ�־λ */

void SPI_Init(SPI_TypeDef *SPIx, SPI_InitTypeDef *SPI_InitStruct);
void SPI_StructInit(SPI_InitTypeDef *SPI_InitStruct);

uint8_t SPI_GetIRQFlag(SPI_TypeDef *SPIx,u8 IRQ_Flag);
void SPI_ClearIRQFlag(SPI_TypeDef *SPIx,u8 IRQ_Flag);

void    SPI_SendData(SPI_TypeDef *SPIx, uint8_t n);
uint8_t SPI_ReadData(SPI_TypeDef *SPIx);
#endif /*__lks32mc03x_SPI_H */

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
