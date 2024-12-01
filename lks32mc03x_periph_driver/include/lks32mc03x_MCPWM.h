/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc03x_MCPWM.h\n
 * 文件标识： 无 \n
 * 内容摘要： mcpwm驱动头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021年10月14日 <td>1.0       <td>HMG     <td>创建
 * </table>
 */

#ifndef __LKS32MC03x_MCPWM_H
#define __LKS32MC03x_MCPWM_H

/* Includes ------------------------------------------------------------------*/
#include "lks32mc03x_lib.h"
/** 
 *@brief MCPWM寄存器结构体句柄
 */
typedef struct
{
  __IO u32 PWM_TH00;    /**< MCPWM CH0_P 比较门限值寄存器 */
  __IO u32 PWM_TH01;    /**< MCPWM CH0_N 比较门限值寄存器 */
  __IO u32 PWM_TH10;    /**< MCPWM CH1_P 比较门限值寄存器 */
  __IO u32 PWM_TH11;    /**< MCPWM CH1_N 比较门限值寄存器 */
  __IO u32 PWM_TH20;    /**< MCPWM CH2_P 比较门限值寄存器 */
  __IO u32 PWM_TH21;    /**< MCPWM CH2_N 比较门限值寄存器 */
  __IO u32 PWM_TH30;    /**< MCPWM CH3_P 比较门限值寄存器 */
  __IO u32 PWM_TH31;    /**< MCPWM CH3_N 比较门限值寄存器 */
  __IO u32 PWM_TMR0;    /**< ADC 采样定时器比较门限 0 寄存器 */
  __IO u32 PWM_TMR1;    /**< ADC 采样定时器比较门限 1 寄存器 */
  __IO u32 PWM_TMR2;    /**< ADC 采样定时器比较门限 2 寄存器 */
  __IO u32 PWM_TMR3;    /**< ADC 采样定时器比较门限 3 寄存器 */
  __IO u32 PWM_TH0;     /**< MCPWM 时基 0 门限值寄存器 */
  __IO u32 PWM_TH1;     /**< MCPWM 时基 1 门限值寄存器 */
  __IO u32 PWM_CNT0;    /**< MCPWM 时基 0 计数器寄存器 */
  __IO u32 PWM_CNT1;    /**< MCPWM 时基 0 计数器寄存器 */
  __IO u32 PWM_UPDATE;  /**< MCPWM 手动加载控制寄存器 */
  __IO u32 PWM_FCNT;    /**< MCPWM FAIL 时刻 CNT 值 */
  __IO u32 PWM_EVT0;    /**< MCPWM 时基 0 外部触发 */
  __IO u32 PWM_EVT1;    /**< MCPWM 时基 1 外部触发 */
  __IO u32 PWM_DTH0;    /**< MCPWM CH0/1/2/3 N通道死区宽度控制寄存器 */
  __IO u32 PWM_DTH1;    /**< MCPWM CH0/1/2/3 P通道死区宽度控制寄存器 0x54 */
  __IO u32 null0;       /**< 空闲 0x58 */
  __IO u32 null1;       /**< 空闲 0x5C */
  __IO u32 null2;       /**< 空闲 0x60 */
  __IO u32 null3;       /**< 空闲 0x64 */
  __IO u32 null4;       /**< 空闲 0x68 */
  __IO u32 null5;       /**< 空闲 0x6C */
  __IO u32 PWM_FLT;     /**< MCPWM 滤波时钟分频寄存器 */
  __IO u32 PWM_SDCFG;   /**< MCPWM 加载配置寄存器 */
  __IO u32 PWM_AUEN;    /**< MCPWM 自动更新使能寄存器 */
  __IO u32 PWM_TCLK;    /**< MCPWM 时钟分频控制寄存器 */
  __IO u32 PWM_IE0;     /**< MCPWM 时基 0 中断控制寄存器 */
  __IO u32 PWM_IF0;     /**< MCPWM 时基 0 中断标志位寄存器 */
  __IO u32 PWM_IE1;     /**< MCPWM 时基 1 中断控制寄存器 */
  __IO u32 PWM_IF1;     /**< MCPWM 时基 1 中断标志位寄存器 */
  __IO u32 PWM_EIE;     /**< MCPWM 异常中断控制寄存器 0x90*/
  __IO u32 PWM_EIF;     /**< MCPWM 异常中断标志位寄存器 0x94*/
  __IO u32 PWM_RE;      /**< MCPWM DMA 请求控制寄存器 */
  __IO u32 PWM_PP;      /**< MCPWM 推挽模式使能寄存器 */
  __IO u32 PWM_IO01;    /**< MCPWM CH0 CH1 IO 控制寄存器 */
  __IO u32 PWM_IO23;    /**< MCPWM CH2 CH3 IO 控制寄存器 */
  __IO u32 PWM_FAIL012; /**< MCPWM CH0 CH1 CH2 短路控制寄存器 */
  __IO u32 PWM_FAIL3;   /**< MCPWM CH3 短路控制寄存器 */
  __IO u32 PWM_PRT;     /**< MCPWM 保护寄存器 */
	__IO u32 PWM_SWAP;    /**< MCPWM 通道重映射寄存器 */
  __IO u32 PWM_CHMSK;   /**< MCPWM 通道屏蔽位寄存器 */
} MCPWM_REG_TypeDef;

