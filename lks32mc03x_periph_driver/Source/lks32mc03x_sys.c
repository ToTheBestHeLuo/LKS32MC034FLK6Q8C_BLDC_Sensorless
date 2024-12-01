/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc03x_sys.c\n
 * 文件标识： 无 \n
 * 内容摘要： SYS外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021年11月09日 <td>1.0     <td>YangZJ      <td>创建
 * </table>
 */
#include "lks32mc03x_sys.h"

/**
 * @brief 低功耗初始化结构体定义
 * 
 */
WAKE_InitTypeDef WAKE_InitStruct;

/**
 *@brief @b 函数名称:   void SYS_Init(SYS_InitTypeDef* SYS_InitStruct)
 *@brief @b 功能描述:   SYS模块初始化函数
 *@see被调用函数：      无
 *@param输入参数：      SYS_InitTypeDef* SYS_InitStruct
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       一般不使用该函数，因为涉及模块较多，比较杂乱，对应里面的配置在各模块
 *                     初始化单独配置。
 *@warning             无
 *@par 示例代码：
 *@code    
           SYS_InitTypeDef SYS_InitStruct;
           SYS_StructInit(&SYS_InitStruct);
           SYS_InitStruct.PLL_SrcSel = SYS_PLLSRSEL_RCH;    // 使用内部4MHz晶振作为时钟输入源
           SYS_Init(&SYS_InitStruct);
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021年11月10日 <td>1.0     <td>Yangzj      <td>创建
 * </table>
 */
void SYS_Init(SYS_InitTypeDef* SYS_InitStruct)
{
    uint32_t tmp1;

    SYS_WR_PROTECT = 0x7A83;    //解除系统寄存器写保护
    tmp1 = SYS_AFE_REG0;
    tmp1 &= 0x7FFF;
    tmp1 |= (SYS_InitStruct->PLL_SrcSel << 15);
    SYS_AFE_REG0 = tmp1;
    SYS_CLK_CFG = SYS_InitStruct->PLL_DivSel + (SYS_InitStruct->Clk_Sel << 8);
    
    SYS_CLK_DIV0 = SYS_InitStruct->Clk_DivI2C;
    SYS_CLK_DIV2 = SYS_InitStruct->Clk_DivUART;
    SYS_CLK_FEN = SYS_InitStruct->Clk_FEN;
    SYS_WR_PROTECT = 0;
}

/**
 *@brief @b 函数名称:   void SYS_StructInit(SYS_InitTypeDef* SYS_InitStruct)
 *@brief @b 功能描述:   SYS结构体初始化
 *@see被调用函数：      无
 *@param输入参数：      SYS_InitTypeDef* SYS_InitStruct
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无   
 *@par 示例代码：
 *@code    
           SYS_InitTypeDef SYS_InitStruct;
           SYS_StructInit(&SYS_InitStruct);
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021年11月10日 <td>1.0     <td>YangZJ      <td>创建
 * </table>
 */
void SYS_StructInit(SYS_InitTypeDef* SYS_InitStruct)
{
    SYS_InitStruct -> PLL_SrcSel  = SYS_PLLSRSEL_RCH;
    SYS_InitStruct -> PLL_DivSel  = 0xFF;
    SYS_InitStruct->Clk_Sel = CLK_SEL_PLL;
                                  
    SYS_InitStruct -> Clk_DivI2C  = SYS_Clk_SPIDiv1;
    SYS_InitStruct -> Clk_DivUART = SYS_Clk_UARTDiv1;
    SYS_InitStruct -> Clk_FEN     = 0;
}

/**
 *@brief @b 函数名称:   void SYS_ClearRst(void)
 *@brief @b 功能描述:   SYS清除复位标志记录
 *@see被调用函数：      无
 *@param输入参数：      无
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       请注意由于复位记录工作于低速时钟域，清除执行完成需要一定时间，不应清
                       除后立即读记录状态 
 *@warning             无
 *@par 示例代码：
 *@code    
           u32 RSET_VALUE = 0;
           SYS_ClearRst();//清除复位标志记录
           delay_ms(1);
           RSET_VALUE = SYS_GetRstSource();//读取复位源记录值
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021年11月10日 <td>1.0     <td>YangZJ      <td>创建
 * </table>
 */
