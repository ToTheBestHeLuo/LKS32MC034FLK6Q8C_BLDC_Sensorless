/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief �ļ����ƣ� lks32mc03x_tim.h\n
 * �ļ���ʶ�� �� \n
 * ����ժҪ�� TIM����ͷ�ļ� \n
 * ����˵���� �� \n
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��11��09�� <td>1.0     <td>YangZJ        <td>����
 * </table>
 */

#ifndef __LKS32MC03x_TIM_H
#define __LKS32MC03x_TIM_H

/* Includes ------------------------------------------------------------------*/
#include "lks32mc03x_lib.h"

/** 
 *@brief ��ʱ���Ĵ����ṹ����
 */
typedef struct
{
    __IO uint32_t CFG;        /**<��ʱ�����üĴ���*/
    __IO uint32_t TH;         /**<��ʱ���������޼Ĵ���*/
    __IO uint32_t CNT;        /**<��ʱ������ֵ�Ĵ���*/
    __IO uint32_t CMPT0;      /**<��ʱ���Ƚ�/����Ĵ��� 0*/
    __IO uint32_t CMPT1;      /**<��ʱ���Ƚ�/����Ĵ��� 1*/
    __IO uint32_t EVT;        /**<��ʱ���ⲿ�¼�ѡ��Ĵ���*/
    __IO uint32_t FLT;        /**<��ʱ���˲����ƼĴ���*/
    __IO uint32_t IE;         /**<��ʱ���ж�ʹ�ܼĴ���*/
    __IO uint32_t IF;         /**<��ʱ���жϱ�־�Ĵ���*/
} TIM_TimerTypeDef;


/**
 * TIMER0�ṹ�����ַ����
 */
#ifndef TIMER0
#define TIMER0         ((TIM_TimerTypeDef *) TIMER0_BASE)
#endif
/**
 * TIMER1�ṹ�����ַ����
 */
#ifndef TIMER1
#define TIMER1         ((TIM_TimerTypeDef *) TIMER1_BASE)
#endif


#define TIMER_OPMode_CAP ((uint32_t)0x0000001)    /**<����ģʽ,����ģʽ*/
#define TIMER_OPMode_CMP ((uint32_t)0x0000000)    /**<����ģʽ,�Ƚ�ģʽ*/

/* ��timerʱ��ΪMCLKʱ*/	
#define TIM_Clk_Div1        0x00   	  /**< Timer����Ƶ��48Mhz*/
#define TIM_Clk_Div2        0x01   	  /**< Timer����Ƶ��24Mhz*/
#define TIM_Clk_Div4        0x02   	  /**< Timer����Ƶ��12Mhz*/
#define TIM_Clk_Div8        0x03   	  /**< Timer����Ƶ��6Mhz*/
#define TIM_Clk_Div16       0x04  	  /**< Timer����Ƶ��3Mhz*/
#define TIM_Clk_Div32       0x05  	  /**< Timer����Ƶ��1.5Mhz*/
#define TIM_Clk_Div64       0x06  	  /**< Timer����Ƶ��750Khz*/
#define TIM_Clk_Div128      0x07 	  /**< Timer����Ƶ��375Khz*/

#define TIM_Clk_SRC_MCLK    0x00      /**< Timerʹ��оƬ�ڲ�ʱ��*/
#define TIM_Clk_SRC_Timer00 0x01      /**< Timerʹ���ⲿTimer0ͨ��0�����ź�*/
#define TIM_Clk_SRC_Timer01 0x02      /**< Timerʹ���ⲿTimer0ͨ��1�����ź�*/
#define TIM_Clk_SRC_Timer10 0x03      /**< Timerʹ���ⲿTimer1ͨ��0�����ź�*/
#define TIM_Clk_SRC_Timer11 0x04      /**< Timerʹ���ⲿTimer1ͨ��1�����ź�*/

#define TIM_SRC1_0          0x00      /**< Timer1���� ���ͨ��0*/
#define TIM_SRC1_1          0x01      /**< Timer1���� ���ͨ��1*/
#define TIM_SRC1_CMP0       0x02 	  /**< Timer1���� �Ƚ��� 0 �����*/
#define TIM_SRC1_CMP1       0x03 	  /**< Timer1���� �Ƚ��� 1 �����*/
#define TIM_SRC1_0XOR1      0x04	  /**< Timer1���� ͨ��0��ͨ��1�����*/

