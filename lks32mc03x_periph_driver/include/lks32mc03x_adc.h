/**
 * @file 
 * @copyright (C)2021, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc03x_adc.h\n
 * 文件标识： 无 \n
 * 内容摘要： ADC驱动头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021年10月14日 <td>1.0     <td>HMG      <td>创建
 * </table>
 */
#ifndef _LKS32MC03x_ADC_H_
#define _LKS32MC03x_ADC_H_

/** 
 *@brief ADC寄存器结构体句柄
 */
#include "lks32mc03x_lib.h"
typedef struct
{
    __IO uint32_t DAT0;   /**< ADC数据寄存器0 */
    __IO uint32_t DAT1;   /**< ADC数据寄存器1 */
    __IO uint32_t DAT2;   /**< ADC数据寄存器2 */
    __IO uint32_t DAT3;   /**< ADC数据寄存器3 */
    __IO uint32_t DAT4;   /**< ADC数据寄存器4 */
    __IO uint32_t DAT5;   /**< ADC数据寄存器5 */
    __IO uint32_t DAT6;   /**< ADC数据寄存器6 */
    __IO uint32_t DAT7;   /**< ADC数据寄存器7 */
    __IO uint32_t DAT8;   /**< ADC数据寄存器8 */
    __IO uint32_t DAT9;   /**< ADC数据寄存器9 */
	
    __IO uint32_t null0;    /**< 空闲 */
    __IO uint32_t null1;    /**< 空闲 */
	
    __IO uint32_t LTH;      /**< ADC模拟看门狗低阈值 */
    __IO uint32_t HTH;      /**< ADC模拟看门狗高阈值 */
    __IO uint32_t GEN;      /**< ADC模拟看门狗监测使能 */
	
    __IO uint32_t null2;    /**< 空闲 */
	
    __IO uint32_t CHN0;     /**< ADC采样信号来源寄存器0 */
    __IO uint32_t CHN1;     /**< ADC采样信号来源寄存器1 */
    __IO uint32_t CHN2;     /**< ADC采样信号来源寄存器2 */
		
    __IO uint32_t null3;    /**< 空闲 */

    __IO uint32_t CHNT;     /**< ADC每各段采样通道数配置寄存器 */

    __IO uint32_t CFG;      /**< ADC模式配置寄存器 */
    __IO uint32_t SWT;      /**< ADC软件触发寄存器 */

    __IO uint32_t null4;    /**< 空闲 */

    __IO uint32_t DC;       /**< ADC直流偏置寄存器 */
    __IO uint32_t AMC;      /**< ADC增益校正寄存器 */

    __IO uint32_t IE;       /**< ADC中断寄存器 */
		__IO uint32_t IF;       /**< ADC中断标志位寄存器 */

} ADC_TypeDef;

/**
 * ADC结构体基地址定义
 */
#ifndef  ADC
#define  ADC    ((ADC_TypeDef *) ADC_BASE)
#endif
/** 
 *@brief ADC初始化结构体句柄，初始化时请定义该句柄，并用其它地址来传参
 */
