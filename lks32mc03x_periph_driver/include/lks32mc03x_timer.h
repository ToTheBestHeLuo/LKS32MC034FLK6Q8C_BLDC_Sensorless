/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc03x_tim.h\n
 * 文件标识： 无 \n
 * 内容摘要： TIM驱动头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021年11月09日 <td>1.0     <td>YangZJ        <td>创建
 * </table>
 */

#ifndef __LKS32MC03x_TIM_H
#define __LKS32MC03x_TIM_H

/* Includes ------------------------------------------------------------------*/
#include "lks32mc03x_lib.h"

/** 
 *@brief 定时器寄存器结构体句柄
 */
typedef struct
{
    __IO uint32_t CFG;        /**<定时器配置寄存器*/
    __IO uint32_t TH;         /**<定时器计数门限寄存器*/
    __IO uint32_t CNT;        /**<定时器计数值寄存器*/
    __IO uint32_t CMPT0;      /**<定时器比较/捕获寄存器 0*/
    __IO uint32_t CMPT1;      /**<定时器比较/捕获寄存器 1*/
    __IO uint32_t EVT;        /**<定时器外部事件选择寄存器*/
    __IO uint32_t FLT;        /**<定时器滤波控制寄存器*/
    __IO uint32_t IE;         /**<定时器中断使能寄存器*/
    __IO uint32_t IF;         /**<定时器中断标志寄存器*/
} TIM_TimerTypeDef;


/**
 * TIMER0结构体基地址定义
 */
#ifndef TIMER0
#define TIMER0         ((TIM_TimerTypeDef *) TIMER0_BASE)
#endif
/**
 * TIMER1结构体基地址定义
 */
#ifndef TIMER1
#define TIMER1         ((TIM_TimerTypeDef *) TIMER1_BASE)
#endif


#define TIMER_OPMode_CAP ((uint32_t)0x0000001)    /**<工作模式,捕获模式*/
#define TIMER_OPMode_CMP ((uint32_t)0x0000000)    /**<工作模式,比较模式*/

/* 当timer时钟为MCLK时*/	
#define TIM_Clk_Div1        0x00   	  /**< Timer工作频率48Mhz*/
#define TIM_Clk_Div2        0x01   	  /**< Timer工作频率24Mhz*/
#define TIM_Clk_Div4        0x02   	  /**< Timer工作频率12Mhz*/
#define TIM_Clk_Div8        0x03   	  /**< Timer工作频率6Mhz*/
#define TIM_Clk_Div16       0x04  	  /**< Timer工作频率3Mhz*/
#define TIM_Clk_Div32       0x05  	  /**< Timer工作频率1.5Mhz*/
#define TIM_Clk_Div64       0x06  	  /**< Timer工作频率750Khz*/
#define TIM_Clk_Div128      0x07 	  /**< Timer工作频率375Khz*/

#define TIM_Clk_SRC_MCLK    0x00      /**< Timer使用芯片内部时钟*/
#define TIM_Clk_SRC_Timer00 0x01      /**< Timer使用外部Timer0通道0输入信号*/
#define TIM_Clk_SRC_Timer01 0x02      /**< Timer使用外部Timer0通道1输入信号*/
#define TIM_Clk_SRC_Timer10 0x03      /**< Timer使用外部Timer1通道0输入信号*/
#define TIM_Clk_SRC_Timer11 0x04      /**< Timer使用外部Timer1通道1输入信号*/

#define TIM_SRC1_0          0x00      /**< Timer1捕获 外接通道0*/
#define TIM_SRC1_1          0x01      /**< Timer1捕获 外接通道1*/
#define TIM_SRC1_CMP0       0x02 	  /**< Timer1捕获 比较器 0 的输出*/
#define TIM_SRC1_CMP1       0x03 	  /**< Timer1捕获 比较器 1 的输出*/
#define TIM_SRC1_0XOR1      0x04	  /**< Timer1捕获 通道0和通道1的异或*/

