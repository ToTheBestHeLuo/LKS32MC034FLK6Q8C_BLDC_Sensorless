/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief �ļ����ƣ� lks32mc03x_MCPWM.h\n
 * �ļ���ʶ�� �� \n
 * ����ժҪ�� mcpwm����ͷ�ļ� \n
 * ����˵���� �� \n
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��10��14�� <td>1.0       <td>HMG     <td>����
 * </table>
 */

#ifndef __LKS32MC03x_MCPWM_H
#define __LKS32MC03x_MCPWM_H

/* Includes ------------------------------------------------------------------*/
#include "lks32mc03x_lib.h"
/** 
 *@brief MCPWM�Ĵ����ṹ����
 */
typedef struct
{
  __IO u32 PWM_TH00;    /**< MCPWM CH0_P �Ƚ�����ֵ�Ĵ��� */
  __IO u32 PWM_TH01;    /**< MCPWM CH0_N �Ƚ�����ֵ�Ĵ��� */
  __IO u32 PWM_TH10;    /**< MCPWM CH1_P �Ƚ�����ֵ�Ĵ��� */
  __IO u32 PWM_TH11;    /**< MCPWM CH1_N �Ƚ�����ֵ�Ĵ��� */
  __IO u32 PWM_TH20;    /**< MCPWM CH2_P �Ƚ�����ֵ�Ĵ��� */
  __IO u32 PWM_TH21;    /**< MCPWM CH2_N �Ƚ�����ֵ�Ĵ��� */
  __IO u32 PWM_TH30;    /**< MCPWM CH3_P �Ƚ�����ֵ�Ĵ��� */
  __IO u32 PWM_TH31;    /**< MCPWM CH3_N �Ƚ�����ֵ�Ĵ��� */
  __IO u32 PWM_TMR0;    /**< ADC ������ʱ���Ƚ����� 0 �Ĵ��� */
  __IO u32 PWM_TMR1;    /**< ADC ������ʱ���Ƚ����� 1 �Ĵ��� */
  __IO u32 PWM_TMR2;    /**< ADC ������ʱ���Ƚ����� 2 �Ĵ��� */
  __IO u32 PWM_TMR3;    /**< ADC ������ʱ���Ƚ����� 3 �Ĵ��� */
  __IO u32 PWM_TH0;     /**< MCPWM ʱ�� 0 ����ֵ�Ĵ��� */
  __IO u32 PWM_TH1;     /**< MCPWM ʱ�� 1 ����ֵ�Ĵ��� */
  __IO u32 PWM_CNT0;    /**< MCPWM ʱ�� 0 �������Ĵ��� */
  __IO u32 PWM_CNT1;    /**< MCPWM ʱ�� 0 �������Ĵ��� */
  __IO u32 PWM_UPDATE;  /**< MCPWM �ֶ����ؿ��ƼĴ��� */
  __IO u32 PWM_FCNT;    /**< MCPWM FAIL ʱ�� CNT ֵ */
  __IO u32 PWM_EVT0;    /**< MCPWM ʱ�� 0 �ⲿ���� */
  __IO u32 PWM_EVT1;    /**< MCPWM ʱ�� 1 �ⲿ���� */
  __IO u32 PWM_DTH0;    /**< MCPWM CH0/1/2/3 Nͨ��������ȿ��ƼĴ��� */
  __IO u32 PWM_DTH1;    /**< MCPWM CH0/1/2/3 Pͨ��������ȿ��ƼĴ��� 0x54 */
  __IO u32 null0;       /**< ���� 0x58 */
  __IO u32 null1;       /**< ���� 0x5C */
  __IO u32 null2;       /**< ���� 0x60 */
  __IO u32 null3;       /**< ���� 0x64 */
  __IO u32 null4;       /**< ���� 0x68 */
  __IO u32 null5;       /**< ���� 0x6C */
  __IO u32 PWM_FLT;     /**< MCPWM �˲�ʱ�ӷ�Ƶ�Ĵ��� */
  __IO u32 PWM_SDCFG;   /**< MCPWM �������üĴ��� */
  __IO u32 PWM_AUEN;    /**< MCPWM �Զ�����ʹ�ܼĴ��� */
  __IO u32 PWM_TCLK;    /**< MCPWM ʱ�ӷ�Ƶ���ƼĴ��� */
  __IO u32 PWM_IE0;     /**< MCPWM ʱ�� 0 �жϿ��ƼĴ��� */
  __IO u32 PWM_IF0;     /**< MCPWM ʱ�� 0 �жϱ�־λ�Ĵ��� */
  __IO u32 PWM_IE1;     /**< MCPWM ʱ�� 1 �жϿ��ƼĴ��� */
  __IO u32 PWM_IF1;     /**< MCPWM ʱ�� 1 �жϱ�־λ�Ĵ��� */
  __IO u32 PWM_EIE;     /**< MCPWM �쳣�жϿ��ƼĴ��� 0x90*/
  __IO u32 PWM_EIF;     /**< MCPWM �쳣�жϱ�־λ�Ĵ��� 0x94*/
  __IO u32 PWM_RE;      /**< MCPWM DMA ������ƼĴ��� */
  __IO u32 PWM_PP;      /**< MCPWM ����ģʽʹ�ܼĴ��� */
  __IO u32 PWM_IO01;    /**< MCPWM CH0 CH1 IO ���ƼĴ��� */
  __IO u32 PWM_IO23;    /**< MCPWM CH2 CH3 IO ���ƼĴ��� */
  __IO u32 PWM_FAIL012; /**< MCPWM CH0 CH1 CH2 ��·���ƼĴ��� */
  __IO u32 PWM_FAIL3;   /**< MCPWM CH3 ��·���ƼĴ��� */
  __IO u32 PWM_PRT;     /**< MCPWM �����Ĵ��� */
	__IO u32 PWM_SWAP;    /**< MCPWM ͨ����ӳ��Ĵ��� */
  __IO u32 PWM_CHMSK;   /**< MCPWM ͨ������λ�Ĵ��� */
} MCPWM_REG_TypeDef;

