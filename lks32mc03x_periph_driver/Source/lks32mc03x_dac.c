 /**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： LKS32MC03x_dac.c\n
 * 文件标识： 无 \n
 * 内容摘要： DAC外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年4月18日 <td>1.0     <td>Zhu Jie      <td>创建
 * </table>
 */

#include "lks32mc03x_dac.h"
#include "string.h"

DAC_CheckTypeDef Stru_DAC_CHECK;

 /**
 *@brief @b 函数名称:   void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct)
 *@brief @b 功能描述:   DAC结构体初始化
 *@see被调用函数：       无
 *@param输入参数：      ADC_InitTypeDef
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无   
 *@par 示例代码：
 *@code    
           DAC_StructInit DAC_InitStructure;
		   DAC_StructInit(&DAC_InitStructure); //初始化结构体
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年4月18日 <td>1.0     <td>Zhu Jie      <td>创建
 * </table>
 */
void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct)
{
    memset(DAC_InitStruct, 0, sizeof(DAC_InitTypeDef));
}

/**
 *@brief @b 函数名称:   void DAC_init(DAC_InitTypeDef* DAC_InitStruct)
 *@brief @b 功能描述:   DAC初始化函数
 *@see被调用函数：      SYS_AnalogModuleClockCmd()
 *@param输入参数：      DAC_InitTypeDef
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
			  DAC_InitTypeDef DAC_InitStructure;
			  DAC_StructInit(&DAC_InitStructure);
			  DAC_InitStructure.DACOUT_EN = DISABLE ;    // DAC输出至IO口
			  DAC_InitStructure.DAC_GAIN = DAC_RANGE_3V0；//ADC量程选择3.0V，只有B版本芯片支持4.8V量程
			  DAC_Init(&DAC_InitStructure);              // DAC初始化
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2022年4月18日 <td>1.0     <td>Zhu Jie      <td>创建
 * </table>
 */
void DAC_Init(DAC_InitTypeDef* DAC_InitStruct)
{
    SYS_AnalogModuleClockCmd(SYS_AnalogModule_DAC, ENABLE);  /* DAC 时钟使能 */
	
	  DAC_InitStruct->DAC_VERSION = REG32(0x40000004); /* 读取03芯片版本号 1 为A版本；2为B版本 ；3为C版本 */
		
		if ((DAC_InitStruct->DAC_VERSION) == 1)/* 芯片版本A 加载DAC 3.0V量程校正值 */
		{
			  Stru_DAC_CHECK.VersionAndDACGain = 2;/* A版本仅有3.0V量程 */
				Stru_DAC_CHECK.DAC_AMC = (Read_Trim(0x000001c0)&0xFFFF);
				Stru_DAC_CHECK.DAC_DC  = (Read_Trim(0x000001c4)&0xFFFF);
		}
		else if (DAC_InitStruct->DAC_VERSION == 2)/* 芯片版本B  */
		{
	      if(DAC_InitStruct->DAC_GAIN == DAC_RANGE_3V0)
				{
					  Stru_DAC_CHECK.VersionAndDACGain = 2;/* B版本有3.0V和4.8V两个量程 分别用2、3表示*/
				    Stru_DAC_CHECK.DAC_AMC = (Read_Trim(0x000001c0)&0xFFFF);
				    Stru_DAC_CHECK.DAC_DC  = (Read_Trim(0x000001c4)&0xFFFF);
				}
				else if(DAC_InitStruct->DAC_GAIN == DAC_RANGE_4V8)
				{
					  Stru_DAC_CHECK.VersionAndDACGain = 3;
				    Stru_DAC_CHECK.DAC_AMC = ((Read_Trim(0x000001c0)&0xFFFF0000) >> 16);
				    Stru_DAC_CHECK.DAC_DC  = ((Read_Trim(0x000001c4)&0xFFFF0000) >> 16);
				}
		}
		else
		{
	      if(DAC_InitStruct->DAC_GAIN == DAC_RANGE_1V2)
				{/* C版本有1.2V、3.0V和4.8V三个量程 分别用1、2、3表示*/
					  Stru_DAC_CHECK.VersionAndDACGain = 1;
				    Stru_DAC_CHECK.DAC_AMC = ((Read_Trim(0x0000018c)&0xFFFF0000) >> 16);
				    Stru_DAC_CHECK.DAC_DC  =  (Read_Trim(0x0000018c)&0xFFFF);
					  SYS_WR_PROTECT = 0x7a83;  /* 解锁寄存器写保护 */
					  SYS_AFE_REG2|=0x00008000;
					  SYS_WR_PROTECT = 0xffff;  /* 锁定寄存器写保护 */
				}
				else if(DAC_InitStruct->DAC_GAIN == DAC_RANGE_3V0)
				{
					  Stru_DAC_CHECK.VersionAndDACGain = 2;
				    Stru_DAC_CHECK.DAC_AMC = (Read_Trim(0x000001c0)&0xFFFF);
				    Stru_DAC_CHECK.DAC_DC  = (Read_Trim(0x000001c4)&0xFFFF);
				}
				else if(DAC_InitStruct->DAC_GAIN == DAC_RANGE_4V8)
				{
					  Stru_DAC_CHECK.VersionAndDACGain = 3;
				    Stru_DAC_CHECK.DAC_AMC = ((Read_Trim(0x000001c0)&0xFFFF0000) >> 16);
				    Stru_DAC_CHECK.DAC_DC  = ((Read_Trim(0x000001c4)&0xFFFF0000) >> 16);
				}
		}
}

 /**
 *@brief @b 函数名称:   void DAC_OutputValue(uint32_t DACValue)
 *@brief @b 功能描述:   DAC输出数字量数值设置
 *@see被调用函数：       无
 *@param输入参数：       DACValue:DAC输出电压对应数字量
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无   
 *@par 示例代码：
 *@code    
           DAC_OutputValue(128);//DAC输出128*3.0/256 = 1.5V
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年4月18日 <td>1.0     <td>Zhu Jie      <td>创建
 * </table>
 */