/**
 * MCPWM结构体基地址定义
 */
#ifndef MCPWM0
#define MCPWM0   ((MCPWM_REG_TypeDef *) MCPWM_BASE)
#endif

/** 
 *@brief MCPWM初始化结构体句柄，初始化时请定义该句柄，并用其它地址来传参
 */
typedef struct
{
  u16 TimeBase0_PERIOD;       /**< 时期0周期设置*/
  u16 TimeBase1_PERIOD;       /**< 时期1周期设置*/
  u8 CLK_DIV;                 /**< MCPWM 分频系数 */
  u8 MCLK_EN;                 /**< MCPWM 时钟使能开关 */
  u8 MCPWM_Cnt0_EN;           /**< MCPWM 时基0主计数器使能开关 */
  u8 MCPWM_Cnt1_EN;           /**< MCPWM 时基1主计数器使能开关 */
  u8 GPIO_BKIN_Filter;        /**< GPIO输入滤波时钟设置1-256 */
  u8 CMP_BKIN_Filter;         /**< 比较器CMP输入滤波时钟设置1-256 */

  u8 TMR2_TimeBase_Sel;       /**< TMR2 比较门限寄存器 时基选择 0:时基0 | 1:时基1 */
  u8 TMR3_TimeBase_Sel;       /**< TMR3 比较门限寄存器 时基选择 1:时基0 | 1:时基1 */

  u8 TimeBase0_Trig_Enable;   /**< 时基0 外部触发使能 */
  u8 TimeBase1_Trig_Enable;   /**< 时基1 外部触发使能*/

  u16 TimeBase_TrigEvt0;      /**< 时基0 外部触发事件选择 */
  u16 TimeBase_TrigEvt1;      /**< 时基1 外部触发事件选择 */

  s16 TimeBase0Init_CNT;      /**< 时基0 计数器初始值 */
  s16 TimeBase1Init_CNT;      /**< 时基1 计数器初始值 */

  u16 MCPWM_WorkModeCH0;      /**< MCPWM CH0工作模式：边沿对齐/中心对齐 */
  u16 MCPWM_WorkModeCH1;      /**< MCPWM CH0工作模式：边沿对齐/中心对齐 */
  u16 MCPWM_WorkModeCH2;      /**< MCPWM CH0工作模式：边沿对齐/中心对齐 */
  u16 MCPWM_WorkModeCH3;      /**< MCPWM CH0工作模式：边沿对齐/中心对齐 */
                         
  u16 TriggerPoint0;          /**< PWM触发ADC事件0，时间点设置 */
  u16 TriggerPoint1;          /**< PWM触发ADC事件1，时间点设置 */
  u16 TriggerPoint2;          /**< PWM触发ADC事件2，时间点设置 */
  u16 TriggerPoint3;          /**< PWM触发ADC事件3，时间点设置 */
                         
  u16 DeadTimeCH0123N;        /**< CH0123N死区时间设置　*/
  u16 DeadTimeCH0123P;        /**< CH0123P死区时间设置　*/
                         
  u8 CH0N_Polarity_INV;       /**< CH0N输出极性取反，0:正常输出；1:取反输出 */
  u8 CH0P_Polarity_INV;       /**< CH0P输出极性取反，0:正常输出；1:取反输出 */
  u8 CH1N_Polarity_INV;       /**< CH1N输出极性取反，0:正常输出；1:取反输出 */
  u8 CH1P_Polarity_INV;       /**< CH1P输出极性取反，0:正常输出；1:取反输出 */
  u8 CH2N_Polarity_INV;       /**< CH2N输出极性取反，0:正常输出；1:取反输出 */
  u8 CH2P_Polarity_INV;       /**< CH2P输出极性取反，0:正常输出；1:取反输出 */
  u8 CH3N_Polarity_INV;       /**< CH3N输出极性取反，0:正常输出；1:取反输出 */
  u8 CH3P_Polarity_INV;       /**< CH3P输出极性取反，0:正常输出；1:取反输出 */

  u8 CH0P_SCTRLP;             /**< 当CH0_PS = 1时，输出到CH0_P通道的值*/
  u8 CH0N_SCTRLN;             /**< 当CH0_NS = 1时，输出到CH0_N通道的值*/
  u8 CH1P_SCTRLP;             /**< 当CH1_PS = 1时，输出到CH1_P通道的值*/
  u8 CH1N_SCTRLN;             /**< 当CH1_NS = 1时，输出到CH1_N通道的值*/
  u8 CH2P_SCTRLP;             /**< 当CH2_PS = 1时，输出到CH2_P通道的值*/
  u8 CH2N_SCTRLN;             /**< 当CH2_NS = 1时，输出到CH2_N通道的值*/
  u8 CH3P_SCTRLP;             /**< 当CH3_PS = 1时，输出到CH3_P通道的值*/
  u8 CH3N_SCTRLN;             /**< 当CH3_NS = 1时，输出到CH3_PN通道的值*/
   
	u8 CH0_PS;                  /**< CH0_P信号来源，1：来自CH0_SCTRLP；0：来自MCPWM实际运行计数器*/
	u8 CH0_NS;                  /**< CH0_N信号来源，1：来自CH0_SCTRLN；0：来自MCPWM实际运行计数器*/
	u8 CH1_PS;                  /**< CH1_P信号来源，1：来自CH1_SCTRLP；0：来自MCPWM实际运行计数器*/
	u8 CH1_NS;                  /**< CH1_N信号来源，1：来自CH1_SCTRLN；0：来自MCPWM实际运行计数器*/
	u8 CH2_PS;                  /**< CH2_P信号来源，1：来自CH2_SCTRLP；0：来自MCPWM实际运行计数器*/
	u8 CH2_NS;                  /**< CH2_N信号来源，1：来自CH2_SCTRLN；0：来自MCPWM实际运行计数器*/
	u8 CH3_PS;                  /**< CH3_P信号来源，1：来自CH3_SCTRLP；0：来自MCPWM实际运行计数器*/
	u8 CH3_NS;                  /**< CH3_N信号来源，1：来自CH3_SCTRLN；0：来自MCPWM实际运行计数器*/
	
	u8 Switch_CH0N_CH0P;        /**< 交换CH0N, CH0P信号输出使能开关 */
  u8 Switch_CH1N_CH1P;        /**< 交换CH1N, CH1P信号输出使能开关 */
  u8 Switch_CH2N_CH2P;        /**< 交换CH2N, CH2P信号输出使能开关 */
  u8 Switch_CH3N_CH3P;        /**< 交换CH3N, CH3P信号输出使能开关 */
	
  u8 MCPWM_UpdateT0Interval; /**< MCPWM T0事件更新间隔 */
  u8 MCPWM_UpdateT1Interval; /**< MCPWM T1事件更新间隔 */
  u8 MCPWM_Base0T0_UpdateEN; /**< MCPWM 时基0 T0事件更新使能 */
  u8 MCPWM_Base0T1_UpdateEN; /**< MCPWM 时基0 T1事件更新使能 */
  u8 MCPWM_Base1T0_UpdateEN; /**< MCPWM 时基1 T0事件更新使能 */
  u8 MCPWM_Base1T1_UpdateEN; /**< MCPWM 时基1 T1事件更新使能 */
  u8 MCPWM_Auto0_ERR_EN;     /**< MCPWM 时基0更新事件是否自动打开MOE, 使能开关 */
  u8 MCPWM_Auto1_ERR_EN;     /**< MCPWM 时基1更新事件是否自动打开MOE, 使能开关 */

  u8 FAIL0_INPUT_EN;         /**< FAIL0 输入功能使能 */
  u8 FAIL1_INPUT_EN;         /**< FAIL1 输入功能使能 */
  u8 FAIL0_Signal_Sel;       /**< FAIL0 信号选择，比较器0或GPIO */
  u8 FAIL1_Signal_Sel;       /**< FAIL1 信号选择，比较器0或GPIO */
  u8 FAIL0_Polarity;         /**< FAIL0 信号极性设置，高有效或低有效 */
  u8 FAIL1_Polarity;         /**< FAIL1 信号极性设置，高有效或低有效 */
  u8 DebugMode_PWM_out;      /**< Debug时，MCU进入Halt, MCPWM信号是否正常输出 */
  u8 FAIL2_INPUT_EN;         /**< FAIL2 输入功能使能 */
  u8 FAIL3_INPUT_EN;         /**< FAIL3 输入功能使能 */
  u8 FAIL2_Signal_Sel;       /**< FAIL2 信号选择，比较器0或GPIO */
  u8 FAIL3_Signal_Sel;       /**< FAIL3 信号选择，比较器0或GPIO */
  u8 FAIL2_Polarity;         /**< FAIL2 信号极性设置，高有效或低有效 */
  u8 FAIL3_Polarity;         /**< FAIL3 信号极性设置，高有效或低有效 */

  u8 CH0P_default_output;    /**< CH0P MOE为0时或发生FAIL事件时，默认电平输出 */
  u8 CH0N_default_output;    /**< CH0N MOE为0时或发生FAIL事件时，默认电平输出 */
  u8 CH1P_default_output;    /**< CH1P MOE为0时或发生FAIL事件时，默认电平输出 */
  u8 CH1N_default_output;    /**< CH1N MOE为0时或发生FAIL事件时，默认电平输出 */
  u8 CH2P_default_output;    /**< CH2P MOE为0时或发生FAIL事件时，默认电平输出 */
  u8 CH2N_default_output;    /**< CH2N MOE为0时或发生FAIL事件时，默认电平输出 */
  u8 CH3P_default_output;    /**< CH3P MOE为0时或发生FAIL事件时，默认电平输出 */
  u8 CH3N_default_output;    /**< CH3N MOE为0时或发生FAIL事件时，默认电平输出 */
													   
  u8 CNT0_T0_Update_INT_EN;  /**< 时基0 T0更新事件中断使能 */
  u8 CNT0_T1_Update_INT_EN;  /**< 时基0 T1更新事件中断使能 */
	u8 CNT0_Update_TH00_EN;    /**< MCPWM 实际运行系统中计数器的计数值等于MCPWM_TH00中断源使能*/
	u8 CNT0_Update_TH01_EN;    /**< MCPWM 实际运行系统中计数器的计数值等于MCPWM_TH01中断源使能*/
	u8 CNT0_Update_TH10_EN;    /**< MCPWM 实际运行系统中计数器的计数值等于MCPWM_TH10中断源使能*/
	u8 CNT0_Update_TH11_EN;    /**< MCPWM 实际运行系统中计数器的计数值等于MCPWM_TH11中断源使能*/
	u8 CNT0_Update_TH20_EN;    /**< MCPWM 实际运行系统中计数器的计数值等于MCPWM_TH20中断源使能*/
	u8 CNT0_Update_TH21_EN;    /**< MCPWM 实际运行系统中计数器的计数值等于MCPWM_TH21中断源使能*/
	u8 CNT0_Update_TH30_EN;    /**< MCPWM 实际运行系统中计数器的计数值等于MCPWM_TH30中断源使能*/
	u8 CNT0_Update_TH31_EN;    /**< MCPWM 实际运行系统中计数器的计数值等于MCPWM_TH31中断源使能*/		
  u8 CNT0_TMR0_Match_INT_EN; /**< 时基0 TMR0计数事件匹配事件中断使能 */
  u8 CNT0_TMR1_Match_INT_EN; /**< 时基0 TMR1计数事件匹配事件中断使能 */
	u8 CNT0_TMR2_Match_INT_EN; /**< 时基0 TMR2计数事件匹配事件中断使能 */
  u8 CNT0_TMR3_Match_INT_EN; /**< 时基0 TMR3计数事件匹配事件中断使能 */
  u8 CNT0_Update_EN;         /**< 寄存器更新到 MCPWM 实际运行系统的中断源使能 */

  u8 CNT1_T0_Update_INT_EN;  /**< 时基1 T0更新事件中断使能 */
  u8 CNT1_T1_Update_INT_EN;  /**< 时基1 T1更新事件中断使能 */
	u8 CNT1_Update_TH30_EN;    /**< MCPWM 实际运行系统中计数器的计数值等于MCPWM_TH30中断源使能*/
	u8 CNT1_Update_TH31_EN;    /**< MCPWM 实际运行系统中计数器的计数值等于MCPWM_TH31中断源使能*/		
	u8 CNT1_TMR2_Match_INT_EN; /**< 时基1 TMR2计数事件匹配事件中断使能 */
  u8 CNT1_TMR3_Match_INT_EN; /**< 时基1 TMR3计数事件匹配事件中断使能 */
  u8 CNT1_Update_EN;         /**< 寄存器更新到 MCPWM 实际运行系统的中断源使能 */

  u8 TMR0_DMA_RE;            /**< MCPWM计数器命中TMR0，DMA请求使能*/
  u8 TMR1_DMA_RE;            /**< MCPWM计数器命中TMR1，DMA请求使能*/
  u8 TMR2_DMA_RE;            /**< MCPWM计数器命中TMR2，DMA请求使能*/
  u8 TMR3_DMA_RE;            /**< MCPWM计数器命中TMR3，DMA请求使能*/
  u8 TR0_T0_DMA_RE;          /**< 时基0 T0事件DMA请求使能*/
  u8 TR0_T1_DMA_RE;          /**< 时基0 T1事件DMA请求使能*/
  u8 TR1_T0_DMA_RE;          /**< 时基1 T0事件DMA请求使能*/
  u8 TR1_T1_DMA_RE;          /**< 时基1 T1事件DMA请求使能*/

  u8 FAIL0_INT_EN;           /**< FAIL0事件中断使能 (MCPWM_CH0-CH2急停事件)*/
  u8 FAIL1_INT_EN;           /**< FAIL1事件中断使能 (MCPWM_CH0-CH2急停事件)*/
  u8 FAIL2_INT_EN;           /**< FAIL2事件中断使能 (MCPWM_CH3急停事件)*/
  u8 FAIL3_INT_EN;           /**< FAIL3事件中断使能 (MCPWM_CH3急停事件)*/

  u16 AUEN;                  /**< 自动更新使能寄存器 */
	
	u8  IO_PPE;                /**< 推挽模式使能信号 */

} MCPWM_InitTypeDef;

