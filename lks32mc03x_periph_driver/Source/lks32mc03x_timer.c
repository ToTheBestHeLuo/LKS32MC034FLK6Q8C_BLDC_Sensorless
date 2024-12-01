/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc03x_tim.c\n
 * 文件标识： 无 \n
 * 内容摘要： 定时器外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021年11月10日 <td>1.0     <td>YangZJ        <td>创建
 * </table>
 */
#include "lks32mc03x_timer.h"

/**
 *@brief @b 函数名称:   void TIM_TimerInit(TIM_TimerTypeDef *TIMERx, TIM_TimerInitTypeDef *this)
 *@brief @b 功能描述:   定时器初始化函数
 *@see被引用内容：      SYS_ModuleClockCmd()
 *@param输入参数：      TIMERx：TIMER0/TIMER1/TIMER2/TIMER3 \n
                        TIM_TimerInitTypeDef *this
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
          TIM_TimerInitTypeDef TIM_InitStruct;
          TIM_TimerStrutInit(&TIM_InitStruct);        // Timer结构体变量初始化 
          TIM_InitStruct.CLK_DIV = TIM_Clk_Div1;      // 设置Timer模块数据分频系数 
          TIM_InitStruct.CH0_MODE = TIMER_OPMode_CMP; // 设置Timer CH0为比较模式
          TIM_InitStruct.CH0_POL = 0;                 // 计数器回零时，比较模式输出极性控制
          TIM_InitStruct.CH1_MODE = TIMER_OPMode_CMP; // 设置Timer CH1为比较模式
          TIM_InitStruct.CH1_POL = 0;                 // 计数器回零时，比较模式输出极性控制 
          TIM_InitStruct.TH = 24000;                  // 设置计数器计数模值 0.5ms 2KHZ
          TIM_InitStruct.TIM_CMP0 = 18000;            // 设置比较模式的CH0比较值 
          TIM_InitStruct.TIM_CMP1 = 18000;            // 设置比较模式的CH1比较值 
          TIM_InitStruct.IE = TIM_IRQ_IE_CH1;         // 开启Timer模块CH1比较中断 
          TIM_TimerInit(TIMER1, &TIM_InitStruct);
		  TIM_TimerCmd(TIMER1,ENABLE);                // 使能Timer1时钟
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021年11月10日 <td>1.0       <td>YangZJ          <td>创建
 * </table>
 */
void TIM_TimerInit(TIM_TimerTypeDef *TIMERx, TIM_TimerInitTypeDef *this)
{
    if(TIMERx == TIMER0)
    {
        SYS_ModuleClockCmd(SYS_Module_TIMER0,ENABLE);     //打开Timer时钟
    }
    if(TIMERx == TIMER1)
    {
        SYS_ModuleClockCmd(SYS_Module_TIMER1,ENABLE);     //打开Timer时钟
    }
		
		
    TIMERx -> CFG  = (this->CAP1_CLR_EN   << 27) |
                     (this->CAP0_CLR_EN   << 26) | (this->ETON          << 24) |
                     (this->CLK_DIV       << 20) | (this->CLK_SRC       << 16) |
                     (this->SRC1          << 12) | (this->CH1_POL       << 11) |
                     (this->CH1_MODE      << 10) | (this->CH1_FE_CAP_EN <<  9) |
                     (this->CH1_RE_CAP_EN <<  8) | (this->SRC0          <<  4) |
                     (this->CH0_POL       <<  3) | (this->CH0_MODE      <<  2) |
                     (this->CH0_FE_CAP_EN <<  1) | (this->CH0_RE_CAP_EN);
    TIMERx -> TH    = this->TH;
    TIMERx -> CNT   = this->CNT;
    TIMERx -> CMPT0 = this->TIM_CMP0;
    TIMERx -> CMPT1 = this->TIM_CMP1;
    TIMERx -> EVT   = this->EVT_SRC;
    TIMERx -> FLT   = this->FLT;
    TIMERx -> IE    = this->IE;
    TIMERx -> IF    = 0x7;
		TIM_TimerCmd(TIMERx,this->EN);
}
/**
 *@brief @b 函数名称:   void TIM_TimerCmd(TIM_TimerTypeDef *TIMERx, FuncState state)
 *@brief @b 功能描述:   定时器时钟使能函数
 *@see被引用内容：      FuncState
 *@param输入参数：      TIM_TimerTypeDef *TIMERx , FuncState state
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning              无
 *@par 示例代码：
 *@code
			    TIM_TimerCmd(TIMER1,ENABLE); // 使能Timer1时钟
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version     <th>Author       <th>Description
 * <tr><td>2022年12月5日  <td>1.0       <td>HuangMG          <td>创建
 * </table>
 */