void DAC_OutputValue(uint32_t DACValue)
{
	  s16 temp1 = 0;
	
	  if(DACValue >=255) /* 限幅 */
		{
		    DACValue = 255;
		}
		temp1 = (s16)(DACValue * Stru_DAC_CHECK.DAC_AMC >> 9 )+ (s16)Stru_DAC_CHECK.DAC_DC;
		if(temp1 < 0)
		{
		    temp1 = 0;		
		}
		else if(temp1 > 255)
		{
		    temp1 = 255;
		}	
	  SYS_AFE_DAC = (u32)temp1;
}
/**
 *@brief @b 函数名称:   void DAC_OutputVoltage(uint32_t DACVoltage)
 *@brief @b 功能描述:   DAC输出模拟量数值设置
 *@see被调用函数：       无
 *@param输入参数：       DACVoltage为Q12格式,范围0~4096对应DAC输出0~3V
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        03xDAC量程为固定的3.0V  8位
                        与05x和08x不同，DAC数字量需要人为计算后再赋值给寄存器SYS_AFE_DAC
                        y = A * x + B，即DAC输出电压 = DAC_Gain * x + DAC_Offset;
                        校正值从地址中直接读取 分别对应0x000001c4 和 0x000001c0;
                        函数Read_Trim();在nvr.o中。
 *@warning              无   
 *@par 示例代码：
 *@code    
           DAC_OutputVoltage(BIT12 * 0.6);//DAC输出0.6V
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年4月18日 <td>1.0     <td>Zhu Jie      <td>创建
 * </table>
 */
void DAC_OutputVoltage(uint16_t DACVoltage)
{
	  s32 temp = 0;
	  u32 range = 0;
	  s16 temp1 = 0; 
    
	  if(Stru_DAC_CHECK.VersionAndDACGain == 1)/* 量程选择1.2V */
		{
		    range = (uint16_t)((1.0/1.2)*BIT8); /* BIT8 表示2^8 DAC为8位 */
		}
		else if(Stru_DAC_CHECK.VersionAndDACGain == 2)/* 量程选择3.0V */
		{
		    range = (uint16_t)((1.0/3.0)*BIT8); /* BIT8 表示2^8 DAC为8位 */
		}
    else if(Stru_DAC_CHECK.VersionAndDACGain == 3)/* 量程选择4.8V */
		{
		    range = (uint16_t)((1.0/4.8)*BIT8); /* BIT8 表示2^8 DAC为8位 */
		}
	  temp = (DACVoltage * range ) >> 12; 
	
	  if(temp >=255) /* 限幅 */
		{
		    temp = 255;
		}
		
		temp1 = (s16)((temp * Stru_DAC_CHECK.DAC_AMC )>> 9) + (s16)Stru_DAC_CHECK.DAC_DC; ;
		
		if(temp1 < 0)
		{
		  temp1 = 0;
		}
		else if(temp1 > 255)
		{
		  temp1 = 255;
		}		
	  SYS_AFE_DAC = temp1;
}

void DAC_Output(DAC_InitTypeDef* DAC_InitStruct)
{
	  SYS_WR_PROTECT = 0x7a83;  /* 解锁寄存器写保护 */
	
	  SYS_AFE_REG1 |= (DAC_InitStruct->DACOUT_EN << 1);/* DAC输出至IO口使能配置 */
	  
	  SYS_WR_PROTECT = 0xffff;  /* 锁定寄存器写保护 */
}
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