/* MCPWM_FAIL012 MOE */
#define MCPWM_MOE_ENABLE_MASK ((u16)0x0040)   /**< 打开MOE位MASK位 */
#define MCPWM_MOE_DISABLE_MASK ((u16)~0x0040) /**< 关MOE位MASK位 */

/* MCPWM_AUEN  MCPWM 自动更新使能寄存器 */
#define TH00_AUEN BIT0  /**< MCPWM_TH00 自动加载使能 */
#define TH01_AUEN BIT1  /**< MCPWM_TH01 自动加载使能 */ 
#define TH10_AUEN BIT2  /**< MCPWM_TH10 自动加载使能 */
#define TH11_AUEN BIT3  /**< MCPWM_TH11 自动加载使能 */
#define TH20_AUEN BIT4  /**< MCPWM_TH20 自动加载使能 */
#define TH21_AUEN BIT5  /**< MCPWM_TH21 自动加载使能 */
#define TH30_AUEN BIT6  /**< MCPWM_TH30 自动加载使能 */
#define TH31_AUEN BIT7  /**< MCPWM_TH31 自动加载使能 */
#define TMR0_AUEN BIT8  /**< MCPWM_TMR0 自动加载使能 */
#define TMR1_AUEN BIT9  /**< MCPWM_TMR1 自动加载使能 */
#define TMR2_AUEN BIT10 /**< MCPWM_TMR2 自动加载使能 */
#define TMR3_AUEN BIT11 /**< MCPWM_TMR3 自动加载使能 */
#define TH0_AUEN  BIT12 /**< MCPWM_TH0 自动加载使能 */
#define TH1_AUEN  BIT13 /**< MCPWM_TH1 自动加载使能 */
#define CNT0_AUEN BIT14 /**< MCPWM_CNT0 自动加载使能 */
#define CNT1_AUEN BIT15 /**< MCPWM_CNT1 自动加载使能 */