/**
 * MCPWM�ṹ�����ַ����
 */
#ifndef MCPWM0
#define MCPWM0   ((MCPWM_REG_TypeDef *) MCPWM_BASE)
#endif

/** 
 *@brief MCPWM��ʼ���ṹ��������ʼ��ʱ�붨��þ��������������ַ������
 */
typedef struct
{
  u16 TimeBase0_PERIOD;       /**< ʱ��0��������*/
  u16 TimeBase1_PERIOD;       /**< ʱ��1��������*/
  u8 CLK_DIV;                 /**< MCPWM ��Ƶϵ�� */
  u8 MCLK_EN;                 /**< MCPWM ʱ��ʹ�ܿ��� */
  u8 MCPWM_Cnt0_EN;           /**< MCPWM ʱ��0��������ʹ�ܿ��� */
  u8 MCPWM_Cnt1_EN;           /**< MCPWM ʱ��1��������ʹ�ܿ��� */
  u8 GPIO_BKIN_Filter;        /**< GPIO�����˲�ʱ������1-256 */
  u8 CMP_BKIN_Filter;         /**< �Ƚ���CMP�����˲�ʱ������1-256 */

  u8 TMR2_TimeBase_Sel;       /**< TMR2 �Ƚ����޼Ĵ��� ʱ��ѡ�� 0:ʱ��0 | 1:ʱ��1 */
  u8 TMR3_TimeBase_Sel;       /**< TMR3 �Ƚ����޼Ĵ��� ʱ��ѡ�� 1:ʱ��0 | 1:ʱ��1 */

  u8 TimeBase0_Trig_Enable;   /**< ʱ��0 �ⲿ����ʹ�� */
  u8 TimeBase1_Trig_Enable;   /**< ʱ��1 �ⲿ����ʹ��*/

  u16 TimeBase_TrigEvt0;      /**< ʱ��0 �ⲿ�����¼�ѡ�� */
  u16 TimeBase_TrigEvt1;      /**< ʱ��1 �ⲿ�����¼�ѡ�� */

  s16 TimeBase0Init_CNT;      /**< ʱ��0 ��������ʼֵ */
  s16 TimeBase1Init_CNT;      /**< ʱ��1 ��������ʼֵ */

  u16 MCPWM_WorkModeCH0;      /**< MCPWM CH0����ģʽ�����ض���/���Ķ��� */
  u16 MCPWM_WorkModeCH1;      /**< MCPWM CH0����ģʽ�����ض���/���Ķ��� */
  u16 MCPWM_WorkModeCH2;      /**< MCPWM CH0����ģʽ�����ض���/���Ķ��� */
  u16 MCPWM_WorkModeCH3;      /**< MCPWM CH0����ģʽ�����ض���/���Ķ��� */
                         
  u16 TriggerPoint0;          /**< PWM����ADC�¼�0��ʱ������� */
  u16 TriggerPoint1;          /**< PWM����ADC�¼�1��ʱ������� */
  u16 TriggerPoint2;          /**< PWM����ADC�¼�2��ʱ������� */
  u16 TriggerPoint3;          /**< PWM����ADC�¼�3��ʱ������� */
                         
  u16 DeadTimeCH0123N;        /**< CH0123N����ʱ�����á�*/
  u16 DeadTimeCH0123P;        /**< CH0123P����ʱ�����á�*/
                         
  u8 CH0N_Polarity_INV;       /**< CH0N�������ȡ����0:���������1:ȡ����� */
  u8 CH0P_Polarity_INV;       /**< CH0P�������ȡ����0:���������1:ȡ����� */
  u8 CH1N_Polarity_INV;       /**< CH1N�������ȡ����0:���������1:ȡ����� */
  u8 CH1P_Polarity_INV;       /**< CH1P�������ȡ����0:���������1:ȡ����� */
  u8 CH2N_Polarity_INV;       /**< CH2N�������ȡ����0:���������1:ȡ����� */
  u8 CH2P_Polarity_INV;       /**< CH2P�������ȡ����0:���������1:ȡ����� */
  u8 CH3N_Polarity_INV;       /**< CH3N�������ȡ����0:���������1:ȡ����� */
  u8 CH3P_Polarity_INV;       /**< CH3P�������ȡ����0:���������1:ȡ����� */

  u8 CH0P_SCTRLP;             /**< ��CH0_PS = 1ʱ�������CH0_Pͨ����ֵ*/
  u8 CH0N_SCTRLN;             /**< ��CH0_NS = 1ʱ�������CH0_Nͨ����ֵ*/
  u8 CH1P_SCTRLP;             /**< ��CH1_PS = 1ʱ�������CH1_Pͨ����ֵ*/
  u8 CH1N_SCTRLN;             /**< ��CH1_NS = 1ʱ�������CH1_Nͨ����ֵ*/
  u8 CH2P_SCTRLP;             /**< ��CH2_PS = 1ʱ�������CH2_Pͨ����ֵ*/
  u8 CH2N_SCTRLN;             /**< ��CH2_NS = 1ʱ�������CH2_Nͨ����ֵ*/
  u8 CH3P_SCTRLP;             /**< ��CH3_PS = 1ʱ�������CH3_Pͨ����ֵ*/
  u8 CH3N_SCTRLN;             /**< ��CH3_NS = 1ʱ�������CH3_PNͨ����ֵ*/
   
	u8 CH0_PS;                  /**< CH0_P�ź���Դ��1������CH0_SCTRLP��0������MCPWMʵ�����м�����*/
	u8 CH0_NS;                  /**< CH0_N�ź���Դ��1������CH0_SCTRLN��0������MCPWMʵ�����м�����*/
	u8 CH1_PS;                  /**< CH1_P�ź���Դ��1������CH1_SCTRLP��0������MCPWMʵ�����м�����*/
	u8 CH1_NS;                  /**< CH1_N�ź���Դ��1������CH1_SCTRLN��0������MCPWMʵ�����м�����*/
	u8 CH2_PS;                  /**< CH2_P�ź���Դ��1������CH2_SCTRLP��0������MCPWMʵ�����м�����*/
	u8 CH2_NS;                  /**< CH2_N�ź���Դ��1������CH2_SCTRLN��0������MCPWMʵ�����м�����*/
	u8 CH3_PS;                  /**< CH3_P�ź���Դ��1������CH3_SCTRLP��0������MCPWMʵ�����м�����*/
	u8 CH3_NS;                  /**< CH3_N�ź���Դ��1������CH3_SCTRLN��0������MCPWMʵ�����м�����*/
	
	u8 Switch_CH0N_CH0P;        /**< ����CH0N, CH0P�ź����ʹ�ܿ��� */
  u8 Switch_CH1N_CH1P;        /**< ����CH1N, CH1P�ź����ʹ�ܿ��� */
  u8 Switch_CH2N_CH2P;        /**< ����CH2N, CH2P�ź����ʹ�ܿ��� */
  u8 Switch_CH3N_CH3P;        /**< ����CH3N, CH3P�ź����ʹ�ܿ��� */
	
  u8 MCPWM_UpdateT0Interval; /**< MCPWM T0�¼����¼�� */
  u8 MCPWM_UpdateT1Interval; /**< MCPWM T1�¼����¼�� */
  u8 MCPWM_Base0T0_UpdateEN; /**< MCPWM ʱ��0 T0�¼�����ʹ�� */
  u8 MCPWM_Base0T1_UpdateEN; /**< MCPWM ʱ��0 T1�¼�����ʹ�� */
  u8 MCPWM_Base1T0_UpdateEN; /**< MCPWM ʱ��1 T0�¼�����ʹ�� */
  u8 MCPWM_Base1T1_UpdateEN; /**< MCPWM ʱ��1 T1�¼�����ʹ�� */
  u8 MCPWM_Auto0_ERR_EN;     /**< MCPWM ʱ��0�����¼��Ƿ��Զ���MOE, ʹ�ܿ��� */
  u8 MCPWM_Auto1_ERR_EN;     /**< MCPWM ʱ��1�����¼��Ƿ��Զ���MOE, ʹ�ܿ��� */

  u8 FAIL0_INPUT_EN;         /**< FAIL0 ���빦��ʹ�� */
  u8 FAIL1_INPUT_EN;         /**< FAIL1 ���빦��ʹ�� */
  u8 FAIL0_Signal_Sel;       /**< FAIL0 �ź�ѡ�񣬱Ƚ���0��GPIO */
  u8 FAIL1_Signal_Sel;       /**< FAIL1 �ź�ѡ�񣬱Ƚ���0��GPIO */
  u8 FAIL0_Polarity;         /**< FAIL0 �źż������ã�����Ч�����Ч */
  u8 FAIL1_Polarity;         /**< FAIL1 �źż������ã�����Ч�����Ч */
  u8 DebugMode_PWM_out;      /**< Debugʱ��MCU����Halt, MCPWM�ź��Ƿ�������� */
  u8 FAIL2_INPUT_EN;         /**< FAIL2 ���빦��ʹ�� */
  u8 FAIL3_INPUT_EN;         /**< FAIL3 ���빦��ʹ�� */
  u8 FAIL2_Signal_Sel;       /**< FAIL2 �ź�ѡ�񣬱Ƚ���0��GPIO */
  u8 FAIL3_Signal_Sel;       /**< FAIL3 �ź�ѡ�񣬱Ƚ���0��GPIO */
  u8 FAIL2_Polarity;         /**< FAIL2 �źż������ã�����Ч�����Ч */
  u8 FAIL3_Polarity;         /**< FAIL3 �źż������ã�����Ч�����Ч */

  u8 CH0P_default_output;    /**< CH0P MOEΪ0ʱ����FAIL�¼�ʱ��Ĭ�ϵ�ƽ��� */
  u8 CH0N_default_output;    /**< CH0N MOEΪ0ʱ����FAIL�¼�ʱ��Ĭ�ϵ�ƽ��� */
  u8 CH1P_default_output;    /**< CH1P MOEΪ0ʱ����FAIL�¼�ʱ��Ĭ�ϵ�ƽ��� */
  u8 CH1N_default_output;    /**< CH1N MOEΪ0ʱ����FAIL�¼�ʱ��Ĭ�ϵ�ƽ��� */
  u8 CH2P_default_output;    /**< CH2P MOEΪ0ʱ����FAIL�¼�ʱ��Ĭ�ϵ�ƽ��� */
  u8 CH2N_default_output;    /**< CH2N MOEΪ0ʱ����FAIL�¼�ʱ��Ĭ�ϵ�ƽ��� */
  u8 CH3P_default_output;    /**< CH3P MOEΪ0ʱ����FAIL�¼�ʱ��Ĭ�ϵ�ƽ��� */
  u8 CH3N_default_output;    /**< CH3N MOEΪ0ʱ����FAIL�¼�ʱ��Ĭ�ϵ�ƽ��� */
													   
  u8 CNT0_T0_Update_INT_EN;  /**< ʱ��0 T0�����¼��ж�ʹ�� */
  u8 CNT0_T1_Update_INT_EN;  /**< ʱ��0 T1�����¼��ж�ʹ�� */
	u8 CNT0_Update_TH00_EN;    /**< MCPWM ʵ������ϵͳ�м������ļ���ֵ����MCPWM_TH00�ж�Դʹ��*/
	u8 CNT0_Update_TH01_EN;    /**< MCPWM ʵ������ϵͳ�м������ļ���ֵ����MCPWM_TH01�ж�Դʹ��*/
	u8 CNT0_Update_TH10_EN;    /**< MCPWM ʵ������ϵͳ�м������ļ���ֵ����MCPWM_TH10�ж�Դʹ��*/
	u8 CNT0_Update_TH11_EN;    /**< MCPWM ʵ������ϵͳ�м������ļ���ֵ����MCPWM_TH11�ж�Դʹ��*/
	u8 CNT0_Update_TH20_EN;    /**< MCPWM ʵ������ϵͳ�м������ļ���ֵ����MCPWM_TH20�ж�Դʹ��*/
	u8 CNT0_Update_TH21_EN;    /**< MCPWM ʵ������ϵͳ�м������ļ���ֵ����MCPWM_TH21�ж�Դʹ��*/
	u8 CNT0_Update_TH30_EN;    /**< MCPWM ʵ������ϵͳ�м������ļ���ֵ����MCPWM_TH30�ж�Դʹ��*/
	u8 CNT0_Update_TH31_EN;    /**< MCPWM ʵ������ϵͳ�м������ļ���ֵ����MCPWM_TH31�ж�Դʹ��*/		
  u8 CNT0_TMR0_Match_INT_EN; /**< ʱ��0 TMR0�����¼�ƥ���¼��ж�ʹ�� */
  u8 CNT0_TMR1_Match_INT_EN; /**< ʱ��0 TMR1�����¼�ƥ���¼��ж�ʹ�� */
	u8 CNT0_TMR2_Match_INT_EN; /**< ʱ��0 TMR2�����¼�ƥ���¼��ж�ʹ�� */
  u8 CNT0_TMR3_Match_INT_EN; /**< ʱ��0 TMR3�����¼�ƥ���¼��ж�ʹ�� */
  u8 CNT0_Update_EN;         /**< �Ĵ������µ� MCPWM ʵ������ϵͳ���ж�Դʹ�� */

  u8 CNT1_T0_Update_INT_EN;  /**< ʱ��1 T0�����¼��ж�ʹ�� */
  u8 CNT1_T1_Update_INT_EN;  /**< ʱ��1 T1�����¼��ж�ʹ�� */
	u8 CNT1_Update_TH30_EN;    /**< MCPWM ʵ������ϵͳ�м������ļ���ֵ����MCPWM_TH30�ж�Դʹ��*/
	u8 CNT1_Update_TH31_EN;    /**< MCPWM ʵ������ϵͳ�м������ļ���ֵ����MCPWM_TH31�ж�Դʹ��*/		
	u8 CNT1_TMR2_Match_INT_EN; /**< ʱ��1 TMR2�����¼�ƥ���¼��ж�ʹ�� */
  u8 CNT1_TMR3_Match_INT_EN; /**< ʱ��1 TMR3�����¼�ƥ���¼��ж�ʹ�� */
  u8 CNT1_Update_EN;         /**< �Ĵ������µ� MCPWM ʵ������ϵͳ���ж�Դʹ�� */

  u8 TMR0_DMA_RE;            /**< MCPWM����������TMR0��DMA����ʹ��*/
  u8 TMR1_DMA_RE;            /**< MCPWM����������TMR1��DMA����ʹ��*/
  u8 TMR2_DMA_RE;            /**< MCPWM����������TMR2��DMA����ʹ��*/
  u8 TMR3_DMA_RE;            /**< MCPWM����������TMR3��DMA����ʹ��*/
  u8 TR0_T0_DMA_RE;          /**< ʱ��0 T0�¼�DMA����ʹ��*/
  u8 TR0_T1_DMA_RE;          /**< ʱ��0 T1�¼�DMA����ʹ��*/
  u8 TR1_T0_DMA_RE;          /**< ʱ��1 T0�¼�DMA����ʹ��*/
  u8 TR1_T1_DMA_RE;          /**< ʱ��1 T1�¼�DMA����ʹ��*/

  u8 FAIL0_INT_EN;           /**< FAIL0�¼��ж�ʹ�� (MCPWM_CH0-CH2��ͣ�¼�)*/
  u8 FAIL1_INT_EN;           /**< FAIL1�¼��ж�ʹ�� (MCPWM_CH0-CH2��ͣ�¼�)*/
  u8 FAIL2_INT_EN;           /**< FAIL2�¼��ж�ʹ�� (MCPWM_CH3��ͣ�¼�)*/
  u8 FAIL3_INT_EN;           /**< FAIL3�¼��ж�ʹ�� (MCPWM_CH3��ͣ�¼�)*/

  u16 AUEN;                  /**< �Զ�����ʹ�ܼĴ��� */
	
	u8  IO_PPE;                /**< ����ģʽʹ���ź� */

} MCPWM_InitTypeDef;

