/**
 * @file 
 * @copyright (C)2021, LINKO SEMICONDUCTOR Co.ltd
 * @brief �ļ����ƣ� lks32mc03x_adc.h\n
 * �ļ���ʶ�� �� \n
 * ����ժҪ�� ADC����ͷ�ļ� \n
 * ����˵���� �� \n
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��10��14�� <td>1.0     <td>HMG      <td>����
 * </table>
 */
#ifndef _LKS32MC03x_ADC_H_
#define _LKS32MC03x_ADC_H_

/** 
 *@brief ADC�Ĵ����ṹ����
 */
#include "lks32mc03x_lib.h"
typedef struct
{
    __IO uint32_t DAT0;   /**< ADC���ݼĴ���0 */
    __IO uint32_t DAT1;   /**< ADC���ݼĴ���1 */
    __IO uint32_t DAT2;   /**< ADC���ݼĴ���2 */
    __IO uint32_t DAT3;   /**< ADC���ݼĴ���3 */
    __IO uint32_t DAT4;   /**< ADC���ݼĴ���4 */
    __IO uint32_t DAT5;   /**< ADC���ݼĴ���5 */
    __IO uint32_t DAT6;   /**< ADC���ݼĴ���6 */
    __IO uint32_t DAT7;   /**< ADC���ݼĴ���7 */
    __IO uint32_t DAT8;   /**< ADC���ݼĴ���8 */
    __IO uint32_t DAT9;   /**< ADC���ݼĴ���9 */
	
    __IO uint32_t null0;    /**< ���� */
    __IO uint32_t null1;    /**< ���� */
	
    __IO uint32_t LTH;      /**< ADCģ�⿴�Ź�����ֵ */
    __IO uint32_t HTH;      /**< ADCģ�⿴�Ź�����ֵ */
    __IO uint32_t GEN;      /**< ADCģ�⿴�Ź����ʹ�� */
	
    __IO uint32_t null2;    /**< ���� */
	
    __IO uint32_t CHN0;     /**< ADC�����ź���Դ�Ĵ���0 */
    __IO uint32_t CHN1;     /**< ADC�����ź���Դ�Ĵ���1 */
    __IO uint32_t CHN2;     /**< ADC�����ź���Դ�Ĵ���2 */
		
    __IO uint32_t null3;    /**< ���� */

    __IO uint32_t CHNT;     /**< ADCÿ���β���ͨ�������üĴ��� */

    __IO uint32_t CFG;      /**< ADCģʽ���üĴ��� */
    __IO uint32_t SWT;      /**< ADC��������Ĵ��� */

    __IO uint32_t null4;    /**< ���� */

    __IO uint32_t DC;       /**< ADCֱ��ƫ�üĴ��� */
    __IO uint32_t AMC;      /**< ADC����У���Ĵ��� */

    __IO uint32_t IE;       /**< ADC�жϼĴ��� */
		__IO uint32_t IF;       /**< ADC�жϱ�־λ�Ĵ��� */

} ADC_TypeDef;

/**
 * ADC�ṹ�����ַ����
 */
#ifndef  ADC
#define  ADC    ((ADC_TypeDef *) ADC_BASE)
#endif
/** 
 *@brief ADC��ʼ���ṹ��������ʼ��ʱ�붨��þ��������������ַ������
 */
