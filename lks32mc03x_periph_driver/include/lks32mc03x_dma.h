/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc03x_dma.h\n
 * 文件标识： 无 \n
 * 内容摘要： DMA外设驱动程序头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021年11月10日 <td>1.0     <td>Yangzj     <td>创建
 * </table>
 */
#ifndef __LKS32MC03x_DMA_H
#define __LKS32MC03x_DMA_H

#include "lks32mc03x_lib.h"

/** 
 *@brief DMA初始化结构体句柄，初始化时请定义该句柄，并用其它地址来传参
 */
typedef struct
{
    /** 
     * @brief DMA 中断使能
     * @see DMA_TCIE       
     */  
    u8   DMA_IRQ_EN;               /**< DMA 中断使能 */

    u8   DMA_RMODE;                /**<  多轮传输使能，DISABLE:单轮传输，ENABLE:多轮*/
    u8   DMA_CIRC;                 /**<  循环模式使能，ENABLE:使能 ， DISABLE:失能 */
    u8   DMA_SINC;                 /**<  源地址递增使能，ENABLE:使能 ， DISABLE:失能 */
    u8   DMA_DINC;                 /**<  目的地址递增使能，ENABLE:使能 ， DISABLE:失能*/
    /** 
     * @brief 源地址访问位宽
     * @see DMA_BYTE_TRANS    
     * @see DMA_HALFWORD_TRANS     
     * @see DMA_WORD_TRANS    
     */ 
    u8   DMA_SBTW;                 /* 源地址访问位宽， 0:byte, 1:half-word, 2:word */
    /** 
     * @brief 目的地址访问位宽
     * @see DMA_BYTE_TRANS    
     * @see DMA_HALFWORD_TRANS     
     * @see DMA_WORD_TRANS    
     */ 
    u8   DMA_DBTW;                 /* 目的地址访问位宽， 0:byte, 1:half-word, 2:word */
    /** 
     * @brief 通道 x 硬件 DMA 请求使能
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
    u32  DMA_SADR;                 /* DMA 通道 x 源地址 */
    u32  DMA_DADR;                 /* DMA 通道 x 目的地址 */
} DMA_InitTypeDef;
/** 
 *@brief DMA寄存器结构体句柄
 */
typedef struct
{
    __IO uint32_t DMA_CCR;     /**< DMA 通道配置寄存器*/
    __IO uint32_t DMA_REN;     /**< DMA 请求使能寄存器*/
    __IO uint32_t DMA_CTMS;    /**< DMA 传输次数寄存器*/
    __IO uint32_t DMA_SADR;    /**< DMA 源地址寄存器*/
    __IO uint32_t DMA_DADR;    /**< DMA 目的地址寄存器*/
} DMA_RegTypeDef;

/**
 * DAM通道0结构体基地址定义
 */
#ifndef DMA_CH0
#define DMA_CH0                   ((DMA_RegTypeDef *) DMA_BASE)
#endif
/**
 * DAM通道1结构体基地址定义
 */
#ifndef DMA_CH1
#define DMA_CH1                   ((DMA_RegTypeDef *) (DMA_BASE+0x20))
#endif
/**
 * DAM通道2结构体基地址定义
 */
#ifndef DMA_CH2
#define DMA_CH2                   ((DMA_RegTypeDef *) (DMA_BASE+0x40))
#endif
/**
 * DAM通道3结构体基地址定义
 */
#ifndef DMA_CH3
#define DMA_CH3                   ((DMA_RegTypeDef *) (DMA_BASE+0x60))
#endif

#define DMA_TCIE                   BIT0       /**< DMA中断使能定义，传输完成中断使能，高有效 */   
																  
#define CH3_FIF                    BIT3       /**< DMA通道 3 完成中断标志，高有效，写 1 清零 */
#define CH2_FIF                    BIT2       /**< DMA通道 2 完成中断标志，高有效，写 1 清零 */
#define CH1_FIF                    BIT1       /**< DMA通道 1 完成中断标志，高有效，写 1 清零 */
#define CH0_FIF                    BIT0       /**< DMA通道 0 完成中断标志，高有效，写 1 清零 */
																  
#define DMA_BYTE_TRANS             0          /**< DMA搬运数据位宽定义，访问位宽， 0:byte */
#define DMA_HALFWORD_TRANS         1          /**< DMA搬运数据位宽定义，访问位宽， 1:half-word */
#define DMA_WORD_TRANS             2          /**< DMA搬运数据位宽定义，访问位宽， 2:word */ 

#define DMA_SW_TRIG_REQ_EN         BIT15      /**< 触发DMA搬运源定义，软件触发 */
#define DMA_I2C_REQ_EN             BIT14      /**< 触发DMA搬运源定义，I2C DMA请求使能 */
#define DMA_GPIO_REQ_EN            BIT13      /**< 触发DMA搬运源定义，GPIO DMA请求使能 */ 
#define DMA_CMP_REQ_EN             BIT12      /**< 触发DMA搬运源定义，CMP DMA请求使能 */
#define DMA_SPI_TX_REQ_EN          BIT11      /**< 触发DMA搬运源定义，SPI TX DMA请求使能 */
#define DMA_SPI_RX_REQ_EN          BIT10      /**< 触发DMA搬运源定义，SPI RX DMA请求使能 */
#define DMA_UART_TX_REQ_EN         BIT7       /**< 触发DMA搬运源定义，UART TX DMA请求使能 */
#define DMA_UART_RX_REQ_EN         BIT6       /**< 触发DMA搬运源定义，UART RX DMA请求使能 */
#define DMA_TIMER1_REQ_EN          BIT5       /**< 触发DMA搬运源定义，TIMER1 DMA请求使能 */ 
#define DMA_TIMER0_REQ_EN          BIT4       /**< 触发DMA搬运源定义，TIMER0 DMA请求使能 */
#define DMA_HALL_REQ_EN            BIT2       /**< 触发DMA搬运源定义，HALL DMA请求使能 */
#define DMA_MCPWM_REQ_EN           BIT1       /**< 触发DMA搬运源定义，MCPWM DMA请求使能 */
#define DMA_ADC_REQ_EN             BIT0       /**< 触发DMA搬运源定义，ADC DMA请求使能 */


void DMA_Init(DMA_RegTypeDef *DMAx, DMA_InitTypeDef *DMAInitStruct);
void DMA_StructInit(DMA_InitTypeDef *DMAInitStruct);
uint32_t DMA_GetIRQFlag(u32 timer_if);
void DMA_ClearIRQFlag(uint32_t tempFlag);
void DMA_CHx_EN(DMA_RegTypeDef *DMAx,u32 Channel_EN,u32 set);

#endif

