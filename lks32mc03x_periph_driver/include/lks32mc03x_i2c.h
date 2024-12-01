/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc03x_i2c.h\n
 * 文件标识： 无 \n
 * 内容摘要： I2C驱动头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021年11月09日 <td>1.0     <td>YangZJ     <td>创建
 * </table>
 */
#ifndef __LKS32MC03x_I2C_H
#define __LKS32MC03x_I2C_H
/* Includes ------------------------------------------------------------------*/
#include "lks32mc03x_lib.h"

//I2C_BUS_STATE   I2C总线状态
#define I2C_BUS_STATE_STT_ERR     BIT7   /**< 总线错误 */
#define I2C_BUS_STATE_LOST_ARB    BIT6   /**< 总线仲裁丢失 */
#define I2C_BUS_STATE_STOP_EVT    BIT5   /**< STOP事件记录 */

#define I2C_BUS_STATE_ADDR_DATA   BIT3   /**< 正在传输地址数据 */

#define I2C_BUS_STATE_RX_ACK      BIT1   /**< 接收到ACK响应 */
#define I2C_BUS_STATE_Done        BIT0   /**< 传输完成 */


/** 
 *@brief I2C寄存器结构体句柄
 */
typedef struct
{
    __IO uint32_t ADDR;   /**< I2C地址寄存器 */
    __IO uint32_t CFG;    /**< I2C配置寄存器*/
    __IO uint32_t SCR;    /**< I2C状态寄存器*/
    __IO uint32_t DATA;   /**< I2C数据寄存器*/
    __IO uint32_t MSCR;   /**< I2C主模式寄存器*/
    __IO uint32_t BCR;    /**< I2C传输控制寄存器*/
    __IO uint32_t BSIZE;  /**< I2C传输长度寄存器*/
} I2C_TypeDef;


/**
 * I2C结构体基地址定义
 */
#ifndef I2C
#define I2C             ((I2C_TypeDef *) I2C_BASE)
#endif

/** 
 *@brief I2C初始化结构体句柄，初始化时请定义该句柄，并用其它地址来传参
 */
typedef struct
{
    u32 ADRCMP          ;   /**<   I2C 硬件地址比较使能开关，只有在 DMA 模式下开启才有效*/
    u32 MST_MODE        ;   /**<   I2C 主模式使能；ENABLE:使能，DISABLE:失能*/
    u32 SLV_MODE        ;   /**<   I2C 从模式使能；ENABLE:使能，DISABLE:失能*/
    u32 DMA             ;   /**<   I2C DMA传输使能；ENABLE:使能，DISABLE:失能*/
    u32 BaudRate        ;   /**<   I2C 波特率*/
    u32 IE              ;   /**<   I2C 中断使能；ENABLE:使能，DISABLE:失能*/
    u32 TC_IE           ;   /**<   I2C 数据传输完成中断使能；ENABLE:使能，DISABLE:失能*/
    u32 BUS_ERR_IE      ;   /**<   I2C 总线错误事件中断使能；ENABLE:使能，DISABLE:失能*/
    u32 STOP_IE         ;   /**<   I2C STOP 事件中断使能；ENABLE:使能，DISABLE:失能*/
    u32 BURST_NACK      ;   /**<   I2C 传输，NACK 事件中断使能；ENABLE:使能，DISABLE:失能*/
    u32 BURST_ADDR_CMP  ;   /**<   I2C 传输，硬件地址匹配中断使能；ENABLE:使能，DISABLE:失能*/
}I2C_InitTypeDef;

void I2C_Init(I2C_InitTypeDef *);        // I2C初始化
void I2C_StructInit(I2C_InitTypeDef *);   // I2C配置结构体初始化

u8 Read_I2c_Bus_State(u16);            // 读I2C总线状态
void Clear_I2c_Bus_State(u16);          // I2C总线状态复位

// i2c&dma发送&接收
void i2c_dma_rx(u8 addr, u8 *data, u8 len);
void i2c_dma_tx(u8 addr, u8 *data, u8 len);
void i2c_dma_init(void);
void i2c_dma_state_over(void);
#endif /*__lks32mc03x_I2C_H */
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