typedef struct
{
	  uint16_t ADC_SAMP_CLK;     /**< ADC ����ʱ��ѡ���5->36��ADCʱ�����ڿ�ѡ*/
    /** 
     * @brief ADC�ж�ʹ�� \n
     * @see ADC_EOS0_IRQ_EN  \n 
     * @see ADC_EOS1_IRQ_EN  \n   
     * @see ADC_EOS2_IRQ_EN  \n
     * @see ADC_EOS3_IRQ_EN  \n
     * @see ADC_CONFLICT_IRQ_EN  \n   
     * @see ADC_HERR_IRQ_EN  \n     
     * @see ADC_DAT0_OV_IRQ_EN  \n      
     */  
    uint16_t IE;
	  /**
     * @brief TADC������Դѡ�� \n
     * @see ADC_MCPWM_TRG  \n
     * @see ADC_UTIMER_TRG   \n  
     */ 
	  uint16_t SEL_En;       
	  uint16_t FSM_RESET;      /**< ADC ״̬����λ�����ź�  */

    /**
     * @brief �������ݶ��뷽ʽ \n
     * @see ADC_LEFT_ALIGN  \n
     * @see ADC_RIGHT_ALIGN   \n  
     */ 
    uint16_t Align;        
    /**
     * @brief ADC ����ģʽ ���Ρ�˫�λ��Ķ� \n
     * @see ADC_1SEG_TRG  \n
     * @see ADC_2SEG_TRG  \n  
     * @see ADC_4SEG_TRG  
     */
    uint16_t Trigger_Mode; 
    /**
     * @brief Trigger_Cnt����1������Ҫ����ADC���βɽ���һ��ADC����ת�������÷�Χ0~15����ʾ��Ҫ1~16�δ����¼�
     */ 
    uint16_t Trigger_Cnt;  /**< ����ģʽ�´�����һ�β�������Ĵ����¼��� */
    /**
     * @brief TADC����ADC����ʹ���ź� \n
     * @see ADC_HARDWARE_T0_TRG  \n
     * @see ADC_HARDWARE_T1_TRG  \n  
     * @see ADC_HARDWARE_T2_TRG  \n
     * @see ADC_HARDWARE_T3_TRG  
     */
	  uint16_t Trigger_En;   
	  /**
     * @brief ʹ�øöβ�����Ӧ�εĲ���������������Ϊ0�����δ�øöβ�������������������Ϊ0��
     */ 
    uint16_t FirSeg_Ch;    /**< ��һ�β�������ͨ���� */
    /**
     * @brief ʹ�øöβ�����Ӧ�εĲ���������������Ϊ0�����δ�øöβ�������������������Ϊ0��
     */ 
    uint16_t SecSeg_Ch;    /**< �ڶ��β�������ͨ���� */
    /**
     * @brief ʹ�øöβ�����Ӧ�εĲ���������������Ϊ0�����δ�øöβ�������������������Ϊ0��
     */ 
    uint16_t ThrSeg_Ch;    /**< �����β�������ͨ���� */
    /**
     * @brief ʹ�øöβ�����Ӧ�εĲ���������������Ϊ0�����δ�øöβ�������������������Ϊ0��
     */ 
    uint16_t FouSeg_Ch;    /**< ���Ķβ�������ͨ���� */
    /**
     * @brief ADCģ�⿴�Ź���Ӧλʹ���ź� \n
     * @see ADC_GEN_DAT0  \n
     * @see ADC_GEN_DAT1  \n  
     * @see ADC_GEN_DAT2  \n  
     * @see ADC_GEN_DAT3  \n
     * @see ADC_GEN_DAT4  \n  
     * @see ADC_GEN_DAT5  \n
     * @see ADC_GEN_DAT6  \n
     * @see ADC_GEN_DAT7  \n  
     * @see ADC_GEN_DAT8  \n
     * @see ADC_GEN_DAT9  \n
     */
    uint16_t ADC_GEN_En;   
    uint16_t ADC_GEN_HTH;  /**< ADCģ�⿴�Ź�����ֵ */
    uint16_t ADC_GEN_LTH;  /**< ADCģ�⿴�Ź�����ֵ */
	  uint16_t REFOUT_EN;    /**< ADC REF���ʹ��*/
	  /**
     * @brief ADC����ѡ�� \n
     * @see ADC_RANGE_2V4 \n
     * @see ADC_RANGE_3V6   
     */    
	  uint16_t ADC_RANGE;    

} ADC_InitTypeDef;

#define ADC_MCPWM_TRG            (0x00)   /**< ѡ��MCPWMΪADC������Դ */
#define ADC_UTIMER_TRG           (0x01)   /**< ѡ��UTIMERΪADC������Դ */

#define ADC_RANGE_2V4            (0x01)    /*ADC����2.4V*/
#define ADC_RANGE_3V6            (0x00)    /*ADC����3.6V*/

#define ADC_1_TIMES_SAMPLE       ((u8)1) /**< ADC����ͨ����1�β��� */
#define ADC_2_TIMES_SAMPLE       ((u8)2) /**< ADC����ͨ����2�β��� */
#define ADC_3_TIMES_SAMPLE       ((u8)3) /**< ADC����ͨ����3�β��� */
#define ADC_4_TIMES_SAMPLE       ((u8)4) /**< ADC����ͨ����4�β��� */
#define ADC_5_TIMES_SAMPLE       ((u8)5) /**< ADC����ͨ����5�β��� */
#define ADC_6_TIMES_SAMPLE       ((u8)6) /**< ADC����ͨ����6�β��� */
#define ADC_7_TIMES_SAMPLE       ((u8)7) /**< ADC����ͨ����7�β��� */
#define ADC_8_TIMES_SAMPLE       ((u8)8) /**< ADC����ͨ����8�β��� */
#define ADC_9_TIMES_SAMPLE       ((u8)9) /**< ADC����ͨ����9�β��� */