/* MCPWM_FAIL012 MOE */
#define MCPWM_MOE_ENABLE_MASK ((u16)0x0040)   /**< ��MOEλMASKλ */
#define MCPWM_MOE_DISABLE_MASK ((u16)~0x0040) /**< ��MOEλMASKλ */

/* MCPWM_AUEN  MCPWM �Զ�����ʹ�ܼĴ��� */
#define TH00_AUEN BIT0  /**< MCPWM_TH00 �Զ�����ʹ�� */
#define TH01_AUEN BIT1  /**< MCPWM_TH01 �Զ�����ʹ�� */ 
#define TH10_AUEN BIT2  /**< MCPWM_TH10 �Զ�����ʹ�� */
#define TH11_AUEN BIT3  /**< MCPWM_TH11 �Զ�����ʹ�� */
#define TH20_AUEN BIT4  /**< MCPWM_TH20 �Զ�����ʹ�� */
#define TH21_AUEN BIT5  /**< MCPWM_TH21 �Զ�����ʹ�� */
#define TH30_AUEN BIT6  /**< MCPWM_TH30 �Զ�����ʹ�� */
#define TH31_AUEN BIT7  /**< MCPWM_TH31 �Զ�����ʹ�� */
#define TMR0_AUEN BIT8  /**< MCPWM_TMR0 �Զ�����ʹ�� */
#define TMR1_AUEN BIT9  /**< MCPWM_TMR1 �Զ�����ʹ�� */
#define TMR2_AUEN BIT10 /**< MCPWM_TMR2 �Զ�����ʹ�� */
#define TMR3_AUEN BIT11 /**< MCPWM_TMR3 �Զ�����ʹ�� */
#define TH0_AUEN  BIT12 /**< MCPWM_TH0 �Զ�����ʹ�� */
#define TH1_AUEN  BIT13 /**< MCPWM_TH1 �Զ�����ʹ�� */
#define CNT0_AUEN BIT14 /**< MCPWM_CNT0 �Զ�����ʹ�� */
#define CNT1_AUEN BIT15 /**< MCPWM_CNT1 �Զ�����ʹ�� */

