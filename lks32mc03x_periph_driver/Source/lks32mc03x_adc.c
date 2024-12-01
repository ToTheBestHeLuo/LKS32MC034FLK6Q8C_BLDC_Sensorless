/**
 * @file
 * @copyright (C)2021, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc03x_adc.c \n
 * 文件标识： 无 \n
 * 内容摘要： ADC外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021年10月14日 <td>1.0     <td>HMG      <td>创建
 * </table>
 */
#include "lks32mc03x_adc.h"

/**
 *@brief @b 函数名称:   void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct)
 *@brief @b 功能描述:   ADC初始化函数
 *@see被引用内容：      SYS_AnalogModuleClockCmd()
 *@param输入参数：      ADCx：ADC, ADC_InitTypeDef *ADC_InitTypeDef
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
            ADC_InitTypeDef ADC_InitStructure;
            ADC_StructInit(&ADC_InitStructure);                            // ADC初始化结构体
            ADC_InitStructure.Align = ADC_LEFT_ALIGN;                      // ADC数据输出左对齐
            ADC_InitStructure.Trigger_Mode = ADC_1SEG_TRG;                 // 设置ADC转换模式为1段式采样 
            ADC_InitStructure.FirSeg_Ch = ADC_2_TIMES_SAMPLE;              // 第一段共采样2个通道 
            ADC_InitStructure.SecSeg_Ch = 0;                               // 第二段共采样0个通道 
            ADC_InitStructure.ThrSeg_Ch = 0;                               // 第三段共采样0个通道 
            ADC_InitStructure.FouSeg_Ch = 0;                               // 第四段共采样0个通道 
            ADC_InitStructure.Trigger_Cnt = 0;                             // 单段触发模式下触发一次采样所需要的事件数:0~15 0表示需要一次触发，15表示需要16次
            ADC_InitStructure.ADC_RANGE = ADC_RANGE_3V6;                   // ADC量程选择  
            ADC_InitStructure.Trigger_En = ADC_HARDWARE_T0_TRG;            // 开启T0和T1硬件触发事件 
            ADC_InitStructure.SEL_En = ADC_UTIMER_SEL;                     // MCPWM触发ADC采样 
            ADC_InitStructure.ADC_SAMP_CLK = 20;                           // 设置采样时间为20个ADC时钟周期 范围4--35
            ADC_InitStructure.IE = ADC_EOS0_IRQ_EN ;                       // 开启第一段中断 
            // ADC模拟看门狗           
            ADC_InitStructure.ADC_GEN_En  = DISABLE ;                      // 看门狗监测禁止 
            ADC_InitStructure.ADC_GEN_HTH = 0;                             // ADC模拟看门狗上阈值 
            ADC_InitStructure.ADC_GEN_LTH = 0;                             // ADC模拟看门狗下阈值 
            ADC_InitStructure.REFOUT_EN = DISABLE;                         // ADC REF输出不使能
            ADC_Init(ADC, &ADC_InitStructure);
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021年10月14日 <td>1.0     <td>HungMG        <td>创建
 * </table>
 */
