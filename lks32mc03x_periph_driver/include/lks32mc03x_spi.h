 /**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc03x_spi.h\n
 * 文件标识： 无 \n
 * 内容摘要： SPI驱动头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021年11月10日   <td>1.0     <td>Yangzj       <td>创建
 * </table>
 */
 
#ifndef __LKS32MC03x_SPI_H
#define __LKS32MC03x_SPI_H


/* Includes ------------------------------------------------------------------*/
#include "lks32mc03x_lib.h"

 /** 
 *@brief SPI模式配置枚举
 */
typedef enum
{
   SPI_Master = 0x01, /**< SPI主模式 */
   SPI_Slave  = 0x00  /**< SPI从模式 */
}SPI_Mode;

 /** 
 *@brief SPI工作模式配置枚举
 */
typedef enum
{
   SPI_Full    = 0x0, /**< SPI全双工 */
   SPI_Half_Tx = 0x2, /**< SPI半双工仅发送 */
   SPI_Half_Rx = 0x3  /**< SPI半双工仅接收 */
}SPI_Duplex;

/** 
 *@brief SPI寄存器结构体句柄
 */
typedef struct
{
   __IO uint32_t CFG;     /**< SPI控制寄存器 */
   __IO uint32_t IE;      /**< SPI中断寄存器 */
   __IO uint32_t BAUD;    /**< SPI波特率控制寄存器 */
   __IO uint32_t TX_DATA; /**< SPI发送数据寄存器 */
   __IO uint32_t RX_DATA; /**< SPI接收数据寄存器 */
   __IO uint32_t SIZE;    /**< SPI传输数据长度寄存器 */
}SPI_TypeDef;

/**
 * SPI结构体基地址定义
 */
#ifndef   SPI
#define   SPI     ((SPI_TypeDef *) SPI_BASE)
#endif

 /** 
 *@brief SPI初始化结构体句柄，初始化时请定义该句柄，并用其它地址来传参
 */
typedef struct
{
   /** 
    * @brief 全双工、半双工工作模式选择：0，全双工；2，半双工仅发送；3，半双工仅接收  \n
    * @see SPI_Duplex     
    */ 
   SPI_Duplex Duplex;       /**< 半双工模式设置*/
   uint8_t    CS;           /**< SPI 从设备下，片选信号来源。0:Slave 模式下，片选信号恒为有效值 1:Slave 模式下，片选信号来自 Master 设备*/
   /** 
    * @brief 主从模式选择：0，从模式；1，主模式  \n
    * @see SPI_Mode     
    */
   SPI_Mode   Mode;         /**< SPI 主从模式选择。*/
   uint8_t    CPHA;         /**< SPI 相位选择。*/
   uint8_t    CPOL;         /**< SPI 极性选择。*/
   uint8_t    ENDIAN;       /**< SPI 模块传输顺序。*/
   uint8_t    EN;           /**< SPI Enable Signal, 0: disable;1: enable*/
   /** 
   * @brief SPI中断使能：DISABLE：关闭所以中断  \n
   * @see SPI_IRQEna_Enable     \n  
   * @see SPI_IRQEna_TranDone   \n  
   * @see SPI_IRQEna_SSErr      \n  
   * @see SPI_IRQEna_DataOver    
   */
   uint8_t    IRQEna;       /**< SPI 中断使能。*/
   uint8_t    TRANS_TRIG;   /**< 传输触发选择。*/

   uint8_t    TRANS_MODE;   /**< SPI 数据搬移方式。0 DMA 方式。*/
   uint8_t    BAUD;         /**< SPI 传输波特率配置, SPI 传输速度 = 系统时钟 / (2*(BAUD + 1)),最小为3 */

   uint8_t    BITSIZE;      /**< SPI传输数据字节长度寄存器。8-16 */
}SPI_InitTypeDef;

#define SPI_FIRSTSEND_LSB 1    /**< 低位先传 */
#define SPI_FIRSTSEND_MSB 0    /**< 高位先传 */

#define SPI_DMA_ENABLE     0   /**< 使能DMA搬运 */
#define SPI_DMA_DISABLE    1   /**< 禁止DMA搬运 */

#define SPI_DMA_CARRY      0   /**< SPI由DMA搬运 */
#define SPI_MCU_CARRY      1   /**< SPI由MCU搬运 */

/*中断使能定义*/
#define SPI_IRQEna_Enable              BIT7            /**<中断使能定义，SPI中断使能 */
#define SPI_IRQEna_TranDone            BIT6            /**<中断使能定义，传输完成中断 */
#define SPI_IRQEna_SSErr               BIT5            /**<中断使能定义，传输异常事件中断 */
#define SPI_IRQEna_DataOver            BIT4            /**<中断使能定义，传输溢出事件中断 */

/*中断标志定义*/
#define SPI_IF_TranDone                BIT2            /**<中断标志定义，传输完成中断标志位 */
#define SPI_IF_SSErr                   BIT1            /**<中断标志定义，传输异常中断标志位 */
#define SPI_IF_DataOver                BIT0            /**<中断标志定义，传输溢出中断标志位 */

void SPI_Init(SPI_TypeDef *SPIx, SPI_InitTypeDef *SPI_InitStruct);
void SPI_StructInit(SPI_InitTypeDef *SPI_InitStruct);

uint8_t SPI_GetIRQFlag(SPI_TypeDef *SPIx,u8 IRQ_Flag);
void SPI_ClearIRQFlag(SPI_TypeDef *SPIx,u8 IRQ_Flag);

void    SPI_SendData(SPI_TypeDef *SPIx, uint8_t n);
uint8_t SPI_ReadData(SPI_TypeDef *SPIx);
#endif /*__lks32mc03x_SPI_H */

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
