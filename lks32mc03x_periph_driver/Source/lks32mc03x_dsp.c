
 /**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc03x_dsp.c\n
 * 文件标识： 无 \n
 * 内容摘要： DSP驱动程序 \n
 * 其它说明： 无 \n
 *@par 
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年4月18日 <td>1.0     <td>Zhu Jie   <td>创建
 * </table>
 */
#include "lks32mc03x_dsp.h"

static volatile u8 dsp_flg; /**< 标志位，用于判断程序是否被打断*/

 /**
 *@brief @b 函数名称:   void DSP_Cmd(FuncState state)
 *@brief @b 功能描述:   DSP使能和关闭
 *@see被引用内容：       SYS_ModuleClockCmd()
 *@param输入参数：       state：ENABLE：使能 ，DISABLE：失能
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
			DSP_Cmd(ENABLE);//使能DSP时钟
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2022年4月18日 <td>1.0     <td>Zhu Jie          <td>创建
 * </table>
 */
void DSP_Cmd(FuncState state)
{
   SYS_ModuleClockCmd(SYS_Module_DSP, state); /* DSP时钟使能 */
}

 /**
 *@brief @b 函数名称:   void DSP_CalcDivision(stru_DiviComponents * stru_Divi)
 *@brief @b 功能描述:   DSP除法运算
 *@see被引用内容：       stru_DiviComponents ，SYS_SoftResetModule()
 *@param输入参数：       .nDID,被除数   .nDIS除数
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        
                        1、除法10个总线周期完成 \n
                        2、被除数Dividend为32位大小，即范围是 -(2^31 - 1) ~ (2^31 - 1) \n
                        3、除数Divisor为16位大小，即范围是 -(2^15 - 1) ~ (2^15 - 1) \n
                        4、被除数不支持赋值为-2^31，除数不支持赋值为-2^15 \n
                        5、商Quotient为32位大小 \n
                        6、余数Remainder为16位大小
 *@warning              无
 *@par 示例代码：
 *@code    
            stru_DiviComponents DiviData; //定义除法函数计算结构体变量
            DiviData.Dividend = 100;//被除数赋值
            DiviData.Divisor = 10;  //除数赋值
			DSP_CalcDivision(&DiviData);
            除法的商储存位置：DiviData.Quotient
            除法的余数储存位置：DiviData.Remainder
  @endcode
 *@par 修改日志:      
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2022年4月18日 <td>1.0     <td>Zhu Jie          <td>创建
 * </table>
 */
void DSP_CalcDivision(stru_DiviComponents *stru_Divi)
{
	 u8 dsp_flg_old;
    do
    {
        dsp_flg++;
        dsp_flg_old = dsp_flg;
        SYS_SoftResetModule(SYS_Module_DSP);
        DSP_DID = stru_Divi->Dividend; /* 被除数寄存器赋值 */
		DSP_DIS = stru_Divi->Divisor;  /* 除数寄存器赋值   */

		stru_Divi->Quotient = DSP_QUO;  /* 取出商寄存器值 */
		stru_Divi->Remainder = DSP_REM;/* 取出余数寄存器值 */
    } while (dsp_flg_old != dsp_flg);  /* 防止DSP计算被打断 */
}

 /**
 *@brief @b 函数名称:   uint32_t DSP_GetSqrt(uint32_t Data)
 *@brief @b 功能描述:   DSP开平方函数
 *@see被引用内容：       SYS_SoftResetModule()
 *@param输入参数：       被开方数
 *@param输出参数：       无
 *@return返 回 值：      开方根
 *@note其它说明：        
                        1、开方8个总线周期完成 \n
                        2、被开方数Data为32位无符号数，即范围是(0 ~ (2^31)) \n
                        3、开方根sqrt(Data)为16位无符号数，即范围是(0 ~ (2^15)) \n
 *@warning              无
 *@par 示例代码：
 *@code    
            u16 GetSqrt_Value = 0;
            GetSqrt_Value = DSP_GetSqrt(100);//sqrt(100) 100开根号结果为10
  @endcode   
 *@par 修改日志:    
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2022年4月18日 <td>1.0     <td>Zhu Jie          <td>修改
 * </table>
 */
static volatile u8 dsp_flg2; /**< 标志位，用于判断程序是否被打断*/
uint32_t DSP_GetSqrt(uint32_t Data)
{
	  uint8_t dsp_flg_old;
      uint32_t  tdsp_sqrt;
    do
    {
        dsp_flg2++;
        dsp_flg_old = dsp_flg2;
        DSP_RAD = Data;  /*被开方寄存器赋值*/
       tdsp_sqrt = DSP_SQRT;
    } while (dsp_flg_old != dsp_flg2);  /* 防止DSP计算被打断 */
	 
   return tdsp_sqrt ;
}


/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