#define TIM_SRC0_0          0x00      /**< Timer0捕获 外接通道0*/
#define TIM_SRC0_1          0x01      /**< Timer0捕获 外接通道1*/
#define TIM_SRC0_CMP0       0x02 	  /**< Timer0捕获 比较器 0 的输出*/
#define TIM_SRC0_CMP1       0x03 	  /**< Timer0捕获 比较器 1 的输出*/
#define TIM_SRC0_0XOR1      0x04	  /**< Timer0捕获 通道0和通道1的异或*/

/* 触发Timer开始计数信号来源*/	
#define TIM_EVT_SRC_Timer00 0x00      /**< Timer0_CH0比较事件*/
#define TIM_EVT_SRC_Timer01 0x01      /**< Timer0_CH1比较事件*/
#define TIM_EVT_SRC_Timer10 0x02      /**< Timer1_CH0比较事件*/
#define TIM_EVT_SRC_Timer11 0x03      /**< Timer1_CH1比较事件*/
#define TIM_EVT_SRC_MCPWM_0 0x0A      /**< MCPWM TADC0事件*/
#define TIM_EVT_SRC_MCPWM_1 0x0B      /**< MCPWM TADC1事件*/
#define TIM_EVT_SRC_MCPWM_2 0x0C      /**< MCPWM TADC2事件*/
#define TIM_EVT_SRC_MCPWM_3 0x0D      /**< MCPWM TADC3事件*/

/* TIMER产生DMA请求*/	
#define TIM_IRQ_RE_ZC  			(BIT10)   /**< TIMER产生DMA请求,计数器过0(计数器回零)*/
#define TIM_IRQ_RE_CH1 			(BIT9)    /**< TIMER产生DMA请求,Timer1比较OR捕获事件*/
#define TIM_IRQ_RE_CH0 			(BIT8)    /**< TIMER产生DMA请求,Timer0比较OR捕获事件*/
			
// TIMER中断使能*/			
#define TIM_IRQ_IE_ZC  			(BIT2)    /**< TIMER计数器过0(计数器回零)中断使能*/
#define TIM_IRQ_IE_CH1 			(BIT1)    /**< Timer1比较OR捕获事件中断使能*/
#define TIM_IRQ_IE_CH0 			(BIT0)    /**< Timer0比较OR捕获事件中断使能*/

/* TIMER中断标志位*/																	
#define TIM_IRQ_IF_ZC  			(BIT2)    /**< TIMER计数器过0(计数器回零)中断标志位*/
#define TIM_IRQ_IF_CH1 			(BIT1)    /**< Timer1比较OR捕获事件中断标志位*/
#define TIM_IRQ_IF_CH0 			(BIT0)    /**< Timer0比较OR捕获事件中断标志位*/