void SYS_ClearRst(void)
{
    AON_EVT_RCD = 0xCA40;
}

/**
 *@brief @b 函数名称:   uint32_t SYS_GetRstSource(void)
 *@brief @b 功能描述:   获得SYS复位源信号
 *@see被调用函数：      无
 *@param输入参数：      无
 *@param输出参数：      
 * <table>
 *                     <tr><th>BIT3 <td>看门狗复位发生标志<td> 高有效
 *                     <tr><th>BIT2 <td>按键复位发生标志  <td> 高有效
 *                     <tr><th>BIT1 <td>HPOR 复位发生标志 <td> 高有效
 *                     <tr><th>BIT0 <td>LPOR 复位发生标志 <td> 高有效
 * </table>
 *@return返 回 值：     复位源记录值
 *@note其它说明：       返回值位介绍  
 *@warning             无     
 *@par 示例代码：
 *@code    
           u32 RSET_VALUE = 0;
           RSET_VALUE = SYS_GetRstSource();//读取复位源记录值
           如 RSET_VALUE = 0x01;则LPOR发生复位
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021年11月10日 <td>1.0     <td>YangZJ      <td>创建
 * </table>
 */
uint32_t SYS_GetRstSource(void)
{
    return AON_EVT_RCD;
}

/**
 *@brief @b 函数名称:   void SYS_ModuleClockCmd(uint32_t nModule, FuncState state)
 *@brief @b 功能描述:   数字模块时钟使能和停止
 *@see被调用枚举：      FuncState
 *@param输入参数：   
 *                     state： ENABLE使能 , DISABLE关闭     
 *                     nModule：参数可选： \n 
 * <table> 
 *                     <tr><td> 宏定义                   <td>原始值    <td>说明
 *                     <tr><th> SYS_Module_I2C           <td> BIT0    <td> I2C模块
 *                     <tr><th> SYS_Module_HALL          <td> BIT1    <td>HALL模块
 *                     <tr><th> SYS_Module_UART          <td> BIT2    <td>UART模块
 *                     <tr><th> SYS_Module_CMP           <td> BIT3    <td> CMP模块
 *                     <tr><th> SYS_Module_MCPWM         <td> BIT4    <td> MCPWM模块
 *                     <tr><th> SYS_Module_TIMER0        <td> BIT5    <td>TIMER0模块
 *                     <tr><th> SYS_Module_TIMER1        <td> BIT6    <td>TIMER1模块
 *                     <tr><th> SYS_Module_GPIO          <td> BIT7    <td>  GPIO模块
 *                     <tr><th> SYS_Module_DSP           <td> BIT8    <td>DSP模块
 *                     <tr><th> SYS_Module_ADC           <td> BIT9    <td>ADC模块
 *                     <tr><th> SYS_Module_SPI           <td> BIT10   <td>SPI模块
 *                     <tr><th> SYS_Module_DMA           <td> BIT11   <td>DMA模块
 * </table>
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
        SYS_ModuleClockCmd(SYS_Module_SPI,ENABLE);//使能SPI时钟
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2021年11月10日 <td>1.0     <td>YangZJ         <td>创建
 * </table>
 */
void SYS_ModuleClockCmd(uint32_t nModule, FuncState state)
{
    SYS_WR_PROTECT = 0x7A83;    //解除系统寄存器写保护
    if (state != DISABLE)
    {
        SYS_CLK_FEN |= nModule;
    }
    else
    {
        SYS_CLK_FEN &= ~nModule;
    }
    SYS_WR_PROTECT = 0;
}