/* MCPWM_AUEN  MCPWM 自动更新使能寄存器 */
#define CENTRAL_PWM_MODE 0 /**< 中心对齐PWM模式 */
#define EDGE_PWM_MODE 1    /**< 边沿对齐PWM模式 */

/* MCPWM_FAIL012[8:13] MCPWM_FAIL3[8:9] 通道默认输出电平 */
#define HIGH_LEVEL 1 /**< MCPWM通道空闲状态输出高电平 */
#define LOW_LEVEL 0  /**< MCPWM通道空闲状态输出低电平 */

/* MCPWM_IO01和MCPWM_IO23 极性设置CHxPP CHxNP */
#define HIGH_LEVEL_VALID 0 /**< FAIL极性选择 高电平有效 */
#define LOW_LEVEL_VALID 1  /**< FAIL极性选择 低电平有效 */

/* MCPWM_FAIL012和MCPWM_FAIL3 failx信号来源 */
#define FAIL_SEL_CMP 1 /**< Fail事件来源比较器 */
#define FAIL_SEL_IO 0  /**< Fail事件来源IO */




/* MCPWM_PP  MCPWM 推挽模式使能寄存器 */
#define  MCPWM_IO0_PPEN  BIT0         /**< IO0 推挽模式使能信号 */
#define  MCPWM_IO1_PPEN  BIT1         /**< IO1 推挽模式使能信号 */
#define  MCPWM_IO2_PPEN  BIT2         /**< IO2 推挽模式使能信号 */
#define  MCPWM_IO3_PPEN  BIT3         /**< IO3 推挽模式使能信号 */