void ADC_Init(ADC_TypeDef *ADCx, ADC_InitTypeDef *ADC_InitStruct)
{

    uint16_t t_reg;

    SYS_AnalogModuleClockCmd(SYS_AnalogModule_ADC, ENABLE); // ADC模块使能

    ADCx->IE = ADC_InitStruct->IE;

    t_reg = (ADC_InitStruct->Align << 10) |
            (ADC_InitStruct->Trigger_En) |
            (ADC_InitStruct->SEL_En << 12) |
            (ADC_InitStruct->FSM_RESET << 11) |
            (ADC_InitStruct->Trigger_Cnt << 4) |
            (ADC_InitStruct->Trigger_Mode << 8);
    ADCx->CFG = t_reg;

    ADCx->CHNT = ADC_InitStruct->FirSeg_Ch |
                 (ADC_InitStruct->SecSeg_Ch << 4) |
                 (ADC_InitStruct->ThrSeg_Ch << 8) |
                 (ADC_InitStruct->FouSeg_Ch << 12);

    ADC_LTH = ADC_InitStruct->ADC_GEN_LTH;

    ADC_HTH = ADC_InitStruct->ADC_GEN_HTH;

    ADC_GEN = ADC_InitStruct->ADC_GEN_En;

    SYS_WR_PROTECT = 0x7a83; // 解除系统寄存器写保护 

    if (ADC_InitStruct->ADC_SAMP_CLK > 4)
    {
        t_reg = ADC_InitStruct->ADC_SAMP_CLK - 4;
    }
    else
    {
        t_reg = 0;
    }

    if (ADC_InitStruct->ADC_RANGE & 0x01) //2.4V量程
    {
        SYS_AFE_REG0 |= 0x01 << 6;        //ADC量程选择
        ADC_AMC = Read_Trim(0x000001AC);  //ADC_AMC1校正值，1倍增益
        ADC_DC = Read_Trim(0x000001A8);   //ADC_DC1校正值 ，1倍增益
    } 
    else 
    {                                     //3.6V量程
        SYS_AFE_REG0 &= ~(0x01 << 6);     //ADC量程选择
        ADC_AMC = Read_Trim(0x000001A4);  //ADC_AMC0校正值，2/3倍增益
        ADC_DC = Read_Trim(0x000001A0);   //ADC_DC0校正值 ，2/3倍增益
    }
    SYS_AFE_REG2 = (t_reg << 8);          //设置ADC采样时间
    SYS_AFE_REG1 |= ADC_InitStruct->REFOUT_EN << 6;

    SYS_WR_PROTECT = 0;                   // 开启系统寄存器写保护 
}
/**
 *@brief @b 函数名称:   void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct)
 *@brief @b 功能描述:   ADC结构体初始化
 *@see被引用内容：      无
 *@param输入参数：      ADC_InitTypeDef *ADC_InitStruct
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
		   ADC_InitTypeDef ADC_InitStructure;
		   ADC_StructInit(&ADC_InitStructure); //初始化结构体
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021年10月14日 <td>1.0     <td>HMG     <td>创建
 * </table>
 */

void ADC_StructInit(ADC_InitTypeDef *ADC_InitStruct)
{
    ADC_InitStruct->ADC_SAMP_CLK = 0;
    ADC_InitStruct->IE = 0;
    ADC_InitStruct->SEL_En = 0;
    ADC_InitStruct->FSM_RESET = 0;
    ADC_InitStruct->Align = 0;
    ADC_InitStruct->Trigger_Mode = 0;
    ADC_InitStruct->Trigger_Cnt = 0;
    ADC_InitStruct->Trigger_En = 0;

    ADC_InitStruct->FirSeg_Ch = 0;
    ADC_InitStruct->SecSeg_Ch = 0;
    ADC_InitStruct->ThrSeg_Ch = 0;
    ADC_InitStruct->FouSeg_Ch = 0;

    ADC_InitStruct->ADC_GEN_En = 0;
    ADC_InitStruct->ADC_GEN_HTH = 0;
    ADC_InitStruct->ADC_GEN_LTH = 0;
    ADC_InitStruct->REFOUT_EN = 0;

    ADC_InitStruct->ADC_RANGE = 0;
}
/**
 *@brief @b 函数名称:   void ADC_ClearIRQFlag(ADC_TypeDef* ADCx, uint16_t INT_flag)
 *@brief @b 功能描述:   ADC中断标志位清零
 *@see被引用内容：      无
 *@param输入参数：
 * <table>              <tr><td>ADCx：                   <td> ADC
 *                      <tr><td>INT_flag:                <td> ADC中断标志
 * 						<tr><th>ADC_DAT0_OV_IRQ_IF       <td>超阈值中断标志位 \n
 * 						<tr><th>ADC_CONFLICT_IRQ_IF      <td>硬件触发冲突标志 \n
 * 						<tr><th>ADC_HERR_IRQ_IF          <td>软件触发冲突标志 \n
 * 						<tr><th>ADC_EOS3_IRQ_IF          <td>第四段扫描结束中断标志 \n
 * 						<tr><th>ADC_EOS2_IRQ_IF          <td>第三段扫描结束中断标志 \n
 * 						<tr><th>ADC_EOS1_IRQ_IF          <td>第二段扫描结束中断标志 \n
 * 						<tr><th>ADC_EOS0_IRQ_IF          <td>第一段扫描结束中断标志 \n
 * 						<tr><th>ADC_ALL_IRQ_IF           <td>ADC全部中断标志位——可用于初始化 \n
 * </table>
 *@param输出参数：   无
 *@return返 回 值：  无
 *@note其它说明：    写1清零
 *@warning          无
 *@par 示例代码：
 *@code
            if(ADC_GetIRQFlag(ADC,ADC_EOS0_IRQ_IF))           // 第一段采样完成中断
            {
                ADC_ClearIRQFlag(ADC,ADC_EOS0_IRQ_IF);          // 清除第一段采样完成中断标志位
            }
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年04月20日 <td>1.0     <td>Zhu Jie      <td>创建
 * </table>
 */
