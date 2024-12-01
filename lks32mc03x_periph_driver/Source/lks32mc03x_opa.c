/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc03x_opa.c\n
 * 文件标识： 无 \n
 * 内容摘要： OPA运放外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年04月20日 <td>1.0     <td>HuangMG      <td>创建
 * </table>
 */
#include "lks32mc03x_opa.h"

/**
 *@brief @b 函数名称:   void OPA_Init(enumOPA opa, OPA_InitTypeDef* OPA_InitStruct)
 *@brief @b 功能描述:   OPA初始化函数
 *@see被引用内容：       无
 *@param输入参数：       enumOPA opa , OPA_InitTypeDef *OPA_InitStruct 
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
    OPA_InitTypeDef OPA_InitStruct;
    OPA_StructInit(&OPA_InitStruct);//初始化结构体
    OPA_InitStruct.OPA_CLEna = ENABLE;       //使能OPA
    OPA_InitStruct.OPA_Gain = PGA_GAIN_4P25; //OPA内部增益电阻选择170：40
    OPA_InitStruct.OPA_B_EN = OPA0_IN_IP_B;  //OPA0使用 OPA0_IN_B/OPA0_IP_B 作为差分输入
    OPA_Init(OPA, &OPA_InitStruct);
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2022年04月20日 <td>1.0       <td>HuangMG           <td>创建
 * </table>
 */
void OPA_Init(enumOPA opa, OPA_InitTypeDef* OPA_InitStruct)
{
	uint32_t tmp1;
	SYS_WR_PROTECT = 0x7a83;   /* 解除系统寄存器写保护 */
	tmp1 = SYS_AFE_REG0;
	
	if (opa == OPA)
	{
		tmp1 &= ~(BIT0 | BIT1 | BIT5 | BIT9);
		tmp1 |= OPA_InitStruct->OPA_Gain;

		tmp1 |= OPA_InitStruct->OPA_B_EN << 5;
		
		tmp1 |= OPA_InitStruct->OPA_CLEna << 9;	
	}

	SYS_AFE_REG0 = tmp1;
	SYS_WR_PROTECT = 0x0;   /* 开启系统寄存器写保护 */
}

/**
 *@brief @b 函数名称:   void OPA_StructInit(OPA_InitTypeDef* OPA_InitStruct)
 *@brief @b 功能描述:   OPA结构体初始化
 *@see被引用内容：       无
 *@param输入参数：       OPA_InitTypeDef *OPA_InitStruct 
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
			    OPA_InitTypeDef OPA_InitStruct;
				OPA_StructInit(&OPA_InitStruct);       //初始化结构体
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2022年04月20日 <td>1.0       <td>HuangMG           <td>创建
 * </table>
 */
void OPA_StructInit(OPA_InitTypeDef* OPA_InitStruct)
{
   OPA_InitStruct->OPA_Gain = PGA_GAIN_4P25;
	 OPA_InitStruct->OPA_B_EN = OPA0_IN_IP;
   OPA_InitStruct->OPA_CLEna = DISABLE;
}

/**
 *@brief @b 函数名称:   void OPA_OUT(enumOPA opa, FuncState state)
 *@brief @b 功能描述:   OPA外部输出，输出到外部P0.7引脚
 *@see被引用内容：       无
 *@param输入参数：       enumOPA opa, FuncState state
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
			   OPA_OUT(OPA,ENABLE); //将OPA输出通过外部P0.7引脚送出
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2022年04月20日 <td>1.0       <td>HuangMG        <td>创建
 * </table>
 */
void OPA_OUT(enumOPA opa, FuncState state)
{
	SYS_WR_PROTECT = 0x7a83;   /* 解除系统寄存器写保护 */
  if(state != DISABLE)
	{
		if(opa == OPA)
		{		
		  SYS_AFE_REG0 |= 0x01<<2;
		}	
  }else{
		  SYS_AFE_REG0 &= ~(0x1<<2);
	}
	SYS_WR_PROTECT = 0x0;   /* 开启系统寄存器写保护 */
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