/**
 *@brief @b 函数名称:   void SYS_AnalogModuleClockCmd(uint32_t nModule, FuncState state)
 *@brief @b 功能描述:   模拟模块使能和停止
 *@see被调用枚举：      FuncState
 *@param输入参数：      
 *                     state： ENABLE使能 , DISABLE关闭  \n 
 *                     nModule：参数可选： \n 
 * <table> 
 *                     <tr><td> 宏定义                  <td>说明
 *                     <tr><th> SYS_AnalogModule_ADC   <td>  BIT8  <td> ADC模块  
 *                     <tr><th> SYS_AnalogModule_OPA   <td>  BIT9  <td> OPA0模块 
 *                     <tr><th> SYS_AnalogModule_BGP   <td>  BIT10 <td> OPA1模块 
 *                     <tr><th> SYS_AnalogModule_DAC   <td>  BIT11 <td> OPA2模块 
 *                     <tr><th> SYS_AnalogModule_TMP   <td>  BIT12 <td> OPA3模块
 *                     <tr><th> SYS_AnalogModule_CMP0  <td>  BIT13 <td> CMP0模块 
 *                     <tr><th> SYS_AnalogModule_CMP1  <td>  BIT14 <td> CMP1模块 
 *                     <tr><th> SYS_AnalogModule_PLL   <td>  BIT8  <td> BGP模块                 
 * </table>
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
        SYS_AnalogModuleClockCmd(SYS_AnalogModule_PLL,ENABLE);//使能PLL模块
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2021年11月10日 <td>1.0     <td>YangZJ         <td>创建
 * </table>
 */
void SYS_AnalogModuleClockCmd(uint32_t nModule, FuncState state)
{
    SYS_WR_PROTECT = 0x7A83;    //解除系统寄存器写保护
    
    if (state == ENABLE)
    {
        if(nModule & SYS_AnalogModule_BGP)
        {//BGP与其他模块极性相反
            SYS_AFE_REG0 &= ~SYS_AnalogModule_BGP;
            nModule &= ~SYS_AnalogModule_BGP;
        }
        SYS_AFE_REG0 |= nModule;
    }
    else
    {
        if(nModule & SYS_AnalogModule_BGP)
        {//BGP与其他模块极性相反
            SYS_AFE_REG0 |= SYS_AnalogModule_BGP;
            nModule |= SYS_AnalogModule_BGP;
        }
        SYS_AFE_REG0 &= ~nModule;
    }
    SYS_WR_PROTECT = 0;
}

/**
 *@brief @b 函数名称:   void SYS_SoftResetModule(uint32_t nModule)
 *@brief @b 功能描述:   模块软复位函数
 *@see被调用函数：      无
 *@param输入参数：      
 *                     nModule：参数可选： \n 
 * <table> 
 *                     <tr><td> 宏定义                   <td>原始值    <td>说明
 *                     <tr><th> SYS_Module_I2C           <td> BIT0    <td> I2C模块
 *                     <tr><th> SYS_Module_HALL          <td> BIT1    <td>HALL模块
 *                     <tr><th> SYS_Module_UART          <td> BIT2    <td>UART模块
 *                     <tr><th> SYS_Module_CMP           <td> BIT3    <td> CMP模块
 *                     <tr><th> SYS_Module_MCPWM         <td> BIT4    <td> MCPWM模块
 *                     <tr><th> SYS_Module_TIMER0        <td> BIT5    <td>TIMER0模块
 *                     <tr><th> SYS_Module_TIMER1        <td> BIT6    <td>TIMER1模块
 *                     <tr><th> SYS_Module_GPIO          <td> BIT7    <td>  GPIO模块
 *                     <tr><th> SYS_Module_DSP           <td> BIT8    <td>DSP模块
 *                     <tr><th> SYS_Module_ADC           <td> BIT9    <td>ADC模块
 *                     <tr><th> SYS_Module_SPI           <td> BIT10   <td>SPI模块
 *                     <tr><th> SYS_Module_DMA           <td> BIT11   <td>DMA模块
 * </table>
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无     
 *@warning             无
 *@par 示例代码：
 *@code    
           SYS_SoftResetModule(SYS_Module_ADC);
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2022年04月26日 <td>1.0     <td>HuangMG      <td>创建
 * </table>
 */
