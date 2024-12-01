/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc03x_hall.h\n
 * 文件标识： 无 \n
 * 内容摘要： HALL驱动头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021年10月14日    <td>1.0     <td>HMG     <td>创建
 * </table>
 */
#ifndef __LKS32MC03x_HALL_H
#define __LKS32MC03x_HALL_H

/* Includes ------------------------------------------------------------------*/
#include "lks32mc03x_lib.h"

/** 
 *@brief HALL寄存器结构体句柄
 */
typedef struct
{
   __IO uint32_t CFG;    /**< HALL 模块配置寄存器 */ 
   __IO uint32_t INFO;   /**< HALL 模块信息寄存器 */ 
   __IO uint32_t WIDTH;  /**< HALL 宽度计数值寄存器*/ 
   __IO uint32_t TH;     /**< HALL 模块计数器门限值寄存器*/
   __IO uint32_t CNT;    /**< HALL 计数寄存器*/ 

} HALL_TypeDef;

/**
 * HALL结构体基地址定义
 */
#ifndef  HALL
#define  HALL        ((HALL_TypeDef *) HALL_BASE)
#endif

/** 
 *@brief HALL初始化结构体句柄，初始化时请定义该句柄，并用其它地址来传参
 */
typedef struct
{
   uint16_t FilterLen;       /**<滤波长度,0对应长度1,1023对应长度1024滤波长度*/
   uint8_t ClockDivision;    /**<分频 0~3:/1 /2 /4 /8*/
   uint8_t Filter75_Ena;     /**<使能第一级7/5滤波,ENABLE：使能 DISABLE：失能*/
   uint8_t HALL_Ena;         /**<使能HALL,ENABLE：使能 DISABLE：失能*/
   uint8_t HALL_CHGDMA_Ena;  /**<HALL信号变化DMA请求使能,ENABLE：使能 DISABLE：失能*/
   uint8_t HALL_OVDMA_Ena;   /**<HALL计数器溢出DMA请求使能,ENABLE：使能 DISABLE：失能*/
   uint8_t Capture_IRQ_Ena;  /**<HALL信号变化中断使能,ENABLE：使能 DISABLE：失能*/
   uint8_t OverFlow_IRQ_Ena; /**<HALL计数器溢出中断使能,ENABLE：使能 DISABLE：失能*/
   uint32_t CountTH;         /**<HALL计数器门限值*/
   uint8_t softIE;           /**<软件中断使能 */
} HALL_InitTypeDef;

#define HALL_CLK_DIV1 ((uint32_t)0x00) /**< HALL时钟为主时钟1分频*/
#define HALL_CLK_DIV2 ((uint32_t)0x01) /**< HALL时钟为主时钟2分频*/
#define HALL_CLK_DIV4 ((uint32_t)0x02) /**< HALL时钟为主时钟4分频*/
#define HALL_CLK_DIV8 ((uint32_t)0x03) /**< HALL时钟为主时钟8分频*/
/*HALL中断使能和标志定义*/
#define HALL_CAPTURE_EVENT ((uint32_t)0x00010000)   /**< HALL信号变化中断*/
#define HALL_OVERFLOW_EVENT ((uint32_t)0x00020000)  /**< HALL信号溢出中断*/

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