void ADC_ClearIRQFlag(ADC_TypeDef *ADCx, uint16_t INT_flag)
{
    ADCx->IF = INT_flag;
}

/**
 *@brief @b 函数名称:   uint16_t ADC_GetIRQFlag(ADC_TypeDef* ADCx, uint16_t INT_flag)
 *@brief @b 功能描述:   获取ADC中断标志
 *@see被引用内容：      无
 *@param输入参数：
 * <table>              <tr><td>ADCx：                   <td> ADC
 *                      <tr><td>INT_flag:                <td> ADC中断标志
 * 						<tr><th>ADC_DAT0_OV_IRQ_IF       <td>超阈值中断标志位 \n
 * 						<tr><th>ADC_CONFLICT_IRQ_IF      <td>硬件触发冲突标志 \n
 * 						<tr><th>ADC_HERR_IRQ_IF          <td>软件触发冲突标志 \n
 * 						<tr><th>ADC_EOS3_IRQ_IF          <td>第四段扫描结束中断标志 \n
 * 						<tr><th>ADC_EOS2_IRQ_IF          <td>第三段扫描结束中断标志 \n
 * 						<tr><th>ADC_EOS1_IRQ_IF          <td>第二段扫描结束中断标志 \n
 * 						<tr><th>ADC_EOS0_IRQ_IF          <td>第一段扫描结束中断标志 \n
 * 						<tr><th>ADC_ALL_IRQ_IF           <td>ADC全部中断标志位——可用于初始化 \n
 * </table>
 *@param输出参数：   无
 *@return返 回 值：  读对应标志位是否为1，1为置位，0为未置位
 *@note其它说明：    无
 *@warning          只有对应中断使能后，改为才能读取，如果对应中断未使能，读取结果一直为0
 *@par 示例代码：
 *@code
		    if(ADC_GetIRQFlag(ADC,ADC_EOS0_IRQ_IF))           // 第一段采样完成中断
            {
                ADC_ClearIRQFlag(ADC,ADC_EOS0_IRQ_IF);          // 清除第一段采样完成中断标志位
            }
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年04月20日 <td>1.0     <td>Zhu Jie      <td>创建
 * </table>
 */