#define PWM_Clk_Div1     0x00         /**<MCPWM工作频率48M*/
#define PWM_Clk_Div2     0x01         /**<MCPWM工作频率24M*/
#define PWM_Clk_Div4     0x02         /**<MCPWM工作频率12M*/
#define PWM_Clk_Div8     0x03         /**<MCPWM工作频率6M*/  


#define MCPWM_UPDATE_REG()  \
  {                         \
    MCPWM_PRT = 0x0000DEAD; \
    MCPWM_UPDATE = 0x00ff;  \
    MCPWM_PRT = 0x0000CAFE; \
  }/**< PWM通道交换 */
	
/** 
 *@brief MCPWM比较门限寄存器更新结构体
 */
typedef struct
{
	s16 th00;/**< 对应MCPWM_TH00 */
	s16 th01;/**< 对应MCPWM_TH01 */
	s16 th10;/**< 对应MCPWM_TH10 */
	s16 th11;/**< 对应MCPWM_TH11 */
	s16 th20;/**< 对应MCPWM_TH20 */
	s16 th21;/**< 对应MCPWM_TH21 */
	s16 th30;/**< 对应MCPWM_TH30 */
	s16 th31;/**< 对应MCPWM_TH31 */
}strPWM_DutyCycleDef;

/** 
 *@brief MCPWM 时基号选择 
 */