void TIM_TimerCmd(TIM_TimerTypeDef *TIMERx, FuncState state)
{
    if (state != DISABLE)
    {
         TIMERx -> CFG |= BIT31;
    }
    else
    {   
         TIMERx -> CFG &= ~BIT31;
    }
}


/**
 *@brief @b 函数名称:   void TIM_TimerStrutInit(TIM_TimerInitTypeDef *this)
 *@brief @b 功能描述:   定时器结构体初始化
 *@see被引用内容：      无
 *@param输入参数：      TIM_TimerInitTypeDef *this
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
			    TIM_TimerInitTypeDef TIM_InitStruct;
          TIM_TimerStrutInit(&TIM_InitStruct);  // Timer结构体初始化
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021年11月10日 <td>1.0       <td>YangZJ          <td>创建
 * </table>
 */
void TIM_TimerStrutInit(TIM_TimerInitTypeDef *this)
{
    this -> CAP1_CLR_EN   = DISABLE;          // 当发生 CAP1 捕获事件时，清零 Timer 计数器，高有效
    this -> CAP0_CLR_EN   = DISABLE;          // 当发生 CAP0 捕获事件时，清零 Timer 计数器，高有效
    this -> ETON          = DISABLE;          // Timer 计数器计数使能配置 0: 自动运行 1: 等待外部事件触发计数
    this -> CLK_DIV       = 0;                // Timer 计数器分频
    this -> CLK_SRC       = TIM_Clk_SRC_MCLK; // Timer 时钟源
    this -> TH            = 0;                // Timer 计数器计数门限。计数器从 0 计数到 TH 值后再次回 0 开始计数
            
    this -> SRC1          = TIM_SRC1_1;       // Timer 通道 1 捕获模式信号来源
    this -> CH1_POL       = 1;                // Timer 通道 1 在比较模式下的输出极性控制，计数器回0后的输出值
    this -> CH1_MODE      = 0;                // Timer 通道 1 工作模式选择，0：比较模式，1：捕获模式
    this -> CH1_FE_CAP_EN = DISABLE;          // Timer 通道 1 下降沿捕获事件使能。1:使能；0:关闭
    this -> CH1_RE_CAP_EN = DISABLE;          // Timer 通道 1 上升沿捕获事件使能。1:使能；0:关闭
    this -> TIM_CMP1      = 0;            // Timer 通道 1 比较门限
            
    this -> SRC0          = TIM_SRC1_0;       // Timer 通道 0 捕获模式信号来源
    this -> CH0_POL       = 1;                // Timer 通道 0 在比较模式下的输出极性控制，计数器回0后的输出值
    this -> CH0_MODE      = 0;                // Timer 通道 0 工作模式选择，0：比较模式，1：捕获模式
    this -> CH0_FE_CAP_EN = DISABLE;          // Timer 通道 0 下降沿捕获事件使能。1:使能；0:关闭
    this -> CH0_RE_CAP_EN = DISABLE;          // Timer 通道 0 上升沿捕获事件使能。1:使能；0:关闭
    this -> TIM_CMP0      = 0;            // Timer 通道 0 比较门限
            
    this -> CNT           = 0;                // Timer 计数器当前计数值。写操作可以写入新的计数值。
    this -> EVT_SRC       = 0;                // Timer 计数使能开始后，外部事件选择
    this -> FLT           = 0;                // 通道 0/1 信号滤波宽度选择，0-255
    this -> IE            = 0;                // Timer 中断失能
		this -> EN = DISABLE;                     // Timer 中断失能
}

/**
 *@brief @b 函数名称:   uint32_t TIM_GetIRQFlag(TIM_TimerTypeDef *TIMERx , u32 timer_if)
 *@brief @b 功能描述:   获取TIM中断标志
 *@see被引用内容：      无
 *@param输入参数：      TIMERx：TIMER0/TIMER1 \n
                        timer_if：
 * <table>              <tr><th>TIM_IRQ_IF_ZC   <td>TIMER计数器过0(计数器回零)中断标志
                        <tr><th>TIM_IRQ_IF_CH1  <td>Timer1比较OR捕获事件中断标志
                        <tr><th>TIM_IRQ_IF_CH0  <td>Timer0比较OR捕获事件中断标志
 * </table> 
 *@param输出参数：      无
 *@return返 回 值：     0或1，对应中断标志置位返回1，未置位返回0
 *@note其它说明：       无
 *@warning             只有对应中断使能后，改为才能读取，如果对应中断未使能，读取结果一直为0
 *@par 示例代码：
 *@code
			    if(TIM_GetIRQFlag(TIMER0,TIM_IRQ_IF_CH0)) //判断UTimer0的CH0是否发生比较中断
                {
                }
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
  * <tr><td>2022年04月11日 <td>1.0     <td>HuangMG        <td>修改
 * </table>
 */