void SYS_SoftResetModule(uint32_t nModule)
{
    SYS_WR_PROTECT = 0x7A83;    //解除系统寄存器写保护
    SYS_SFT_RST = nModule;
    SYS_SFT_RST = 0;
    SYS_WR_PROTECT = 0;
}

/**
 *@brief @b 函数名称:   void SYS_VolSelModule(uint32_t Vol)
 *@brief @b 功能描述:   时钟校正函数
 *@see被调用函数：      无
 *@param输入参数：      Vol：0 3.3 Voltage；1 5.0 Voltage
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无     
 *@warning             无
 *@par 示例代码：
 *@code    
           SYS_VolSelModule(0);
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2022年04月26日 <td>1.0     <td>HuangMG      <td>创建
 * </table>
 */
void SYS_VolSelModule(uint32_t Vol)
{
	if((Read_Trim(0x000001D4)>>16) >= 0x03)
	{
		if(Vol == 0) //3.3 Voltage
		{

		SYS_AFE_REG5 = (Read_Trim(0x00000198)>>16) & 0xffff; 

		SYS_AFE_REG6 = (Read_Trim(0x0000019C)>>16) & 0xffff; 
        }
        else         // 5.0 Voltage
        {
	    SYS_AFE_REG5 = Read_Trim(0x00000198) & 0xffff;

		SYS_AFE_REG6 = Read_Trim(0x0000019C) & 0xffff;
        }

	}
}

/**
 *@brief @b 函数名称:   static void SoftDelay(u32 cnt)
 *@brief @b 功能描述:   延时函数
 *@see被调用函数：      无
 *@param输入参数：      cnt：延时cnt的空指令_NOP()
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       改函数只在此文件使用，主要用在Switch2PLL函数内      
 *@warning             无
 *@par 示例代码：
 *@code    
           SoftDelay(0xff);//延时255个_NOP()时间1个_NOP大约按一个系统时钟周期计算
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2022年04月14日 <td>1.0     <td>HuangMG      <td>创建
 * </table>
 */
static void SoftDelay(u32 cnt)
{
    volatile u32 t_cnt;
    for (t_cnt = 0; t_cnt < cnt; t_cnt++)
    {
        __nop();
    }
}

/**
 *@brief @b 函数名称:   void Switch2PLL(void)
 *@brief @b 功能描述:   休眠唤醒后，系统时钟切换到PLL时钟函数
 *@see被调用函数：      无
 *@param输入参数：      无
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       系统低功耗唤醒使用  
 *@warning             无 
 *@par 示例代码：
 *@code    
           Switch2PLL();
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2022年04月26日 <td>1.0     <td>HuangMG      <td>创建
 * </table>
 */
void Switch2PLL(void)
{
	  SYS_WR_PROTECT = 0x7a83;                        /*开启寄存器写使能*/
    SYS_AFE_REG0 = WAKE_InitStruct.AFE_REG0_RECORD; /*开启 PLL,BGP*/
    SoftDelay(200);
    SYS_CLK_CFG = WAKE_InitStruct.CLK_CFG_RECORD;   /*将主时钟切换到PLL时钟*/
	  SYS_WR_PROTECT = 0x0; 
}

/**
 *@brief @b 函数名称:   void Switch2HRC(void)
 *@brief @b 功能描述:   休眠唤醒前一时刻，关闭高速时钟与BGP和掉电检测电路函数
 *@see被调用函数：      无
 *@param输入参数：      无
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       系统低功耗休眠使用   
 *@warning             无
 *@par 示例代码：
 *@code    
           Switch2HRC();
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2022年04月26日 <td>1.0     <td>HuangMG      <td>创建
 * </table>
 */
void Switch2HRC(void)
{
	  SYS_WR_PROTECT = 0x7a83; /*开启寄存器写使能*/
    WAKE_InitStruct.AFE_REG0_RECORD = SYS_AFE_REG0;
	  WAKE_InitStruct.CLK_CFG_RECORD = SYS_CLK_CFG;
	  SYS_CLK_CFG = 0x101;         /* 使用PLL 1/8分频时钟 */
	  SYS_AFE_REG0 = 0x0400;    /* 准备关闭 PLL,BGP*/  
	  SYS_WR_PROTECT = 0x0; 
}