typedef enum 
{  
  CNT0 = 0, 
  CNT1 = 1,
}CNT_Num;

/* MCPWM时基0对应的中断 */
#define CNT0_MCPWM_T0_IRQ_EN        BIT0  /**< 计数器计数值回到MCPWM_TH中断使能 */
#define CNT0_MCPWM_T1_IRQ_EN        BIT1  /**< 计数器计数值回到0中断使能 */
#define CNT0_MCPWM_TH00_IRQ_EN      BIT2  /**< 计数器计数值回到MCPWM_TH00中断使能 */
#define CNT0_MCPWM_TH01_IRQ_EN      BIT3  /**< 计数器计数值回到MCPWM_TH01中断使能 */
#define CNT0_MCPWM_TH10_IRQ_EN      BIT4  /**< 计数器计数值回到MCPWM_TH10中断使能 */
#define CNT0_MCPWM_TH11_IRQ_EN      BIT5  /**< 计数器计数值回到MCPWM_TH11中断使能 */
#define CNT0_MCPWM_TH20_IRQ_EN      BIT6  /**< 计数器计数值回到MCPWM_TH20中断使能 */
#define CNT0_MCPWM_TH21_IRQ_EN      BIT7  /**< 计数器计数值回到MCPWM_TH21中断使能 */
#define CNT0_MCPWM_TH30_IRQ_EN      BIT8  /**< 计数器计数值回到MCPWM_TH30中断使能 */
#define CNT0_MCPWM_TH31_IRQ_EN      BIT9  /**< 计数器计数值回到MCPWM_TH31中断使能 */
#define CNT0_MCPWM_TMR0_IRQ_EN      BIT10 /**< 计数器计数值回到MCPWM_TMR0中断使能 */
#define CNT0_MCPWM_TMR1_IRQ_EN      BIT11 /**< 计数器计数值回到MCPWM_TMR1中断使能 */
#define CNT0_MCPWM_TMR2_IRQ_EN      BIT12 /**< 计数器计数值回到MCPWM_TMR0中断使能 */
#define CNT0_MCPWM_TMR3_IRQ_EN      BIT13 /**< 计数器计数值回到MCPWM_TMR1中断使能 */
#define CNT0_MCPWM_SHADE_IRQ_EN     BIT14 /**< MCPWM_TH/MCPWM_TH00-MCPWM_TH31/\
MCPWM_TR0-MCPWM_TR3等寄存器更新到MCPWM实际运行系统中断使能 */