/* MCPWM_AUEN  MCPWM �Զ�����ʹ�ܼĴ��� */
#define CENTRAL_PWM_MODE 0 /**< ���Ķ���PWMģʽ */
#define EDGE_PWM_MODE 1    /**< ���ض���PWMģʽ */

/* MCPWM_FAIL012[8:13] MCPWM_FAIL3[8:9] ͨ��Ĭ�������ƽ */
#define HIGH_LEVEL 1 /**< MCPWMͨ������״̬����ߵ�ƽ */
#define LOW_LEVEL 0  /**< MCPWMͨ������״̬����͵�ƽ */

/* MCPWM_IO01��MCPWM_IO23 ��������CHxPP CHxNP */
#define HIGH_LEVEL_VALID 0 /**< FAIL����ѡ�� �ߵ�ƽ��Ч */
#define LOW_LEVEL_VALID 1  /**< FAIL����ѡ�� �͵�ƽ��Ч */

/* MCPWM_FAIL012��MCPWM_FAIL3 failx�ź���Դ */
#define FAIL_SEL_CMP 1 /**< Fail�¼���Դ�Ƚ��� */
#define FAIL_SEL_IO 0  /**< Fail�¼���ԴIO */




/* MCPWM_PP  MCPWM ����ģʽʹ�ܼĴ��� */
#define  MCPWM_IO0_PPEN  BIT0         /**< IO0 ����ģʽʹ���ź� */
#define  MCPWM_IO1_PPEN  BIT1         /**< IO1 ����ģʽʹ���ź� */
#define  MCPWM_IO2_PPEN  BIT2         /**< IO2 ����ģʽʹ���ź� */
#define  MCPWM_IO3_PPEN  BIT3         /**< IO3 ����ģʽʹ���ź� */


