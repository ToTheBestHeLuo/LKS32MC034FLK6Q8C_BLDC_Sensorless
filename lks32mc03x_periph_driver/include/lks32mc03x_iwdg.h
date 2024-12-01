 /**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc03x_IWDG.h\n
 * 文件标识： 无 \n
 * 内容摘要： 看门狗驱动头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021年11月09日 <td>1.0     <td>YangZJ      <td>创建
 * </table>
 */
#ifndef __LKS32MC03x_IWDG_H
#define __LKS32MC03x_IWDG_H

/* Includes ------------------------------------------------------------------*/
#include "lks32mc03x_lib.h"
/** 
 *@brief IWDG寄存器结构体句柄
 */
typedef struct
{
    __IO uint32_t PSW; /**<IWDG密码寄存器*/
    __IO uint32_t CFG; /**<IWDG配置寄存器*/
    __IO uint32_t CLR; /**<IWDG清零寄存器*/
    __IO uint32_t WTH; /**<IWDG计数器定时唤醒门限值寄存器*/
    __IO uint32_t RTH; /**<IWDG计数器超时复位门限值寄存器*/
    __IO uint32_t CNT; /**<IWDG计数器当前计数值寄存器*/
} IWDG_TypeDef;
/**
 * IWDG结构体基地址定义
 */
#ifndef IWDG
#define IWDG             ((IWDG_TypeDef *) AON_BASE)
#endif
/** 
 *@brief IWDG初始化结构体句柄
 */
typedef struct
{
    u32 DWK_EN;             /**< 深度休眠定时唤醒使能*/
    u32 WDG_EN;             /**< 独立看门狗使能*/
    u32 WTH;                /**< 看门狗定时唤醒时间（21位计数器，但低12恒位0）*/
    u32 RTH;                /**< 看门狗超时复位时间*/
}IWDG_InitTypeDef;


/** 
 *@brief 
 *函数名称：    u32 SECOND2IWDGCNT(float)
 *功能描述：    看门狗时间计算
 *输入参数：    时间，单位S
 *返 回 值：    看门狗计数值
 *其它说明：    RC时钟精度有限，全温度范围内误差±20% \n
                0x80为浮点转定点的取整
 */
#define SECOND2IWDGCNT(x)   ((u32)(64000*(float)x+0x800)&0x1ff000) /**<看门狗时间计算*/

void IWDG_Init(IWDG_InitTypeDef *);                 // 看门狗初始化
void IWDG_StrutInit(IWDG_InitTypeDef *);            // 看门狗配置结构体初始化
void IWDG_DISABLE(void);                            // 关闭看门狗
void IWDG_ENABLE(void);                             // 看门狗使能
void IWDG_Feed(void);                               // 看门狗喂狗
#endif /*__lks32mc03x_IWDG_H */
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