#define ADC_GEN_DAT0             ((uint16_t)0x01)  /**< DAT0���Ź����ʹ�� */
#define ADC_GEN_DAT1             ((uint16_t)0x02)  /**< DAT1���Ź����ʹ�� */
#define ADC_GEN_DAT2             ((uint16_t)0x04)  /**< DAT2���Ź����ʹ�� */
#define ADC_GEN_DAT3             ((uint16_t)0x08)  /**< DAT3���Ź����ʹ�� */
#define ADC_GEN_DAT4             ((uint16_t)0x10)  /**< DAT4���Ź����ʹ�� */
#define ADC_GEN_DAT5             ((uint16_t)0x20)  /**< DAT5���Ź����ʹ�� */
#define ADC_GEN_DAT6             ((uint16_t)0x40)  /**< DAT6���Ź����ʹ�� */
#define ADC_GEN_DAT7             ((uint16_t)0x80)  /**< DAT7���Ź����ʹ�� */
#define ADC_GEN_DAT8             ((uint16_t)0x100) /**< DAT8���Ź����ʹ�� */
#define ADC_GEN_DAT9             ((uint16_t)0x200) /**< DAT9���Ź����ʹ�� */

#define ADC_EOS0_IRQ_EN          ((uint16_t)0x01)     /**< ��һ��ɨ������ж� */
#define ADC_EOS1_IRQ_EN          ((uint16_t)0x02)     /**< �ڶ���ɨ������ж� */
#define ADC_EOS2_IRQ_EN          ((uint16_t)0x04)     /**< ������ɨ������ж� */
#define ADC_EOS3_IRQ_EN          ((uint16_t)0x08)     /**< ���Ķ�ɨ������ж� */
#define ADC_CONFLICT_IRQ_EN      ((uint16_t)0x10)     /**< ���������ͻ */
#define ADC_HERR_IRQ_EN          ((uint16_t)0x20)     /**< Ӳ��������ͻ */
#define ADC_DAT0_OV_IRQ_EN       ((uint16_t)0x40)     /**< ����ֵ�ж� */

#define ADC_EOS0_DMA_EN          ((uint16_t)0x100)      /**< ��һ��ɨ�����DMA����ʹ�� */
#define ADC_EOS1_DMA_EN          ((uint16_t)0x200)      /**< �ڶ���ɨ�����DMA����ʹ�� */
#define ADC_EOS2_DMA_EN          ((uint16_t)0x400)      /**< ������ɨ�����DMA����ʹ�� */
#define ADC_EOS3_DMA_EN          ((uint16_t)0x800)      /**< ���Ķ�ɨ�����DMA����ʹ�� */
#define ADC_CONFLICT_DMA_EN      ((uint16_t)0x1000)     /**< ���������ͻDMA����ʹ�� */
#define ADC_HERR_DMA_EN          ((uint16_t)0x2000)     /**< Ӳ��������ͻDMA����ʹ�� */
#define ADC_DAT0_OV_DMA_EN       ((uint16_t)0x4000)     /**< ����ֵDMA����ʹ�� */

#define ADC_ALL_IRQ_IF           ((uint16_t)0x7f)     /**< ADCȫ���жϱ�־λ���������ڳ�ʼ�� */
#define ADC_DAT0_OV_IRQ_IF       ((uint16_t)0x40)     /**< ����ֵ�ж� */
#define ADC_CONFLICT_IRQ_IF      ((uint16_t)0x20)     /**< Ӳ��������ͻ��־ */
#define ADC_HERR_IRQ_IF          ((uint16_t)0x10)     /**< ���������ͻ��־ */
#define ADC_EOS3_IRQ_IF          ((uint16_t)0x08)     /**< ���Ķ�ɨ������жϱ�־ */
#define ADC_EOS2_IRQ_IF          ((uint16_t)0x04)     /**< ������ɨ������жϱ�־*/
#define ADC_EOS1_IRQ_IF          ((uint16_t)0x02)     /**< �ڶ���ɨ������жϱ�־ */
#define ADC_EOS0_IRQ_IF          ((uint16_t)0x01)     /**< ��һ��ɨ������жϱ�־ */

#define ADC_LEFT_ALIGN           ((uint16_t)0x0000)   /**< ADC������������ */
#define ADC_RIGHT_ALIGN          ((uint16_t)0x0001)   /**< ADC��������Ҷ��� */

#define ADC_DAT0_HTH             ((uint16_t)0x0001)   /**< ADC_DAT0_TH��Ϊ����ֵ */
#define ADC_DAT0_LTH             ((uint16_t)0x0000)   /**< ADC_DAT0_TH��Ϊ����ֵ */

#define ADC_MCPWM_SEL            ((uint16_t)0x0000)   /**< MCPWM ����ADC���� */
#define ADC_UTIMER_SEL           ((uint16_t)0x0001)   /**< UTIMER����ADC���� */

#define ADC_1SEG_TRG             ((uint16_t)0x00)  /**< ADC���õ���ģʽ */
#define ADC_2SEG_TRG             ((uint16_t)0x01)  /**< ADC����2��ģʽ */
#define ADC_4SEG_TRG             ((uint16_t)0x03)  /**< ADC����4��ģʽ */