typedef struct
{
	  uint16_t ADC_SAMP_CLK;     /**< ADC 采样时间选择从5->36个ADC时钟周期可选*/
    /** 
     * @brief ADC中断使能 \n
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
     * @brief TADC触发来源选择。 \n
     * @see ADC_MCPWM_TRG  \n
     * @see ADC_UTIMER_TRG   \n  
     */ 
	  uint16_t SEL_En;       
	  uint16_t FSM_RESET;      /**< ADC 状态机复位控制信号  */

    /**
     * @brief 采样数据对齐方式 \n
     * @see ADC_LEFT_ALIGN  \n
     * @see ADC_RIGHT_ALIGN   \n  
     */ 
    uint16_t Align;        
    /**
     * @brief ADC 触发模式 单段、双段或四段 \n
     * @see ADC_1SEG_TRG  \n
     * @see ADC_2SEG_TRG  \n  
     * @see ADC_4SEG_TRG  
     */
    uint16_t Trigger_Mode; 
    /**
     * @brief Trigger_Cnt设置1，即需要触发ADC两次采进行一次ADC采样转换，设置范围0~15，表示需要1~16次触发事件
     */ 
    uint16_t Trigger_Cnt;  /**< 单段模式下触发下一次采样所需的触发事件数 */
    /**
     * @brief TADC触发ADC采样使能信号 \n
     * @see ADC_HARDWARE_T0_TRG  \n
     * @see ADC_HARDWARE_T1_TRG  \n  
     * @see ADC_HARDWARE_T2_TRG  \n
     * @see ADC_HARDWARE_T3_TRG  
     */
	  uint16_t Trigger_En;   
	  /**
     * @brief 使用该段采样对应段的采样个数不可设置为0，如果未用该段采样，采样个数可设置为0。
     */ 
    uint16_t FirSeg_Ch;    /**< 第一段采样的总通道数 */
    /**
     * @brief 使用该段采样对应段的采样个数不可设置为0，如果未用该段采样，采样个数可设置为0。
     */ 
    uint16_t SecSeg_Ch;    /**< 第二段采样的总通道数 */
    /**
     * @brief 使用该段采样对应段的采样个数不可设置为0，如果未用该段采样，采样个数可设置为0。
     */ 
    uint16_t ThrSeg_Ch;    /**< 第三段采样的总通道数 */
    /**
     * @brief 使用该段采样对应段的采样个数不可设置为0，如果未用该段采样，采样个数可设置为0。
     */ 
    uint16_t FouSeg_Ch;    /**< 第四段采样的总通道数 */
    /**
     * @brief ADC模拟看门狗对应位使能信号 \n
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
    uint16_t ADC_GEN_HTH;  /**< ADC模拟看门狗上阈值 */
    uint16_t ADC_GEN_LTH;  /**< ADC模拟看门狗下阈值 */
	  uint16_t REFOUT_EN;    /**< ADC REF输出使能*/
	  /**
     * @brief ADC量程选择 \n
     * @see ADC_RANGE_2V4 \n
     * @see ADC_RANGE_3V6   
     */    
	  uint16_t ADC_RANGE;    

} ADC_InitTypeDef;

#define ADC_MCPWM_TRG            (0x00)   /**< 选择MCPWM为ADC触发来源 */
#define ADC_UTIMER_TRG           (0x01)   /**< 选择UTIMER为ADC触发来源 */

#define ADC_RANGE_2V4            (0x01)    /*ADC量程2.4V*/
#define ADC_RANGE_3V6            (0x00)    /*ADC量程3.6V*/

#define ADC_1_TIMES_SAMPLE       ((u8)1) /**< ADC采样通道数1次采样 */
#define ADC_2_TIMES_SAMPLE       ((u8)2) /**< ADC采样通道数2次采样 */
#define ADC_3_TIMES_SAMPLE       ((u8)3) /**< ADC采样通道数3次采样 */
#define ADC_4_TIMES_SAMPLE       ((u8)4) /**< ADC采样通道数4次采样 */
#define ADC_5_TIMES_SAMPLE       ((u8)5) /**< ADC采样通道数5次采样 */
#define ADC_6_TIMES_SAMPLE       ((u8)6) /**< ADC采样通道数6次采样 */
#define ADC_7_TIMES_SAMPLE       ((u8)7) /**< ADC采样通道数7次采样 */
#define ADC_8_TIMES_SAMPLE       ((u8)8) /**< ADC采样通道数8次采样 */
#define ADC_9_TIMES_SAMPLE       ((u8)9) /**< ADC采样通道数9次采样 */