/* MCPWM时基1对应的中断 */
#define CNT1_MCPWM_T0_IRQ_EN        BIT0  /**< 计数器计数值回到MCPWM_TH中断使能 */
#define CNT1_MCPWM_T1_IRQ_EN        BIT1  /**< 计数器计数值回到0中断使能 */
#define CNT1_MCPWM_TH00_IRQ_EN      BIT2  /**< 计数器计数值回到MCPWM_TH00中断使能 */
#define CNT1_MCPWM_TH01_IRQ_EN      BIT3  /**< 计数器计数值回到MCPWM_TH01中断使能 */
#define CNT1_MCPWM_TH10_IRQ_EN      BIT4  /**< 计数器计数值回到MCPWM_TH10中断使能 */
#define CNT1_MCPWM_TH11_IRQ_EN      BIT5  /**< 计数器计数值回到MCPWM_TH11中断使能 */
#define CNT1_MCPWM_TH20_IRQ_EN      BIT6  /**< 计数器计数值回到MCPWM_TH20中断使能 */
#define CNT1_MCPWM_TH21_IRQ_EN      BIT7  /**< 计数器计数值回到MCPWM_TH21中断使能 */
#define CNT1_MCPWM_TH30_IRQ_EN      BIT8  /**< 计数器计数值回到MCPWM_TH30中断使能 */
#define CNT1_MCPWM_TH31_IRQ_EN      BIT9  /**< 计数器计数值回到MCPWM_TH31中断使能 */
#define CNT1_MCPWM_TMR0_IRQ_EN      BIT10 /**< 计数器计数值回到MCPWM_TMR0中断使能 */
#define CNT1_MCPWM_TMR1_IRQ_EN      BIT11 /**< 计数器计数值回到MCPWM_TMR1中断使能 */
#define CNT1_MCPWM_TMR2_IRQ_EN      BIT12 /**< 计数器计数值回到MCPWM_TMR0中断使能 */
#define CNT1_MCPWM_TMR3_IRQ_EN      BIT13 /**< 计数器计数值回到MCPWM_TMR1中断使能 */
#define CNT1_MCPWM_SHADE_IRQ_EN     BIT14 /**< MCPWM_TH/MCPWM_TH00-MCPWM_TH31/\
MCPWM_TR0-MCPWM_TR3等寄存器更新到MCPWM实际运行系统中断使能 */

#define CNT0_MCPWM_FAIL0_IRQ_EN          BIT4     /**< MCPWM_FAIL0中断使能 */
#define CNT0_MCPWM_FAIL1_IRQ_EN          BIT5     /**< MCPWM_FAIL1中断使能 */
#define CNT1_MCPWM_FAIL2_IRQ_EN          BIT6     /**< MCPWM_FAIL2中断使能 */
#define CNT1_MCPWM_FAIL3_IRQ_EN          BIT7     /**< MCPWM_FAIL3中断使能 */

