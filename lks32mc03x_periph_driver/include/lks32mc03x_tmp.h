/**
 * @file 
 * @copyright (C)2018, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc03x_tmp.h\n
 * 文件标识： 无 \n
 * 内容摘要： 芯片内置温度传感器驱动头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021年08月25日 <td>1.0     <td>William Zhang      <td>创建
 * </table>
 */

#ifndef _LKS32MC03x_TMP_H_
#define _LKS32MC03x_TMP_H_


/* Includes ------------------------------------------------------------------*/
#include "lks32mc03x_lib.h"

/** 
 *@brief 芯片内置温度传感器初始化结构体句柄，初始化时请定义该句柄，并用其它地址来传参
 */
typedef struct
{
   u16 nCofA;      /**< 温度系数A*/
   u16 nOffsetB;   /**< 温度系数偏置*/
} Stru_TempertureCof_Def;


void TempSensor_Init(void);
s16 GetCurrentTemperature(s16 ADC_value);

#endif /*_CONNIE_TMP_H_ */



/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