u16 ADC_GetIRQFlag(ADC_TypeDef *ADCx, uint16_t INT_flag)
{
    u8 ADCIRQFlag = 0;
    if (ADCx->IF & INT_flag)
    {
        ADCIRQFlag = 1;
    }
    else
    {
        ADCIRQFlag = 0;
    }
    return ADCIRQFlag;
}
/**
 *@brief @b 函数名称:   void ADC_ChannelConfig(ADC_TypeDef *ADCx, CHNx CHNum, u16 Ch_n0, u16 Ch_n1, u16 Ch_n2, u16 Ch_n3)
 *@brief @b 功能描述:   ADC采样通道设置
 *@see被引用内容：      CHNx
 *@param输入参数：
					   ADCx，03系列固定选择ADC;
 *                     CHNum为枚举类型，对应0-3；
 *                     Ch_n0,Ch_n1,Ch_n2,Ch_n3：ADC_CHANNEL_0 ~ ADC_CHANNEL_13;
 *@param输出参数：     无
 *@return返 回 值：    无
 *@note其它说明：      无
 *@warning            无
 *@par 示例代码：
 *@code
            ADC_ChannelConfig(ADC,CHN0, ADC_CHANNEL_5 ,ADC_CHANNEL_5, ADC_CHANNEL_5 ,ADC_CHANNEL_5);
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年04月20日 <td>1.0     <td>Zhu Jie      <td>创建
 * </table>
 */
void ADC_ChannelConfig(ADC_TypeDef *ADCx, CHNx CHNum, u16 Ch_n0, u16 Ch_n1, u16 Ch_n2, u16 Ch_n3)
{
    if (CHNum == CHN0)
    {
        ADCx->CHN0 = Ch_n0 | Ch_n1 << 4 | Ch_n2 << 8 | Ch_n3 << 12;
    }
    else if (CHNum == CHN1)
    {
        ADCx->CHN1 = Ch_n0 | Ch_n1 << 4 | Ch_n2 << 8 | Ch_n3 << 12;
    }
    else if (CHNum == CHN2)
    {
        ADCx->CHN2 = Ch_n0 | Ch_n1 << 4;
    }
}
/**
 *@brief @b 函数名称:   s16 ADC_GetConversionValue(DATx DATNum)
 *@brief @b 功能描述:   读ADC采样值
 *@see被引用内容：      DATx
 *@param输入参数：      DATx：读取第x次采样结果值
 *@param输出参数：      无
 *@return返 回 值：     对应第x次采样结果值
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
		   s16 ADC_samp0 = 0；
		   ADC_samp0 = ADC_GetConversionValue(DAT0);//读取ADC第0次采样结果
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年04月20日 <td>1.0     <td>Zhu Jie      <td>创建
 * </table>
 */
s16 ADC_GetConversionValue(DATx DATNum)
{
    if (DATNum == DAT0)
    {
        return ADC_DAT0;
    }
    else if (DATNum == DAT1)
    {
        return ADC_DAT1;
    }
    else if (DATNum == DAT2)
    {
        return ADC_DAT2;
    }
    else if (DATNum == DAT3)
    {
        return ADC_DAT3;
    }
    else if (DATNum == DAT4)
    {
        return ADC_DAT4;
    }
    else if (DATNum == DAT5)
    {
        return ADC_DAT5;
    }
    else if (DATNum == DAT6)
    {
        return ADC_DAT6;
    }
    else if (DATNum == DAT7)
    {
        return ADC_DAT7;
    }
    else if (DATNum == DAT8)
    {
        return ADC_DAT8;
    }
    else if (DATNum == DAT9)
    {
        return ADC_DAT9;
    }
    return 0;
}
/**
 *@brief @b 函数名称:   void ADC_SoftTrgEN(ADC_TypeDef* ADCx, FuncState state)
 *@brief @b 功能描述:   ADC采样软件触发使能
 *@see被引用内容：      FuncState
 *@param输入参数：      ADCx，08系列固定选择ADC0
 *                     state：ENABLE触发，DISABLE不触发
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       ADC0_SWT写0x5AA5仅触发一次，完成后自动清零，等待下次软件触发
 *@warning             无
 *@par 示例代码：
 *@code
		  ADC_SoftTrgEN(ADC0，ENABLE);//软件触发一次ADC采样
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年04月20日 <td>1.0     <td>Zhu Jie      <td>创建
 * </table>
 */
void ADC_SoftTrgEN(ADC_TypeDef *ADCx, FuncState state)
{
    if (state == ENABLE)
    {
        ADC->SWT = 0x5AA5;
    }
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