#define TIM_SRC0_0          0x00      /**< Timer0���� ���ͨ��0*/
#define TIM_SRC0_1          0x01      /**< Timer0���� ���ͨ��1*/
#define TIM_SRC0_CMP0       0x02 	  /**< Timer0���� �Ƚ��� 0 �����*/
#define TIM_SRC0_CMP1       0x03 	  /**< Timer0���� �Ƚ��� 1 �����*/
#define TIM_SRC0_0XOR1      0x04	  /**< Timer0���� ͨ��0��ͨ��1�����*/

/* ����Timer��ʼ�����ź���Դ*/	
#define TIM_EVT_SRC_Timer00 0x00      /**< Timer0_CH0�Ƚ��¼�*/
#define TIM_EVT_SRC_Timer01 0x01      /**< Timer0_CH1�Ƚ��¼�*/
#define TIM_EVT_SRC_Timer10 0x02      /**< Timer1_CH0�Ƚ��¼�*/
#define TIM_EVT_SRC_Timer11 0x03      /**< Timer1_CH1�Ƚ��¼�*/
#define TIM_EVT_SRC_MCPWM_0 0x0A      /**< MCPWM TADC0�¼�*/
#define TIM_EVT_SRC_MCPWM_1 0x0B      /**< MCPWM TADC1�¼�*/
#define TIM_EVT_SRC_MCPWM_2 0x0C      /**< MCPWM TADC2�¼�*/
#define TIM_EVT_SRC_MCPWM_3 0x0D      /**< MCPWM TADC3�¼�*/

/* TIMER����DMA����*/	
#define TIM_IRQ_RE_ZC  			(BIT10)   /**< TIMER����DMA����,��������0(����������)*/
#define TIM_IRQ_RE_CH1 			(BIT9)    /**< TIMER����DMA����,Timer1�Ƚ�OR�����¼�*/
#define TIM_IRQ_RE_CH0 			(BIT8)    /**< TIMER����DMA����,Timer0�Ƚ�OR�����¼�*/
			
// TIMER�ж�ʹ��*/			
#define TIM_IRQ_IE_ZC  			(BIT2)    /**< TIMER��������0(����������)�ж�ʹ��*/
#define TIM_IRQ_IE_CH1 			(BIT1)    /**< Timer1�Ƚ�OR�����¼��ж�ʹ��*/
#define TIM_IRQ_IE_CH0 			(BIT0)    /**< Timer0�Ƚ�OR�����¼��ж�ʹ��*/

/* TIMER�жϱ�־λ*/																	
#define TIM_IRQ_IF_ZC  			(BIT2)    /**< TIMER��������0(����������)�жϱ�־λ*/
#define TIM_IRQ_IF_CH1 			(BIT1)    /**< Timer1�Ƚ�OR�����¼��жϱ�־λ*/
#define TIM_IRQ_IF_CH0 			(BIT0)    /**< Timer0�Ƚ�OR�����¼��жϱ�־λ*/