typedef struct
{
	  FuncState EN;           /**<定时器模块使能*/
    uint32_t CAP1_CLR_EN; 	/**<当发生 CAP1 捕获事件时，清零 Timer 计数器，高有效*/
    uint32_t CAP0_CLR_EN; 	/**<当发生 CAP0 捕获事件时，清零 Timer 计数器，高有效*/
    uint32_t ETON;        	/**<Timer 计数器计数使能配置 0: 自动运行 1: 等待外部事件触发计数*/
    /**
     * @brief Timer 计数器分频 \n
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
     * @brief Timer 时钟源 \n
     * @see TIM_Clk_SRC_MCLK \n
     * @see TIM_Clk_SRC_Timer00 \n
     * @see TIM_Clk_SRC_Timer01 \n
     * @see TIM_Clk_SRC_Timer10 \n
     * @see TIM_Clk_SRC_Timer11
     */
    uint32_t CLK_SRC; 

    uint32_t TH;          	/**< Timer 计数器计数门限。计数器从 0 计数到 TH 值后再次回 0 开始计数*/
    /**
     * @brief Timer 通道 1 捕获模式信号来源 \n
     * @see TIM_SRC1_0     \n   
     * @see TIM_SRC1_1     \n
     * @see TIM_SRC1_CMP0  \n
     * @see TIM_SRC1_CMP1  \n
     * @see TIM_SRC1_0XOR1
     */
    uint32_t SRC1;          
    uint32_t CH1_POL;       /**< Timer 通道 1 在比较模式下的输出极性控制，计数器回0后的输出值*/
     /**
     * @brief Timer 通道 1 工作模式选择 \n
     * @see TIMER_OPMode_CAP     \n   
     * @see TIMER_OPMode_CMP     
     */
    uint32_t CH1_MODE;     
    uint32_t CH1_FE_CAP_EN; /**< Timer 通道 1 下降沿捕获事件使能。1:使能；0:关闭*/
    uint32_t CH1_RE_CAP_EN; /**< Timer 通道 1 上升沿捕获事件使能。1:使能；0:关闭*/
    uint32_t TIM_CMP1;      /**< Timer 通道 1 比较门限*/
    /**
     * @brief Timer 通道 0 捕获模式信号来源 \n
     * @see TIM_SRC0_0     \n   
     * @see TIM_SRC0_1     \n
     * @see TIM_SRC0_CMP0  \n
     * @see TIM_SRC0_CMP1  \n
     * @see TIM_SRC0_0XOR1
     */
    uint32_t SRC0;          
    uint32_t CH0_POL;       /**< Timer 通道 0 在比较模式下的输出极性控制，计数器回0后的输出值*/
    /**
     * @brief Timer 通道 0 工作模式选择 \n
     * @see TIMER_OPMode_CAP     \n   
     * @see TIMER_OPMode_CMP     
     */
    uint32_t CH0_MODE;      
    uint32_t CH0_FE_CAP_EN; /**< Timer 通道 0 下降沿捕获事件使能。1:使能；0:关闭*/
    uint32_t CH0_RE_CAP_EN; /**< Timer 通道 0 上升沿捕获事件使能。1:使能；0:关闭*/
    uint32_t TIM_CMP0;      /**< Timer 通道 0 比较门限*/

    uint32_t CNT;     			/**< Timer 计数器当前计数值。写操作可以写入新的计数值*/
    /**
     * @brief Timer 计数使能开始后，外部事件选择 \n
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
    uint32_t FLT;     			/**< 通道 0/1 信号滤波宽度选择，0-255*/
    /**
     * @brief Timer 中断使能 \n
     * @see TIM_IRQ_IE_ZC    \n   
     * @see TIM_IRQ_IE_CH1   \n   
     * @see TIM_IRQ_IE_CH0     
     */
    uint32_t IE;      			
} TIM_TimerInitTypeDef;

/*Timer初始化*/
void TIM_TimerInit(TIM_TimerTypeDef *TIMERx, TIM_TimerInitTypeDef *TIM_TimerInitStruct);
void TIM_TimerStrutInit(TIM_TimerInitTypeDef *TIM_TimerInitStruct);

void TIM_TimerCmd(TIM_TimerTypeDef *TIMERx, FuncState state);

/*TIM获取中断标志*/
uint32_t TIM_GetIRQFlag(TIM_TimerTypeDef *TIMERx , u32 timer_if);
/*TIM中断清除*/
void TIM_ClearIRQFlag(TIM_TimerTypeDef *TIMERx , uint32_t tempFlag);

uint32_t TIM_Timer_GetCount(TIM_TimerTypeDef *TIMERx);
uint32_t TIM_Timer_GetCMPT0(TIM_TimerTypeDef *TIM_TIMERx);
uint32_t TIM_Timer_GetCMPT1(TIM_TimerTypeDef *TIM_TIMERx);

#endif /*__lks32mc03x_TIM_H */
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