uint32_t TIM_GetIRQFlag(TIM_TimerTypeDef *TIMERx , u32 timer_if)
{
	if(TIMERx == TIMER0)
    {
			if((UTIMER0_IF & timer_if & UTIMER0_IE) == 0)
			{
			  return 0;
			}else{
				return 1;
			}    
    }
    if(TIMERx == TIMER1)
    {
      if((UTIMER1_IF & timer_if & UTIMER1_IE) == 0)
			{
			  return 0;
			}else{
				return 1;
			}
    }
     return 0;
}

/**
 *@brief @b 函数名称:   void TIM_ClearIRQFlag(TIM_TimerTypeDef *TIMERx , uint32_t tempFlag)
 *@brief @b 功能描述:   清除TIM中断标志
 *@see被引用内容：      无
 *@param输入参数：      TIMERx：TIMER0/TIMER1 \n
                        timer_if：
 * <table>              <tr><th>TIM_IRQ_IF_ZC   <td>TIMER计数器过0(计数器回零)中断标志
                        <tr><th>TIM_IRQ_IF_CH1  <td>Timer1比较OR捕获事件中断标志
                        <tr><th>TIM_IRQ_IF_CH0  <td>Timer0比较OR捕获事件中断标志
 * </table> 
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning              无
 *@par 示例代码：
 *@code
			    if(TIM_GetIRQFlag(TIMER0,TIM_IRQ_IF_CH0)) //判断UTimer0的CH0是否发生比较中断
          {
              TIM_ClearIRQFlag(TIMER0,TIM_IRQ_IF_CH0); //清除UTimer0通道0比较中断标志位
          }
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
  * <tr><td>2022年04月13日 <td>1.0     <td>HuangMG        <td>修改
 * </table>
 */
void TIM_ClearIRQFlag(TIM_TimerTypeDef *TIMERx , uint32_t tempFlag)
{
		if(TIMERx == TIMER0)
    {
        UTIMER0_IF = tempFlag;
    }
    if(TIMERx == TIMER1)
    {
        UTIMER1_IF = tempFlag;
    }
}

/**
 *@brief @b 函数名称:   uint32_t TIM_Timer_GetCount(TIM_TimerTypeDef *TIMERx)
 *@brief @b 功能描述:   获取Timer计数值
 *@see被引用内容：      无
 *@param输入参数：      TIMERx：TIMER0/TIMER1
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning              无
 *@par 示例代码：
 *@code
            uint32_t TIMER0_Value = 0;
            TIMER0_Value = TIM_Timer_GetCount(TIMER0); //获取定时器0计数值
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
  * <tr><td>2022年04月11日 <td>1.0      <td>HuangMG          <td>修改
 * </table>
 */
uint32_t TIM_Timer_GetCount(TIM_TimerTypeDef *TIMERx)
{
   return TIMERx->CNT;
}

/**
 *@brief @b 函数名称:   uint32_t TIM_Timer_GetCMPT0(TIM_TimerTypeDef *TIM_TIMERx)
 *@brief @b 功能描述:   获取定时器通道0捕获值
 *@see被引用内容：       无
 *@param输入参数：      TIM_TIMERx：TIMER0/TIMER1
 *@param输出参数：      无
 *@return返 回 值：     定时器通道0捕获值
 *@note其它说明：       当定时器发生捕获事件时，将捕获时刻的cnt值存储到该寄存器中
 *@warning              无
 *@par 示例代码：
 *@code
                    uint32_t TIMER0_CAPValue = 0;
                    TIMER0_CAPValue = TIM_Timer_GetCMPT0(TIMER0); //获取定时器0捕获值
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
  * <tr><td>2022年04月11日 <td>1.0      <td>HuangMG          <td>修改
 * </table>
 */
uint32_t TIM_Timer_GetCMPT0(TIM_TimerTypeDef *TIM_TIMERx)
{
   return TIM_TIMERx->CMPT0;
}

/**
 *@brief @b 函数名称:   uint32_t TIM_Timer_GetCMPT1(TIM_TimerTypeDef *TIM_TIMERx)
 *@brief @b 功能描述:   获取定时器通道1捕获值
 *@see被引用内容：      无
 *@param输入参数：      TIM_TIMERx：TIMER0/TIMER1
 *@param输出参数：      无
 *@return返 回 值：     定时器通道1捕获值
 *@note其它说明：       当定时器发生捕获事件时，将捕获时刻的cnt值存储到该寄存器中
 *@warning              无
 *@par 示例代码：
 *@code
                    uint32_t TIMER0_CAPValue = 0;
                    TIMER0_CAPValue = TIM_Timer_GetCMPT1(TIMER0); //获取定时器0捕获值
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
  * <tr><td>2022年04月11日 <td>1.0      <td>HuangMG          <td>创建
 * </table>
 */
uint32_t TIM_Timer_GetCMPT1(TIM_TimerTypeDef *TIM_TIMERx)
{
   return TIM_TIMERx->CMPT1;  
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
