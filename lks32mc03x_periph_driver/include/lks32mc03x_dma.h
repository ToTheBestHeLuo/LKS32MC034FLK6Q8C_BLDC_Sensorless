/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief �ļ����ƣ� lks32mc03x_dma.h\n
 * �ļ���ʶ�� �� \n
 * ����ժҪ�� DMA������������ͷ�ļ� \n
 * ����˵���� �� \n
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��11��10�� <td>1.0     <td>Yangzj     <td>����
 * </table>
 */
#ifndef __LKS32MC03x_DMA_H
#define __LKS32MC03x_DMA_H

#include "lks32mc03x_lib.h"

/** 
 *@brief DMA��ʼ���ṹ��������ʼ��ʱ�붨��þ��������������ַ������
 */
typedef struct
{
    /** 
     * @brief DMA �ж�ʹ��
     * @see DMA_TCIE       
     */  
    u8   DMA_IRQ_EN;               /**< DMA �ж�ʹ�� */

    u8   DMA_RMODE;                /**<  ���ִ���ʹ�ܣ�DISABLE:���ִ��䣬ENABLE:����*/
    u8   DMA_CIRC;                 /**<  ѭ��ģʽʹ�ܣ�ENABLE:ʹ�� �� DISABLE:ʧ�� */
    u8   DMA_SINC;                 /**<  Դ��ַ����ʹ�ܣ�ENABLE:ʹ�� �� DISABLE:ʧ�� */
    u8   DMA_DINC;                 /**<  Ŀ�ĵ�ַ����ʹ�ܣ�ENABLE:ʹ�� �� DISABLE:ʧ��*/
    /** 
     * @brief Դ��ַ����λ��
     * @see DMA_BYTE_TRANS    
     * @see DMA_HALFWORD_TRANS     
     * @see DMA_WORD_TRANS    
     */ 
    u8   DMA_SBTW;                 /* Դ��ַ����λ�� 0:byte, 1:half-word, 2:word */
    /** 
     * @brief Ŀ�ĵ�ַ����λ��
     * @see DMA_BYTE_TRANS    
     * @see DMA_HALFWORD_TRANS     
     * @see DMA_WORD_TRANS    
     */ 
    u8   DMA_DBTW;                 /* Ŀ�ĵ�ַ����λ�� 0:byte, 1:half-word, 2:word */
    /** 
     * @brief ͨ�� x Ӳ�� DMA ����ʹ��
     * @see DMA_SW_TRIG_REQ_EN  
     * @see DMA_I2C_REQ_EN      
     * @see DMA_GPIO_REQ_EN     
     * @see DMA_CMP_REQ_EN      
     * @see DMA_SPI_TX_REQ_EN   
     * @see DMA_SPI_RX_REQ_EN   
     * @see DMA_UART_TX_REQ_EN  
     * @see DMA_UART_RX_REQ_EN  
     * @see DMA_TIMER1_REQ_EN    
     * @see DMA_TIMER0_REQ_EN   
     * @see DMA_MCPWM_REQ_EN     
     * @see DMA_ADC_REQ_EN        
     */    
    u16  DMA_REQ_EN;               
    u32  DMA_SADR;                 /* DMA ͨ�� x Դ��ַ */
    u32  DMA_DADR;                 /* DMA ͨ�� x Ŀ�ĵ�ַ */
} DMA_InitTypeDef;
/** 
 *@brief DMA�Ĵ����ṹ����
 */
typedef struct
{
    __IO uint32_t DMA_CCR;     /**< DMA ͨ�����üĴ���*/
    __IO uint32_t DMA_REN;     /**< DMA ����ʹ�ܼĴ���*/
    __IO uint32_t DMA_CTMS;    /**< DMA ��������Ĵ���*/
    __IO uint32_t DMA_SADR;    /**< DMA Դ��ַ�Ĵ���*/
    __IO uint32_t DMA_DADR;    /**< DMA Ŀ�ĵ�ַ�Ĵ���*/
} DMA_RegTypeDef;

/**
 * DAMͨ��0�ṹ�����ַ����
 */