#define ADC_GEN_DAT0             ((uint16_t)0x01)  /**< DAT0看门狗监测使能 */
#define ADC_GEN_DAT1             ((uint16_t)0x02)  /**< DAT1看门狗监测使能 */
#define ADC_GEN_DAT2             ((uint16_t)0x04)  /**< DAT2看门狗监测使能 */
#define ADC_GEN_DAT3             ((uint16_t)0x08)  /**< DAT3看门狗监测使能 */
#define ADC_GEN_DAT4             ((uint16_t)0x10)  /**< DAT4看门狗监测使能 */
#define ADC_GEN_DAT5             ((uint16_t)0x20)  /**< DAT5看门狗监测使能 */
#define ADC_GEN_DAT6             ((uint16_t)0x40)  /**< DAT6看门狗监测使能 */
#define ADC_GEN_DAT7             ((uint16_t)0x80)  /**< DAT7看门狗监测使能 */
#define ADC_GEN_DAT8             ((uint16_t)0x100) /**< DAT8看门狗监测使能 */
#define ADC_GEN_DAT9             ((uint16_t)0x200) /**< DAT9看门狗监测使能 */

#define ADC_EOS0_IRQ_EN          ((uint16_t)0x01)     /**< 第一段扫描结束中断 */
#define ADC_EOS1_IRQ_EN          ((uint16_t)0x02)     /**< 第二段扫描结束中断 */
#define ADC_EOS2_IRQ_EN          ((uint16_t)0x04)     /**< 第三段扫描结束中断 */
#define ADC_EOS3_IRQ_EN          ((uint16_t)0x08)     /**< 第四段扫描结束中断 */
#define ADC_CONFLICT_IRQ_EN      ((uint16_t)0x10)     /**< 软件触发冲突 */
#define ADC_HERR_IRQ_EN          ((uint16_t)0x20)     /**< 硬件触发冲突 */
#define ADC_DAT0_OV_IRQ_EN       ((uint16_t)0x40)     /**< 超阈值中断 */

#define ADC_EOS0_DMA_EN          ((uint16_t)0x100)      /**< 第一段扫描结束DMA请求使能 */
#define ADC_EOS1_DMA_EN          ((uint16_t)0x200)      /**< 第二段扫描结束DMA请求使能 */
#define ADC_EOS2_DMA_EN          ((uint16_t)0x400)      /**< 第三段扫描结束DMA请求使能 */
#define ADC_EOS3_DMA_EN          ((uint16_t)0x800)      /**< 第四段扫描结束DMA请求使能 */
#define ADC_CONFLICT_DMA_EN      ((uint16_t)0x1000)     /**< 软件触发冲突DMA请求使能 */
#define ADC_HERR_DMA_EN          ((uint16_t)0x2000)     /**< 硬件触发冲突DMA请求使能 */
#define ADC_DAT0_OV_DMA_EN       ((uint16_t)0x4000)     /**< 超阈值DMA请求使能 */

#define ADC_ALL_IRQ_IF           ((uint16_t)0x7f)     /**< ADC全部中断标志位——可用于初始化 */
#define ADC_DAT0_OV_IRQ_IF       ((uint16_t)0x40)     /**< 超阈值中断 */
#define ADC_CONFLICT_IRQ_IF      ((uint16_t)0x20)     /**< 硬件触发冲突标志 */
#define ADC_HERR_IRQ_IF          ((uint16_t)0x10)     /**< 软件触发冲突标志 */
#define ADC_EOS3_IRQ_IF          ((uint16_t)0x08)     /**< 第四段扫描结束中断标志 */
#define ADC_EOS2_IRQ_IF          ((uint16_t)0x04)     /**< 第三段扫描结束中断标志*/
#define ADC_EOS1_IRQ_IF          ((uint16_t)0x02)     /**< 第二段扫描结束中断标志 */
#define ADC_EOS0_IRQ_IF          ((uint16_t)0x01)     /**< 第一段扫描结束中断标志 */

#define ADC_LEFT_ALIGN           ((uint16_t)0x0000)   /**< ADC数据输出左对齐 */
#define ADC_RIGHT_ALIGN          ((uint16_t)0x0001)   /**< ADC数据输出右对齐 */

#define ADC_DAT0_HTH             ((uint16_t)0x0001)   /**< ADC_DAT0_TH作为上阈值 */
#define ADC_DAT0_LTH             ((uint16_t)0x0000)   /**< ADC_DAT0_TH作为下阈值 */