#define PWM_Clk_Div1     0x00         /**<MCPWM����Ƶ��48M*/
#define PWM_Clk_Div2     0x01         /**<MCPWM����Ƶ��24M*/
#define PWM_Clk_Div4     0x02         /**<MCPWM����Ƶ��12M*/
#define PWM_Clk_Div8     0x03         /**<MCPWM����Ƶ��6M*/  


#define MCPWM_UPDATE_REG()  \
  {                         \
    MCPWM_PRT = 0x0000DEAD; \
    MCPWM_UPDATE = 0x00ff;  \
    MCPWM_PRT = 0x0000CAFE; \
  }/**< PWMͨ������ */
	
/** 
 *@brief MCPWM�Ƚ����޼Ĵ������½ṹ��
 */
typedef struct
{
	s16 th00;/**< ��ӦMCPWM_TH00 */
	s16 th01;/**< ��ӦMCPWM_TH01 */
	s16 th10;/**< ��ӦMCPWM_TH10 */
	s16 th11;/**< ��ӦMCPWM_TH11 */
	s16 th20;/**< ��ӦMCPWM_TH20 */
	s16 th21;/**< ��ӦMCPWM_TH21 */
	s16 th30;/**< ��ӦMCPWM_TH30 */
	s16 th31;/**< ��ӦMCPWM_TH31 */
}strPWM_DutyCycleDef;

