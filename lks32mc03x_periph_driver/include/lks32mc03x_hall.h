/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief �ļ����ƣ� lks32mc03x_hall.h\n
 * �ļ���ʶ�� �� \n
 * ����ժҪ�� HALL����ͷ�ļ� \n
 * ����˵���� �� \n
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��10��14��    <td>1.0     <td>HMG     <td>����
 * </table>
 */
#ifndef __LKS32MC03x_HALL_H
#define __LKS32MC03x_HALL_H

/* Includes ------------------------------------------------------------------*/
#include "lks32mc03x_lib.h"

/** 
 *@brief HALL�Ĵ����ṹ����
 */
typedef struct
{
   __IO uint32_t CFG;    /**< HALL ģ�����üĴ��� */ 
   __IO uint32_t INFO;   /**< HALL ģ����Ϣ�Ĵ��� */ 
   __IO uint32_t WIDTH;  /**< HALL ��ȼ���ֵ�Ĵ���*/ 
   __IO uint32_t TH;     /**< HALL ģ�����������ֵ�Ĵ���*/
   __IO uint32_t CNT;    /**< HALL �����Ĵ���*/ 

} HALL_TypeDef;

/**
 * HALL�ṹ�����ַ����
 */
#ifndef  HALL
#define  HALL        ((HALL_TypeDef *) HALL_BASE)
#endif

/** 
 *@brief HALL��ʼ���ṹ��������ʼ��ʱ�붨��þ��������������ַ������
 */
typedef struct
{
   uint16_t FilterLen;       /**<�˲�����,0��Ӧ����1,1023��Ӧ����1024�˲�����*/
   uint8_t ClockDivision;    /**<��Ƶ 0~3:/1 /2 /4 /8*/
   uint8_t Filter75_Ena;     /**<ʹ�ܵ�һ��7/5�˲�,ENABLE��ʹ�� DISABLE��ʧ��*/
   uint8_t HALL_Ena;         /**<ʹ��HALL,ENABLE��ʹ�� DISABLE��ʧ��*/
   uint8_t HALL_CHGDMA_Ena;  /**<HALL�źű仯DMA����ʹ��,ENABLE��ʹ�� DISABLE��ʧ��*/
   uint8_t HALL_OVDMA_Ena;   /**<HALL���������DMA����ʹ��,ENABLE��ʹ�� DISABLE��ʧ��*/
   uint8_t Capture_IRQ_Ena;  /**<HALL�źű仯�ж�ʹ��,ENABLE��ʹ�� DISABLE��ʧ��*/
   uint8_t OverFlow_IRQ_Ena; /**<HALL����������ж�ʹ��,ENABLE��ʹ�� DISABLE��ʧ��*/
   uint32_t CountTH;         /**<HALL����������ֵ*/
   uint8_t softIE;           /**<����ж�ʹ�� */
} HALL_InitTypeDef;

#define HALL_CLK_DIV1 ((uint32_t)0x00) /**< HALLʱ��Ϊ��ʱ��1��Ƶ*/
#define HALL_CLK_DIV2 ((uint32_t)0x01) /**< HALLʱ��Ϊ��ʱ��2��Ƶ*/
#define HALL_CLK_DIV4 ((uint32_t)0x02) /**< HALLʱ��Ϊ��ʱ��4��Ƶ*/
#define HALL_CLK_DIV8 ((uint32_t)0x03) /**< HALLʱ��Ϊ��ʱ��8��Ƶ*/
/*HALL�ж�ʹ�ܺͱ�־����*/
#define HALL_CAPTURE_EVENT ((uint32_t)0x00010000)   /**< HALL�źű仯�ж�*/
#define HALL_OVERFLOW_EVENT ((uint32_t)0x00020000)  /**< HALL�ź�����ж�*/

void HALL_Init(HALL_InitTypeDef *HALL_InitStruct);
void HALL_StructInit(HALL_InitTypeDef *HALL_InitStruct);

uint32_t HALL_GetFilterValue(void);
uint32_t HALL_GetCaptureValue(void);
uint32_t HALL_WIDCount(void);
uint32_t HALL_GetCount(void);

uint32_t HALL_GetIRQFlag(uint32_t tempFlag);
void HALL_ClearIRQFlag(uint32_t tempFlag);


#endif /*__lks32mc03x_HALL_H */

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