#define ADC_MCPWM_SEL            ((uint16_t)0x0000)   /**< MCPWM 触发ADC采样 */
#define ADC_UTIMER_SEL           ((uint16_t)0x0001)   /**< UTIMER触发ADC采样 */

#define ADC_1SEG_TRG             ((uint16_t)0x00)  /**< ADC采用单段模式 */
#define ADC_2SEG_TRG             ((uint16_t)0x01)  /**< ADC采用2段模式 */
#define ADC_4SEG_TRG             ((uint16_t)0x03)  /**< ADC采用4段模式 */

#define ADC_CHANNEL_0            ((uint16_t)0x00)  /**< ADC通道0  OPA0_OUT*/
#define ADC_CHANNEL_1            ((uint16_t)0x01)  /**< ADC通道1  ADC_CH1*/
#define ADC_CHANNEL_2            ((uint16_t)0x02)  /**< ADC通道2  ADC_CH2*/
#define ADC_CHANNEL_3            ((uint16_t)0x03)  /**< ADC通道3  ADC_CH3*/
#define ADC_CHANNEL_4            ((uint16_t)0x04)  /**< ADC通道4  ADC_CH4*/
#define ADC_CHANNEL_5            ((uint16_t)0x05)  /**< ADC通道5  ADC_CH5*/
#define ADC_CHANNEL_6            ((uint16_t)0x06)  /**< ADC通道6  ADC_CH6*/
#define ADC_CHANNEL_7            ((uint16_t)0x07)  /**< ADC通道7  ADC_CH7*/
#define ADC_CHANNEL_8            ((uint16_t)0x08)  /**< ADC通道8  ADC_CH8/OPA1_OUT*/
#define ADC_CHANNEL_9            ((uint16_t)0x09)  /**< ADC通道9  ADC_CH9*/
#define ADC_CHANNEL_10           ((uint16_t)0x0a)  /**< ADC通道10 ADC_CH10*/
#define ADC_CHANNEL_11           ((uint16_t)0x0b)  /**< ADC通道11 温度传感器*/
#define ADC_CHANNEL_12           ((uint16_t)0x0c)  /**< ADC通道12 内部地*/
#define ADC_CHANNEL_13           ((uint16_t)0x0d)  /**< ADC通道13 2.4V基准源*/

#define ADC_HARDWARE_T0_TRG      ((uint16_t)0x01) /**< ADC采用硬件T0事件触发 */
#define ADC_HARDWARE_T1_TRG      ((uint16_t)0x02) /**< ADC采用硬件T1事件触发 */
#define ADC_HARDWARE_T2_TRG      ((uint16_t)0x04) /**< ADC采用硬件T2事件触发 */
#define ADC_HARDWARE_T3_TRG      ((uint16_t)0x08) /**< ADC采用硬件T3事件触发 */


/** ADC采样信号来源寄存器序号 */
typedef enum {
  CHN0 = 0, /**< 第0、1、2、3次采样信号对应信号来源寄存器序号*/
  CHN1,     /**< 第4、5、6、7次采样信号对应信号来源寄存器序号*/
  CHN2,     /**< 第8、9次采样信号对应信号来源寄存器序号*/
  } CHNx;

/** ADC数据寄存器序号 */
typedef enum {
  DAT0 = 0,  /**< 第0次采样信号对应结果寄存器序号*/
  DAT1,      /**< 第1次采样信号对应结果寄存器序号*/
  DAT2,      /**< 第2次采样信号对应结果寄存器序号*/
  DAT3,      /**< 第3次采样信号对应结果寄存器序号*/
  DAT4,      /**< 第4次采样信号对应结果寄存器序号*/
  DAT5,      /**< 第5次采样信号对应结果寄存器序号*/
  DAT6,      /**< 第6次采样信号对应结果寄存器序号*/
  DAT7,      /**< 第7次采样信号对应结果寄存器序号*/
  DAT8,      /**< 第8次采样信号对应结果寄存器序号*/
  DAT9,      /**< 第9次采样信号对应结果寄存器序号*/
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