/** 
 *@brief MCPWM ʱ����ѡ�� 
 */
typedef enum 
{  
  CNT0 = 0, 
  CNT1 = 1,
}CNT_Num;

/* MCPWMʱ��0��Ӧ���ж� */
#define CNT0_MCPWM_T0_IRQ_EN        BIT0  /**< ����������ֵ�ص�MCPWM_TH�ж�ʹ�� */
#define CNT0_MCPWM_T1_IRQ_EN        BIT1  /**< ����������ֵ�ص�0�ж�ʹ�� */
#define CNT0_MCPWM_TH00_IRQ_EN      BIT2  /**< ����������ֵ�ص�MCPWM_TH00�ж�ʹ�� */
#define CNT0_MCPWM_TH01_IRQ_EN      BIT3  /**< ����������ֵ�ص�MCPWM_TH01�ж�ʹ�� */
#define CNT0_MCPWM_TH10_IRQ_EN      BIT4  /**< ����������ֵ�ص�MCPWM_TH10�ж�ʹ�� */
#define CNT0_MCPWM_TH11_IRQ_EN      BIT5  /**< ����������ֵ�ص�MCPWM_TH11�ж�ʹ�� */
#define CNT0_MCPWM_TH20_IRQ_EN      BIT6  /**< ����������ֵ�ص�MCPWM_TH20�ж�ʹ�� */
#define CNT0_MCPWM_TH21_IRQ_EN      BIT7  /**< ����������ֵ�ص�MCPWM_TH21�ж�ʹ�� */
#define CNT0_MCPWM_TH30_IRQ_EN      BIT8  /**< ����������ֵ�ص�MCPWM_TH30�ж�ʹ�� */
#define CNT0_MCPWM_TH31_IRQ_EN      BIT9  /**< ����������ֵ�ص�MCPWM_TH31�ж�ʹ�� */
#define CNT0_MCPWM_TMR0_IRQ_EN      BIT10 /**< ����������ֵ�ص�MCPWM_TMR0�ж�ʹ�� */
#define CNT0_MCPWM_TMR1_IRQ_EN      BIT11 /**< ����������ֵ�ص�MCPWM_TMR1�ж�ʹ�� */
#define CNT0_MCPWM_TMR2_IRQ_EN      BIT12 /**< ����������ֵ�ص�MCPWM_TMR0�ж�ʹ�� */
#define CNT0_MCPWM_TMR3_IRQ_EN      BIT13 /**< ����������ֵ�ص�MCPWM_TMR1�ж�ʹ�� */
#define CNT0_MCPWM_SHADE_IRQ_EN     BIT14 /**< MCPWM_TH/MCPWM_TH00-MCPWM_TH31/\
MCPWM_TR0-MCPWM_TR3�ȼĴ������µ�MCPWMʵ������ϵͳ�ж�ʹ�� */

