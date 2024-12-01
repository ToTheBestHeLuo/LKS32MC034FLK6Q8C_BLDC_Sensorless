
/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc03x_dsp.h\n
 * 文件标识： 无 \n
 * 内容摘要： DSP驱动头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年04月18日 <td>1.0     <td> Zhu Jie      <td>创建
 * </table>
 */
 
#ifndef __LKS32MC03x_DSP_H
#define __LKS32MC03x_DSP_H

/* Includes ------------------------------------------------------------------*/
#include "lks32mc03x_lib.h"

/** 
 *@brief 除法运算结构体句柄
 */
typedef struct
{
	  s32 Dividend;     /**< 被除数 */
	  s32 Divisor;      /**< 除数   */
    s32 Quotient;       /**< 商     */
    s32 Remainder;      /**< 余数   */
} stru_DiviComponents;

void DSP_Cmd(FuncState state);                          /* DSP使能和关闭 */
void DSP_CalcDivision(stru_DiviComponents *stru_Divi);  /* DSP除法运算 */
uint32_t DSP_GetSqrt(u32 Data); /*DSP取得开方根 sprt(Data)*/

#endif 

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