/**
 *@brief @b 函数名称:    void SetWakeIO(uint32_t wakeIO, enumWakeTrigLevel trigLevel, uint32_t flt , uint8_t ena)
 *@brief @b 功能描述:    设置休眠唤醒IO
 *@see唤醒电平选择枚举：  enumWakeTrigLevel 
 *@param输入参数：                           
 * <table>              <tr><td>wakeIO = BIT5: GPIO 1[5]  / P1[5]  外部唤醒使能。1：使能；0：禁用。 \n
 *                              wakeIO = BIT4: GPIO 0[10] / P0[10] 外部唤醒使能。1：使能；0：禁用。 \n
 *                              wakeIO = BIT3: GPIO 0[9]  / P0[9]  外部唤醒使能。1：使能；0：禁用。 \n
 *                              wakeIO = BIT2: GPIO 0[8]  / P0[8]  外部唤醒使能。1：使能；0：禁用。 \n
 *                              wakeIO = BIT1: GPIO 0[2]  / P0[2]  外部唤醒使能。1：使能；0：禁用。 \n
 *                              wakeIO = BIT0: GPIO 0[0]  / P0[0]  外部唤醒使能。1：使能；0：禁用。
 *                      <tr><td>enumWakeTrigLevel : \n
 *                              唤醒电平选择： \n 
 *                              0:低电平唤醒 \n
 *                              1:高电平唤醒 
 *                      <tr><td>flt: \n
 *                              ENABLE： 开启IO滤波 \n
 *                              DISABLE：关闭IO滤波 
 *                      <tr><td>ena: \n
 *                              ENABLE： 开启IO唤醒 \n
 *                              DISABLE：关闭IO唤醒 
 * </table>
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无    
 *@warning             无 
 *@par 示例代码：
 *@code    
           SetWakeIO(WAKEIO_P0_0,WAKETRIG_LOW,ENABLE,ENABLE);//系统休眠时,使能P0.0作为低功耗唤醒IO，
           低电平唤醒
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2022年04月26日 <td>1.0     <td>HuangMG      <td>创建
 * </table>
 */
void SetWakeIO(uint32_t wakeIO, enumWakeTrigLevel trigLevel, uint32_t flt , uint8_t ena)
{
	if(ena == ENABLE)
	{
		AON_IO_WAKE_EN |= wakeIO;
	}
	else
	{
		AON_IO_WAKE_EN &= ~wakeIO;
	}
	
	if (trigLevel == WAKETRIG_HIGH)
	{
		AON_IO_WAKE_POL = 0x01;
	}
	else
	{
		AON_IO_WAKE_POL = 0x00;
	}
	
	if(flt == IOWK_FLT_EN)
	{
	  AON_PWR_CFG = BIT1;
	}else{
		AON_PWR_CFG = 0;
	}
}

/**
 *@brief @b 函数名称:   void SYS_FallSleep(void)
 *@brief @b 功能描述:   触发系统进入休眠状态
 *@see被调用函数：      无
 *@param输入参数：      无
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无 
 *@warning             无
 *@par 示例代码：
 *@code    
           SYS_FallSleep();
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2022年04月26日 <td>1.0     <td>HuangMG      <td>创建
 * </table>
 */