/* MCPWMʱ��1��Ӧ���ж� */
#define CNT1_MCPWM_T0_IRQ_EN        BIT0  /**< ����������ֵ�ص�MCPWM_TH�ж�ʹ�� */
#define CNT1_MCPWM_T1_IRQ_EN        BIT1  /**< ����������ֵ�ص�0�ж�ʹ�� */
#define CNT1_MCPWM_TH00_IRQ_EN      BIT2  /**< ����������ֵ�ص�MCPWM_TH00�ж�ʹ�� */
#define CNT1_MCPWM_TH01_IRQ_EN      BIT3  /**< ����������ֵ�ص�MCPWM_TH01�ж�ʹ�� */
#define CNT1_MCPWM_TH10_IRQ_EN      BIT4  /**< ����������ֵ�ص�MCPWM_TH10�ж�ʹ�� */
#define CNT1_MCPWM_TH11_IRQ_EN      BIT5  /**< ����������ֵ�ص�MCPWM_TH11�ж�ʹ�� */
#define CNT1_MCPWM_TH20_IRQ_EN      BIT6  /**< ����������ֵ�ص�MCPWM_TH20�ж�ʹ�� */
#define CNT1_MCPWM_TH21_IRQ_EN      BIT7  /**< ����������ֵ�ص�MCPWM_TH21�ж�ʹ�� */
#define CNT1_MCPWM_TH30_IRQ_EN      BIT8  /**< ����������ֵ�ص�MCPWM_TH30�ж�ʹ�� */
#define CNT1_MCPWM_TH31_IRQ_EN      BIT9  /**< ����������ֵ�ص�MCPWM_TH31�ж�ʹ�� */
#define CNT1_MCPWM_TMR0_IRQ_EN      BIT10 /**< ����������ֵ�ص�MCPWM_TMR0�ж�ʹ�� */
#define CNT1_MCPWM_TMR1_IRQ_EN      BIT11 /**< ����������ֵ�ص�MCPWM_TMR1�ж�ʹ�� */
#define CNT1_MCPWM_TMR2_IRQ_EN      BIT12 /**< ����������ֵ�ص�MCPWM_TMR0�ж�ʹ�� */
#define CNT1_MCPWM_TMR3_IRQ_EN      BIT13 /**< ����������ֵ�ص�MCPWM_TMR1�ж�ʹ�� */
#define CNT1_MCPWM_SHADE_IRQ_EN     BIT14 /**< MCPWM_TH/MCPWM_TH00-MCPWM_TH31/\
MCPWM_TR0-MCPWM_TR3�ȼĴ������µ�MCPWMʵ������ϵͳ�ж�ʹ�� */

#define CNT0_MCPWM_FAIL0_IRQ_EN          BIT4     /**< MCPWM_FAIL0�ж�ʹ�� */
#define CNT0_MCPWM_FAIL1_IRQ_EN          BIT5     /**< MCPWM_FAIL1�ж�ʹ�� */
#define CNT1_MCPWM_FAIL2_IRQ_EN          BIT6     /**< MCPWM_FAIL2�ж�ʹ�� */
#define CNT1_MCPWM_FAIL3_IRQ_EN          BIT7     /**< MCPWM_FAIL3�ж�ʹ�� */

