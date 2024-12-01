/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc03x_tmp.c\n
 * 文件标识： 无 \n
 * 内容摘要： 芯片内置温度传感器外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2015年11月5日 <td>1.0     <td>Howlet      <td>创建
 * </table>
 */
#include "lks32mc03x_tmp.h"

Stru_TempertureCof_Def m_TempertureCof;     /**< 温度传感器系数 */

/**
 *@brief @b 函数名称:   void TempSensor_Init(void)
 *@brief @b 功能描述:   温度传感器初始化
 *@see被引用内容：       无
 *@param输入参数：       无
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
		   TempSensor_Init(); //温度传感器初始化
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2020年11月5日 <td>1.0     <td>Howlet Li      <td>创建
 * </table>
 */
void TempSensor_Init(void)
{
    SYS_WR_PROTECT = 0x7a83;   /* 解除系统寄存器写保护 */
    SYS_AFE_REG0 |= BIT12;     /* 打开温度传感器开关 */
  
    m_TempertureCof.nCofA    = Read_Trim(0x000001C8);
    m_TempertureCof.nOffsetB = Read_Trim(0x000001CC);
}

/**
 *@brief @b 函数名称:   s16 GetCurrentTemperature(s16 ADC_value)
 *@brief @b 功能描述:   获取当前温度值
 *@see被引用内容：       无
 *@param输入参数：       ADC_value: ADC通道11为温度传感器，ADC采样结果值
 *@param输出参数：       无
 *@return返 回 值：      t_Temperture：当前温度值，单位：1个Lsb代表0.1度
 *@note其它说明：        ADC_value输入的ADC值不区分左右对齐，函数内已经进行ADC结果左右对齐判断
 *@warning              无
 *@par 示例代码：
 *@code
           s16 temp_value = 0;
		   temp_value = GetCurrentTemperature(ADC0_DATA0); //获取当前温度值,单位0.1度
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2020年11月5日 <td>1.0     <td>Howlet Li       <td>创建
 * </table>
 */
s16 GetCurrentTemperature(s16 ADC_value)
{
    s16 t_Temperture;  
    if(ADC->CFG & BIT10)
		{
        t_Temperture = (m_TempertureCof.nOffsetB - ((s32)m_TempertureCof.nCofA * ADC_value) / 1000);
		}
		else
		{
		    t_Temperture = (m_TempertureCof.nOffsetB - ((s32)m_TempertureCof.nCofA * (ADC_value >> 4)) / 1000);
		}

    return t_Temperture;
}
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