/* MCPWM时基0对应的中断标志位 */
#define CNT0_MCPWM_T0_IRQ_IF        BIT0  /**< 计数器计数值回到MCPWM_TH中断标志位 */
#define CNT0_MCPWM_T1_IRQ_IF        BIT1  /**< 计数器计数值回到0中断标志位 */
#define CNT0_MCPWM_TH00_IRQ_IF      BIT2  /**< 计数器计数值回到MCPWM_TH00中断标志位 */
#define CNT0_MCPWM_TH01_IRQ_IF      BIT3  /**< 计数器计数值回到MCPWM_TH01中断标志位 */
#define CNT0_MCPWM_TH10_IRQ_IF      BIT4  /**< 计数器计数值回到MCPWM_TH10中断标志位 */
#define CNT0_MCPWM_TH11_IRQ_IF      BIT5  /**< 计数器计数值回到MCPWM_TH11中断标志位 */
#define CNT0_MCPWM_TH20_IRQ_IF      BIT6  /**< 计数器计数值回到MCPWM_TH20中断标志位 */
#define CNT0_MCPWM_TH21_IRQ_IF      BIT7  /**< 计数器计数值回到MCPWM_TH21中断标志位 */
#define CNT0_MCPWM_TH30_IRQ_IF      BIT8  /**< 计数器计数值回到MCPWM_TH30中断标志位 */
#define CNT0_MCPWM_TH31_IRQ_IF      BIT9  /**< 计数器计数值回到MCPWM_TH31中断标志位 */
#define CNT0_MCPWM_TMR0_IRQ_IF      BIT10 /**< 计数器计数值回到MCPWM_TMR0中断标志位 */
#define CNT0_MCPWM_TMR1_IRQ_IF      BIT11 /**< 计数器计数值回到MCPWM_TMR1中断标志位 */
#define CNT0_MCPWM_TMR2_IRQ_IF      BIT12 /**< 计数器计数值回到MCPWM_TMR0中断标志位 */
#define CNT0_MCPWM_TMR3_IRQ_IF      BIT13 /**< 计数器计数值回到MCPWM_TMR1中断标志位 */
#define CNT0_MCPWM_SHADE_IRQ_IF     BIT14 /**< MCPWM_TH/MCPWM_TH00-MCPWM_TH31/\
MCPWM_TR0-MCPWM_TR3等寄存器更新到MCPWM实际运行系统中断使能 */

/* MCPWM时基1对应的中断标志位 */
#define CNT1_MCPWM_T0_IRQ_IF        BIT0  /**< 计数器计数值回到MCPWM_TH中断标志位 */
#define CNT1_MCPWM_T1_IRQ_IF        BIT1  /**< 计数器计数值回到0中断使能 */
#define CNT1_MCPWM_TH30_IRQ_IF      BIT8  /**< 计数器计数值回到MCPWM_TH30中断标志位 */
#define CNT1_MCPWM_TH31_IRQ_IF      BIT9  /**< 计数器计数值回到MCPWM_TH31中断标志位 */
#define CNT1_MCPWM_TMR2_IRQ_IF      BIT12 /**< 计数器计数值回到MCPWM_TMR0中断标志位 */
#define CNT1_MCPWM_TMR3_IRQ_IF      BIT13 /**< 计数器计数值回到MCPWM_TMR1中断标志位 */
#define CNT1_MCPWM_SHADE_IRQ_IF     BIT14 /**< MCPWM_TH/MCPWM_TH00-MCPWM_TH31/\
MCPWM_TR0-MCPWM_TR3等寄存器更新到MCPWM实际运行系统中断使能 */

/**< fail中断标志位和普通中断标志位用同一个函数实现读、清标志功能\
实际fail0-fail3事件对应MCPWM_EIF的BIT4-BIT7*/
#define CNT0_MCPWM_FAIL0_IRQ_IF          BIT19     /**< MCPWM_FAIL0中断使能 */
#define CNT0_MCPWM_FAIL1_IRQ_IF          BIT20     /**< MCPWM_FAIL1中断使能 */
#define CNT1_MCPWM_FAIL2_IRQ_IF          BIT21     /**< MCPWM_FAIL2中断使能 */
#define CNT1_MCPWM_FAIL3_IRQ_IF          BIT22     /**< MCPWM_FAIL3中断使能 */

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