void SYS_FallSleep(void)
{
	NVIC_DisableIRQ(TIMER0_IRQn); /*关闭TIMER0中断*/
	NVIC_DisableIRQ(TIMER1_IRQn); /*关闭TIMER1中断*/
	NVIC_DisableIRQ(I2C_IRQn); /*关闭I2C中断*/
	NVIC_DisableIRQ(SPI_IRQn); /*关闭SPI中断*/
	NVIC_DisableIRQ(GPIO_IRQn); /*关闭GPIO中断*/
	NVIC_DisableIRQ(HALL_IRQn); /*关闭HALL中断*/
	NVIC_DisableIRQ(UART_IRQn); /*关闭UART中断*/
	NVIC_DisableIRQ(CMP_IRQn); /*关闭CMP中断*/
	NVIC_DisableIRQ(ADC_IRQn); /*关闭ADC中断*/
	NVIC_DisableIRQ(MCPWM0_IRQn); /*关闭MCPWM0中断*/
	NVIC_DisableIRQ(MCPWM1_IRQn); /*关闭MCPWM1中断*/
	NVIC_DisableIRQ(DMA_IRQn); /*关闭DMA中断*/
	NVIC_DisableIRQ(SW_IRQn); /*关闭SW中断*/

	IWDG_PSW = 0xA6B4;
	IWDG_CLR = 0x798D;
	SCB->SCR |= (1UL << 2);
	 __WFI();	  /*PC指针停止运行，等待中断*/
}

/**
 *@brief @b 函数名称:   void SYS_EVTCLRSleep(void)
 *@brief @b 功能描述:   清除休眠全部事件记录
 *@see被调用函数：      无
 *@param输入参数：      无
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无 
 *@warning             无
 *@par 示例代码：
 *@code    
           SYS_EVTCLRSleep();
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2022年04月26日 <td>1.0     <td>HuangMG      <td>创建
 * </table>
 */
void SYS_EVTCLRSleep(void)
{
	 AON_EVT_RCD = PSW_EVT_CLR;/* 清除全部事件记录*/
}

/**
 *@brief @b 函数名称:    void SYS_SetWakeInterval(uint32_t rth , uint32_t wth , uint8_t ena)
 *@brief @b 功能描述:    设置休眠唤醒周期
 *@see被调用函数：  无
 *@param输入参数：                           
 * <table>
 *                     <tr><th>rth <td>看门狗超时复位门限值，也是重新装载值(最大值0x1FF000)
 *                     <tr><th>wth <td>看门狗定时唤醒门限值(最大值小于rth)
 *                     <tr><th>ena <td>ENABLE：开启定时唤醒  DISABLE：关闭定时唤醒  
 * </table>
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       
 *               唤醒时间计算公式：
 *               WakeupIWDG = tLRC * (rth - Iwth) 
 *               tLRC 为 LRC时钟周期，1/64kHz=15.625uS
 *</table>
 *               <tr><th>rth - wth    <td>唤醒时间
 *               <tr><th>16000        <td>0.25S
 *               <tr><th>32000        <td>0.5S
 *               <tr><th>64000        <td>1S
 *               <tr><th>128000       <td>2S
 *               <tr><th>256000       <td>4S  
 *</table> 
 *@warning             无 
 *@par 示例代码：
 *@code    
           SetWakeIO(WAKEIO_P0_0,WAKETRIG_LOW,ENABLE,ENABLE);//系统休眠时,使能P0.0作为低功耗唤醒IO，
           低电平唤醒
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2022年04月26日 <td>1.0     <td>HuangMG      <td>创建
 * </table>
 */
void SYS_SetWakeInterval(uint32_t rth , uint32_t wth , uint8_t ena)
{ 
	 if(ena == ENABLE)
	 { 
	   IWDG_CFG |= 0x01 << 4; /*深度休眠定时唤醒使能*/
	 }else{
		 IWDG_CFG &= ~(0x01 << 4); /*关闭深度休眠定时唤醒*/
	 }
	  IWDG_PSW = 0xA6B4;     /*使能看门狗部分寄存器写操作*/
	  IWDG_RTH = rth;
	  IWDG_WTH = wth;
}

/**
 *@brief @b 函数名称:   void DSP_Init(void)
 *@brief @b 功能描述:   DSP时钟使能
 *@see被调用函数：      无
 *@param输入参数：      无
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无 
 *@warning             无
 *@par 示例代码：
 *@code    
           DSP_Init();
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2016年06月28日 <td>1.0     <td>cfwu      <td>创建
 * </table>
 */
void DSP_Init(void)
{
    SYS_ModuleClockCmd(SYS_Module_DSP, ENABLE); /* DSP时钟使能*/
}
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