#define ADC_CHANNEL_0            ((uint16_t)0x00)  /**< ADCͨ��0  OPA0_OUT*/
#define ADC_CHANNEL_1            ((uint16_t)0x01)  /**< ADCͨ��1  ADC_CH1*/
#define ADC_CHANNEL_2            ((uint16_t)0x02)  /**< ADCͨ��2  ADC_CH2*/
#define ADC_CHANNEL_3            ((uint16_t)0x03)  /**< ADCͨ��3  ADC_CH3*/
#define ADC_CHANNEL_4            ((uint16_t)0x04)  /**< ADCͨ��4  ADC_CH4*/
#define ADC_CHANNEL_5            ((uint16_t)0x05)  /**< ADCͨ��5  ADC_CH5*/
#define ADC_CHANNEL_6            ((uint16_t)0x06)  /**< ADCͨ��6  ADC_CH6*/
#define ADC_CHANNEL_7            ((uint16_t)0x07)  /**< ADCͨ��7  ADC_CH7*/
#define ADC_CHANNEL_8            ((uint16_t)0x08)  /**< ADCͨ��8  ADC_CH8/OPA1_OUT*/
#define ADC_CHANNEL_9            ((uint16_t)0x09)  /**< ADCͨ��9  ADC_CH9*/
#define ADC_CHANNEL_10           ((uint16_t)0x0a)  /**< ADCͨ��10 ADC_CH10*/
#define ADC_CHANNEL_11           ((uint16_t)0x0b)  /**< ADCͨ��11 �¶ȴ�����*/
#define ADC_CHANNEL_12           ((uint16_t)0x0c)  /**< ADCͨ��12 �ڲ���*/
#define ADC_CHANNEL_13           ((uint16_t)0x0d)  /**< ADCͨ��13 2.4V��׼Դ*/

#define ADC_HARDWARE_T0_TRG      ((uint16_t)0x01) /**< ADC����Ӳ��T0�¼����� */
#define ADC_HARDWARE_T1_TRG      ((uint16_t)0x02) /**< ADC����Ӳ��T1�¼����� */
#define ADC_HARDWARE_T2_TRG      ((uint16_t)0x04) /**< ADC����Ӳ��T2�¼����� */
#define ADC_HARDWARE_T3_TRG      ((uint16_t)0x08) /**< ADC����Ӳ��T3�¼����� */


/** ADC�����ź���Դ�Ĵ������ */
typedef enum {
  CHN0 = 0, /**< ��0��1��2��3�β����źŶ�Ӧ�ź���Դ�Ĵ������*/
  CHN1,     /**< ��4��5��6��7�β����źŶ�Ӧ�ź���Դ�Ĵ������*/
  CHN2,     /**< ��8��9�β����źŶ�Ӧ�ź���Դ�Ĵ������*/
  } CHNx;

/** ADC���ݼĴ������ */
typedef enum {
  DAT0 = 0,  /**< ��0�β����źŶ�Ӧ����Ĵ������*/
  DAT1,      /**< ��1�β����źŶ�Ӧ����Ĵ������*/
  DAT2,      /**< ��2�β����źŶ�Ӧ����Ĵ������*/
  DAT3,      /**< ��3�β����źŶ�Ӧ����Ĵ������*/
  DAT4,      /**< ��4�β����źŶ�Ӧ����Ĵ������*/
  DAT5,      /**< ��5�β����źŶ�Ӧ����Ĵ������*/
  DAT6,      /**< ��6�β����źŶ�Ӧ����Ĵ������*/
  DAT7,      /**< ��7�β����źŶ�Ӧ����Ĵ������*/
  DAT8,      /**< ��8�β����źŶ�Ӧ����Ĵ������*/
  DAT9,      /**< ��9�β����źŶ�Ӧ����Ĵ������*/
} DATx;

void ADC_Init(ADC_TypeDef *ADCx, ADC_InitTypeDef *ADC_InitStruct);
void ADC_StructInit(ADC_InitTypeDef *ADC_InitStruct);
void ADC_ClearIRQFlag(ADC_TypeDef* ADCx, uint16_t INT_flag);
u16 ADC_GetIRQFlag(ADC_TypeDef* ADCx, uint16_t INT_flag);
void ADC_ChannelConfig(ADC_TypeDef* ADCx,CHNx CHNum, u16 Ch_n0 ,u16 Ch_n1, u16 Ch_n2 ,u16 Ch_n3);
s16 ADC_GetConversionValue(DATx DATNum);
void ADC_SoftTrgEN(ADC_TypeDef* ADCx, FuncState state);
#endif /*_CONNIE_ADC_H_ */

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
