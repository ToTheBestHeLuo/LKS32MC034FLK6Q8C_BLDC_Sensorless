/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc03x_sys.h\n
 * 文件标识： 无 \n
 * 内容摘要： sys驱动头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021年11月09日 <td>1.0     <td>YangZJ      <td>创建
 * </table>
 */
 
#ifndef __LKS32MC03x_SYS_H
#define __LKS32MC03x_SYS_H


/* Includes ------------------------------------------------------------------*/
#include "lks32mc03x_lib.h"

/** 
 *@brief 系统初始化结构体句柄，初始化时请定义该句柄，并用其它地址来传参
 */
typedef struct
{
	uint32_t PLL_SrcSel;                      /**< PLL信号输入源选择，RC时钟或外部晶体*/
	uint32_t PLL_DivSel;                      /**< 选择8个时钟周期中，哪个周期输出时钟*/
	uint32_t Clk_Sel;						  /**选择4MHz HS时钟或者PLL作为主时钟*/

	uint32_t Clk_DivI2C;                      /**< SPI I2C时钟分频*/
	uint32_t Clk_DivUART;                     /**< UART时钟分频*/
	uint32_t Clk_FEN;                         /**< 模块时钟使能*/

}SYS_InitTypeDef;

/**
 * 系统结构体基地址定义
 */
#ifndef MISC_BASE
#define MISC_BASE           0x40000000
#endif

/** 
 *@brief 低功耗时钟配置中间变量
 */
typedef struct
{
  uint32_t AFE_REG0_RECORD;
  uint32_t CLK_CFG_RECORD;
	
}WAKE_InitTypeDef;

/** 
 *@brief 低功耗IO唤醒电平枚举成员
 */
typedef enum
{
	WAKETRIG_LOW,  //输入IO低电平唤醒
	WAKETRIG_HIGH, //输入IO高电平唤醒
}enumWakeTrigLevel;

/*PLL信号输入源选择*/
#define SYS_PLLSRSEL_RCH        0x00          /**<使用4MHz RC时钟*/
#define SYS_PLLSRSEL_CRYSTAL    0x01          /**<使用晶体时钟*/

/* PLL 或者 HS 时钟选择*/
#define CLK_SEL_HS				0x00
#define CLK_SEL_PLL				0x01

/*SPI时钟分频*/
#define SYS_Clk_SPIDiv1          0     /**< SPI时钟分频，占时未使用*/
#define SYS_Clk_SPIDiv2          1     /**< SPI时钟分频，占时未使用*/
#define SYS_Clk_SPIDiv4          2     /**< SPI时钟分频，占时未使用*/
#define SYS_Clk_SPIDiv8          3     /**< SPI时钟分频，占时未使用*/

/*UART时钟分频*/
#define SYS_Clk_UARTDiv1         0     /**< UART时钟分频，占时未使用*/
#define SYS_Clk_UARTDiv2         1     /**< UART时钟分频，占时未使用*/
#define SYS_Clk_UARTDiv4         2     /**< UART时钟分频，占时未使用*/
#define SYS_Clk_UARTDiv8         3     /**< UART时钟分频，占时未使用*/

/*数字模块位定义*/
#define SYS_Module_I2C          BIT0   /**<I2C模块*/
#define SYS_Module_HALL         BIT1   /**<HALL模块*/
#define SYS_Module_UART         BIT2   /**<UART模块*/
#define SYS_Module_CMP          BIT3   /**<CMP模块*/
#define SYS_Module_MCPWM        BIT4   /**<MCPWM模块*/
#define SYS_Module_TIMER0       BIT5   /**<TIMER0模块*/
#define SYS_Module_TIMER1       BIT6   /**<TIMER1模块*/
#define SYS_Module_GPIO         BIT7   /**<GPIO模块*/
#define SYS_Module_DSP          BIT8   /**<DSP模块*/
#define SYS_Module_ADC          BIT9   /**<ADC模块*/
#define SYS_Module_SPI          BIT10  /**<SPI模块*/
#define SYS_Module_DMA          BIT11  /**<DMA模块*/

/*模拟模块定义*/
#define SYS_AnalogModule_ADC    BIT8   /**< ADC模块*/
#define SYS_AnalogModule_OPA    BIT9   /**< OPA模块*/
#define SYS_AnalogModule_BGP    BIT10  /**< BGP模块*/
#define SYS_AnalogModule_DAC    BIT11  /**< DAC模块*/
#define SYS_AnalogModule_TMP    BIT12  /**< TMP模块*/
#define SYS_AnalogModule_CMP0   BIT13  /**< CMP0模块*/
#define SYS_AnalogModule_CMP1   BIT14  /**< CMP1模块*/
#define SYS_AnalogModule_PLL    BIT15  /**< PLL模块*/