typedef struct
{
	  FuncState EN;           /**<��ʱ��ģ��ʹ��*/
    uint32_t CAP1_CLR_EN; 	/**<������ CAP1 �����¼�ʱ������ Timer ������������Ч*/
    uint32_t CAP0_CLR_EN; 	/**<������ CAP0 �����¼�ʱ������ Timer ������������Ч*/
    uint32_t ETON;        	/**<Timer ����������ʹ������ 0: �Զ����� 1: �ȴ��ⲿ�¼���������*/
    /**
     * @brief Timer ��������Ƶ \n
     * @see TIM_Clk_Div1 \n
     * @see TIM_Clk_Div2 \n
     * @see TIM_Clk_Div4 \n
     * @see TIM_Clk_Div8 \n
     * @see TIM_Clk_Div16 \n
     * @see TIM_Clk_Div32 \n
     * @see TIM_Clk_Div64 \n
     * @see TIM_Clk_Div128 
     */
    uint32_t CLK_DIV;     
    /**
     * @brief Timer ʱ��Դ \n
     * @see TIM_Clk_SRC_MCLK \n
     * @see TIM_Clk_SRC_Timer00 \n
     * @see TIM_Clk_SRC_Timer01 \n
     * @see TIM_Clk_SRC_Timer10 \n
     * @see TIM_Clk_SRC_Timer11
     */
    uint32_t CLK_SRC; 

    uint32_t TH;          	/**< Timer �������������ޡ��������� 0 ������ TH ֵ���ٴλ� 0 ��ʼ����*/
    /**
     * @brief Timer ͨ�� 1 ����ģʽ�ź���Դ \n
     * @see TIM_SRC1_0     \n   
     * @see TIM_SRC1_1     \n
     * @see TIM_SRC1_CMP0  \n
     * @see TIM_SRC1_CMP1  \n
     * @see TIM_SRC1_0XOR1
     */
    uint32_t SRC1;          
    uint32_t CH1_POL;       /**< Timer ͨ�� 1 �ڱȽ�ģʽ�µ�������Կ��ƣ���������0������ֵ*/
     /**
     * @brief Timer ͨ�� 1 ����ģʽѡ�� \n
     * @see TIMER_OPMode_CAP     \n   
     * @see TIMER_OPMode_CMP     
     */
    uint32_t CH1_MODE;     
    uint32_t CH1_FE_CAP_EN; /**< Timer ͨ�� 1 �½��ز����¼�ʹ�ܡ�1:ʹ�ܣ�0:�ر�*/
    uint32_t CH1_RE_CAP_EN; /**< Timer ͨ�� 1 �����ز����¼�ʹ�ܡ�1:ʹ�ܣ�0:�ر�*/
    uint32_t TIM_CMP1;      /**< Timer ͨ�� 1 �Ƚ�����*/
    /**
     * @brief Timer ͨ�� 0 ����ģʽ�ź���Դ \n
     * @see TIM_SRC0_0     \n   
     * @see TIM_SRC0_1     \n
     * @see TIM_SRC0_CMP0  \n
     * @see TIM_SRC0_CMP1  \n
     * @see TIM_SRC0_0XOR1
     */
    uint32_t SRC0;          
    uint32_t CH0_POL;       /**< Timer ͨ�� 0 �ڱȽ�ģʽ�µ�������Կ��ƣ���������0������ֵ*/
    /**
     * @brief Timer ͨ�� 0 ����ģʽѡ�� \n
     * @see TIMER_OPMode_CAP     \n   
     * @see TIMER_OPMode_CMP     
     */
    uint32_t CH0_MODE;      
    uint32_t CH0_FE_CAP_EN; /**< Timer ͨ�� 0 �½��ز����¼�ʹ�ܡ�1:ʹ�ܣ�0:�ر�*/
    uint32_t CH0_RE_CAP_EN; /**< Timer ͨ�� 0 �����ز����¼�ʹ�ܡ�1:ʹ�ܣ�0:�ر�*/
    uint32_t TIM_CMP0;      /**< Timer ͨ�� 0 �Ƚ�����*/

    uint32_t CNT;     			/**< Timer ��������ǰ����ֵ��д��������д���µļ���ֵ*/
    /**
     * @brief Timer ����ʹ�ܿ�ʼ���ⲿ�¼�ѡ�� \n
     * @see TIM_EVT_SRC_Timer00  \n   
     * @see TIM_EVT_SRC_Timer01  \n
     * @see TIM_EVT_SRC_Timer10  \n
     * @see TIM_EVT_SRC_Timer11  \n
     * @see TIM_EVT_SRC_MCPWM_0  \n
     * @see TIM_EVT_SRC_MCPWM_1  \n
     * @see TIM_EVT_SRC_MCPWM_2  \n
     * @see TIM_EVT_SRC_MCPWM_3  
     */
    uint32_t EVT_SRC; 			
    uint32_t FLT;     			/**< ͨ�� 0/1 �ź��˲����ѡ��0-255*/
    /**
     * @brief Timer �ж�ʹ�� \n
     * @see TIM_IRQ_IE_ZC    \n   
     * @see TIM_IRQ_IE_CH1   \n   
     * @see TIM_IRQ_IE_CH0     
     */
    uint32_t IE;      			
} TIM_TimerInitTypeDef;

/*Timer��ʼ��*/
void TIM_TimerInit(TIM_TimerTypeDef *TIMERx, TIM_TimerInitTypeDef *TIM_TimerInitStruct);
void TIM_TimerStrutInit(TIM_TimerInitTypeDef *TIM_TimerInitStruct);

void TIM_TimerCmd(TIM_TimerTypeDef *TIMERx, FuncState state);

/*TIM��ȡ�жϱ�־*/
uint32_t TIM_GetIRQFlag(TIM_TimerTypeDef *TIMERx , u32 timer_if);
/*TIM�ж����*/
void TIM_ClearIRQFlag(TIM_TimerTypeDef *TIMERx , uint32_t tempFlag);

uint32_t TIM_Timer_GetCount(TIM_TimerTypeDef *TIMERx);
uint32_t TIM_Timer_GetCMPT0(TIM_TimerTypeDef *TIM_TIMERx);
uint32_t TIM_Timer_GetCMPT1(TIM_TimerTypeDef *TIM_TIMERx);

#endif /*__lks32mc03x_TIM_H */
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