/* MCPWMʱ��0��Ӧ���жϱ�־λ */
#define CNT0_MCPWM_T0_IRQ_IF        BIT0  /**< ����������ֵ�ص�MCPWM_TH�жϱ�־λ */
#define CNT0_MCPWM_T1_IRQ_IF        BIT1  /**< ����������ֵ�ص�0�жϱ�־λ */
#define CNT0_MCPWM_TH00_IRQ_IF      BIT2  /**< ����������ֵ�ص�MCPWM_TH00�жϱ�־λ */
#define CNT0_MCPWM_TH01_IRQ_IF      BIT3  /**< ����������ֵ�ص�MCPWM_TH01�жϱ�־λ */
#define CNT0_MCPWM_TH10_IRQ_IF      BIT4  /**< ����������ֵ�ص�MCPWM_TH10�жϱ�־λ */
#define CNT0_MCPWM_TH11_IRQ_IF      BIT5  /**< ����������ֵ�ص�MCPWM_TH11�жϱ�־λ */
#define CNT0_MCPWM_TH20_IRQ_IF      BIT6  /**< ����������ֵ�ص�MCPWM_TH20�жϱ�־λ */
#define CNT0_MCPWM_TH21_IRQ_IF      BIT7  /**< ����������ֵ�ص�MCPWM_TH21�жϱ�־λ */
#define CNT0_MCPWM_TH30_IRQ_IF      BIT8  /**< ����������ֵ�ص�MCPWM_TH30�жϱ�־λ */
#define CNT0_MCPWM_TH31_IRQ_IF      BIT9  /**< ����������ֵ�ص�MCPWM_TH31�жϱ�־λ */
#define CNT0_MCPWM_TMR0_IRQ_IF      BIT10 /**< ����������ֵ�ص�MCPWM_TMR0�жϱ�־λ */
#define CNT0_MCPWM_TMR1_IRQ_IF      BIT11 /**< ����������ֵ�ص�MCPWM_TMR1�жϱ�־λ */
#define CNT0_MCPWM_TMR2_IRQ_IF      BIT12 /**< ����������ֵ�ص�MCPWM_TMR0�жϱ�־λ */
#define CNT0_MCPWM_TMR3_IRQ_IF      BIT13 /**< ����������ֵ�ص�MCPWM_TMR1�жϱ�־λ */
#define CNT0_MCPWM_SHADE_IRQ_IF     BIT14 /**< MCPWM_TH/MCPWM_TH00-MCPWM_TH31/\
MCPWM_TR0-MCPWM_TR3�ȼĴ������µ�MCPWMʵ������ϵͳ�ж�ʹ�� */

/* MCPWMʱ��1��Ӧ���жϱ�־λ */
#define CNT1_MCPWM_T0_IRQ_IF        BIT0  /**< ����������ֵ�ص�MCPWM_TH�жϱ�־λ */
#define CNT1_MCPWM_T1_IRQ_IF        BIT1  /**< ����������ֵ�ص�0�ж�ʹ�� */
#define CNT1_MCPWM_TH30_IRQ_IF      BIT8  /**< ����������ֵ�ص�MCPWM_TH30�жϱ�־λ */
#define CNT1_MCPWM_TH31_IRQ_IF      BIT9  /**< ����������ֵ�ص�MCPWM_TH31�жϱ�־λ */
#define CNT1_MCPWM_TMR2_IRQ_IF      BIT12 /**< ����������ֵ�ص�MCPWM_TMR0�жϱ�־λ */
#define CNT1_MCPWM_TMR3_IRQ_IF      BIT13 /**< ����������ֵ�ص�MCPWM_TMR1�жϱ�־λ */
#define CNT1_MCPWM_SHADE_IRQ_IF     BIT14 /**< MCPWM_TH/MCPWM_TH00-MCPWM_TH31/\
MCPWM_TR0-MCPWM_TR3�ȼĴ������µ�MCPWMʵ������ϵͳ�ж�ʹ�� */

/**< fail�жϱ�־λ����ͨ�жϱ�־λ��ͬһ������ʵ�ֶ������־����\
ʵ��fail0-fail3�¼���ӦMCPWM_EIF��BIT4-BIT7*/
#define CNT0_MCPWM_FAIL0_IRQ_IF          BIT19     /**< MCPWM_FAIL0�ж�ʹ�� */
#define CNT0_MCPWM_FAIL1_IRQ_IF          BIT20     /**< MCPWM_FAIL1�ж�ʹ�� */
#define CNT1_MCPWM_FAIL2_IRQ_IF          BIT21     /**< MCPWM_FAIL2�ж�ʹ�� */
#define CNT1_MCPWM_FAIL3_IRQ_IF          BIT22     /**< MCPWM_FAIL3�ж�ʹ�� */

void MCPWM_StructInit(MCPWM_InitTypeDef *MCPWM_InitStruct);
void MCPWM_Init(MCPWM_REG_TypeDef *MCPWMx, MCPWM_InitTypeDef *MCPWM_InitStruct);

void PWMOutputs(MCPWM_REG_TypeDef *MCPWMx, FuncState t_state);
void PWMOutputs_CH3(MCPWM_REG_TypeDef *MCPWMx, FuncState t_state);

void MCPWM_SwapFunction(void);
void MCPWM_Update(strPWM_DutyCycleDef *Duty);

u16 MCPWM_ReadIRQFlag(MCPWM_REG_TypeDef *MCPWMx, CNT_Num CNTx, uint32_t INT_flag);
void MCPWM_ClearIRQFlag(MCPWM_REG_TypeDef *MCPWMx, CNT_Num CNTx, uint32_t INT_flag);
#endif /*__CHANHOM_PWM_H */

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