/*看门狗超时时间*/
#define SYS_WD_TimeOut2s  0         /**<看门狗超时时间2s复位*/
#define SYS_WD_TimeOut4s  1         /**<看门狗超时时间4s复位*/
#define SYS_WD_TimeOut8s  2         /**<看门狗超时时间8s复位*/
#define SYS_WD_TimeOut64s 3         /**<看门狗超时时间64s复位*/

/*复位信号源定义*/
#define SYS_RstSrc_LPOR        0x01     /**< 复位信号源：内部1.5V电源管理复位*/
#define SYS_RstSrc_HPOR        0x02     /**< 复位信号源：内部3.3V电源管理*/
#define SYS_RstSrc_KEYBOARD    0x04     /**< 复位信号源：按键复位*/
#define SYS_RstSrc_WDT         0x08     /**< 复位信号源：WDT复位*/

/*休眠唤醒间隔时间*/
#define SYS_WakeInterval_025s  0x00     /**< 休眠唤醒间隔时间0.25s*/  
#define SYS_WakeInterval_05s   0x01     /**< 休眠唤醒间隔时间0.5s*/
#define SYS_WakeInterval_1s    0x02     /**< 休眠唤醒间隔时间1s*/
#define SYS_WakeInterval_2s    0x03     /**< 休眠唤醒间隔时间2s*/
#define SYS_WakeInterval_4s    0x04     /**< 休眠唤醒间隔时间4s*/
#define SYS_WakeInterval_8s    0x05     /**< 休眠唤醒间隔时间8s*/
#define SYS_WakeInterval_16s   0x06     /**< 休眠唤醒间隔时间16s*/
#define SYS_WakeInterval_32s   0x07     /**< 休眠唤醒间隔时间32s*/

/*低功耗唤醒IO滤波*/
#define IOWK_FLT_EN    0x02 /**< 使能IO滤波*/
#define IOWK_FLT_DI    0x00 /**< 关闭IO滤波*/

/*低功耗唤醒IO选择*/
#define WAKEIO_P0_0	   BIT0  /**< P0.0 作为唤醒IO*/
#define WAKEIO_P0_2	   BIT1  /**< P0.2 作为唤醒IO*/
#define WAKEIO_P0_8	   BIT2  /**< P0.8 作为唤醒IO*/
#define WAKEIO_P0_9	   BIT3  /**< P0.9 作为唤醒IO*/
#define WAKEIO_P0_10   BIT4  /**< P0.10作为唤醒IO*/
#define WAKEIO_P1_5	   BIT5  /**< P1.5 作为唤醒IO*/
#define WAKEIO_P1_8	   BIT6  /**< P1.8 作为唤醒IO*/
#define WAKEIO_P1_9	   BIT7  /**< P1.9 作为唤醒IO*/

/*系统设置*/
void SYS_Init(SYS_InitTypeDef* SYS_InitStruct);         // sys模块初始化
void SYS_StructInit(SYS_InitTypeDef* SYS_InitStruct);   // SYS结构体初始化

/*复位源*/
void SYS_ClearRst(void);                                // SYS清除复位标志

/*控制8路时钟使能*/
void SYS_ModuleClockCmd(uint32_t,FuncState);            // 数字模块时钟使能和停止

/*控制模拟模块时钟使能*/
void SYS_AnalogModuleClockCmd(uint32_t, FuncState);     // 模拟模块使能和停止

/*软复位各模块*/
void SYS_SoftResetModule(uint32_t nModule);             // 模块软复位
void SYS_VolSelModule(uint32_t Vol);                    // 时钟校正
u32 SYS_GetRstSource(void);                             // 获得SYS复位源信号

/*休眠、唤醒*/
void SYS_EVTCLRSleep(void);
void SYS_FallSleep(void);
void SYS_SetWakeInterval(uint32_t rth , uint32_t wth , uint8_t ena);
void Switch2PLL(void);
void Switch2HRC(void);
void SetWakeIO(uint32_t wakeIO, enumWakeTrigLevel trigLevel, uint32_t flt , uint8_t ena);
/*DSP模块初始化*/
void DSP_Init(void);
#endif /*__lks32mc03x_SYS_H */

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