#ifndef DMA_CH0
#define DMA_CH0                   ((DMA_RegTypeDef *) DMA_BASE)
#endif
/**
 * DAMͨ��1�ṹ�����ַ����
 */
#ifndef DMA_CH1
#define DMA_CH1                   ((DMA_RegTypeDef *) (DMA_BASE+0x20))
#endif
/**
 * DAMͨ��2�ṹ�����ַ����
 */
#ifndef DMA_CH2
#define DMA_CH2                   ((DMA_RegTypeDef *) (DMA_BASE+0x40))
#endif
/**
 * DAMͨ��3�ṹ�����ַ����
 */
#ifndef DMA_CH3
#define DMA_CH3                   ((DMA_RegTypeDef *) (DMA_BASE+0x60))
#endif

#define DMA_TCIE                   BIT0       /**< DMA�ж�ʹ�ܶ��壬��������ж�ʹ�ܣ�����Ч */   
																  
#define CH3_FIF                    BIT3       /**< DMAͨ�� 3 ����жϱ�־������Ч��д 1 ���� */
#define CH2_FIF                    BIT2       /**< DMAͨ�� 2 ����жϱ�־������Ч��д 1 ���� */
#define CH1_FIF                    BIT1       /**< DMAͨ�� 1 ����жϱ�־������Ч��д 1 ���� */
#define CH0_FIF                    BIT0       /**< DMAͨ�� 0 ����жϱ�־������Ч��д 1 ���� */
																  
#define DMA_BYTE_TRANS             0          /**< DMA��������λ���壬����λ�� 0:byte */
#define DMA_HALFWORD_TRANS         1          /**< DMA��������λ���壬����λ�� 1:half-word */
#define DMA_WORD_TRANS             2          /**< DMA��������λ���壬����λ�� 2:word */ 

#define DMA_SW_TRIG_REQ_EN         BIT15      /**< ����DMA����Դ���壬������� */
#define DMA_I2C_REQ_EN             BIT14      /**< ����DMA����Դ���壬I2C DMA����ʹ�� */
#define DMA_GPIO_REQ_EN            BIT13      /**< ����DMA����Դ���壬GPIO DMA����ʹ�� */ 
#define DMA_CMP_REQ_EN             BIT12      /**< ����DMA����Դ���壬CMP DMA����ʹ�� */
#define DMA_SPI_TX_REQ_EN          BIT11      /**< ����DMA����Դ���壬SPI TX DMA����ʹ�� */
#define DMA_SPI_RX_REQ_EN          BIT10      /**< ����DMA����Դ���壬SPI RX DMA����ʹ�� */
#define DMA_UART_TX_REQ_EN         BIT7       /**< ����DMA����Դ���壬UART TX DMA����ʹ�� */
#define DMA_UART_RX_REQ_EN         BIT6       /**< ����DMA����Դ���壬UART RX DMA����ʹ�� */
#define DMA_TIMER1_REQ_EN          BIT5       /**< ����DMA����Դ���壬TIMER1 DMA����ʹ�� */ 
#define DMA_TIMER0_REQ_EN          BIT4       /**< ����DMA����Դ���壬TIMER0 DMA����ʹ�� */
#define DMA_HALL_REQ_EN            BIT2       /**< ����DMA����Դ���壬HALL DMA����ʹ�� */
#define DMA_MCPWM_REQ_EN           BIT1       /**< ����DMA����Դ���壬MCPWM DMA����ʹ�� */
#define DMA_ADC_REQ_EN             BIT0       /**< ����DMA����Դ���壬ADC DMA����ʹ�� */


void DMA_Init(DMA_RegTypeDef *DMAx, DMA_InitTypeDef *DMAInitStruct);
void DMA_StructInit(DMA_InitTypeDef *DMAInitStruct);
uint32_t DMA_GetIRQFlag(u32 timer_if);
void DMA_ClearIRQFlag(uint32_t tempFlag);
void DMA_CHx_EN(DMA_RegTypeDef *DMAx,u32 Channel_EN,u32 set);

#endif

