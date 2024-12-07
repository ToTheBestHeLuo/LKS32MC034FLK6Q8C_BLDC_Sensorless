/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： interrupt.c
 * 文件标识：
 * 内容摘要： 中断服务程序文件
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： HuangMG
 * 完成日期： 2021年11月15日
 *
 *******************************************************************************/
#include "lks32mc03x_lib.h"
#include "hardware_init.h"

#include "bldcConfig.h"
#include "protocol.h"
/*******************************************************************************
 函数名称：    void ADC_IRQHandler(void)
 功能描述：    ADC0中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/15      V1.0        HuangMG        创建
 *******************************************************************************/
void ADC_IRQHandler(void)
{
//		GPIO_ResetBits(GPIO1,GPIO_Pin_5);
		if(ADC_GetIRQFlag(ADC,ADC_EOS0_IRQ_EN)){  /*判断是否ADC第一段采样完成中断*/
			ADC_ClearIRQFlag(ADC,ADC_EOS0_IRQ_IF);/*清除ADC第一段采样完成中断标志位*/
			BLDC_LowSpeedTask();
		}
//		GPIO_SetBits(GPIO1,GPIO_Pin_5);
}

/*******************************************************************************
 函数名称：    void DMA_IRQHandler(void)
 功能描述：    DMA中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/15      V1.0        HuangMG        创建
 *******************************************************************************/
void DMA_IRQHandler(void)
{
		GPIO_ResetBits(GPIO1,GPIO_Pin_5);
		/*检查DMA的CH0完成中断*/
		if(DMA_IF & 0x1){
			DMA_IF = 0xf;
			/*检查当前系统的工作状态*/
			if(protocolHandler.status == eProtocol_Sys_Polling){	
				/*开始做信号解析*/
				protocolAnalysisFunc[protocolHandler.type]();
			}else{
				if(protocolHandler.signalFrameCounter < 2){
					protocolHandler.signalPulseWidth = TIMER1->CMPT1;
					protocolHandler.signalFrameCounter++;
				}
			}
			/*重设CH0的比较值，重新打开CH0的比较中断*/
			TIMER1->CMPT0 = 720;TIMER1->IE |= 0x00000001;
		}
		GPIO_SetBits(GPIO1,GPIO_Pin_5);		
}

/*******************************************************************************
 函数名称：    void MCPWM0_IRQHandler(void)
 功能描述：    MCPWM0中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/15      V1.0        HuangMG        创建
 *******************************************************************************/
void MCPWM0_IRQHandler(void)
{
//		GPIO_ResetBits(GPIO1,GPIO_Pin_5);
		if(MCPWM0->PWM_EIF & BIT5){
			MCPWM0->PWM_EIF = (BIT4 | BIT5 | BIT6 | BIT7);
			bldcSysHandler.sysErrorCode = eBLDC_Sys_Error_DriverBrake;
		}
		if(MCPWM0->PWM_IF0 & BIT13){
			MCPWM0->PWM_IF0 = BIT13;
			BLDC_HighSpeedTask();
		}
//		GPIO_SetBits(GPIO1,GPIO_Pin_5);
}

/*******************************************************************************
 函数名称：    void MCPWM1_IRQHandler(void)
 功能描述：    MCPWM1中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/15      V1.0        HuangMG        创建
 *******************************************************************************/
void MCPWM1_IRQHandler(void)
{
}

/*******************************************************************************
 函数名称：    void HALL_IRQHandler(void)
 功能描述：    HALL中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/15      V1.0        HuangMG        创建
 *******************************************************************************/
void HALL_IRQHandler(void)
{
		if(HALL->INFO & BIT17){
			HALL->INFO = BIT17;
			BLDC_PWM_AllSides_TurnOff();
			BLDC_RunMode runMode = bldcSysHandler.bldcSensorlessHandler.runMode;
			if(runMode == eBLDC_Run_Mode_COMP_Polling)
				bldcSysHandler.sysErrorCode = eBLDC_Sys_Error_RotorBlock;
			else if(runMode == eBLDC_Run_Mode_COMP_INT)
				bldcSysHandler.sysErrorCode = eBLDC_Sys_Error_Commutation;
		}
}

/*******************************************************************************
 函数名称：    void TIMER0_IRQHandler(void)
 功能描述：    TIMER0中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/15      V1.0        HuangMG        创建
 *******************************************************************************/
void TIMER0_IRQHandler(void)
{

}

/*******************************************************************************
 函数名称：    void TIMER1_IRQHandler(void)
 功能描述：    TIMER1中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/4/14     V1.0          HuangMG             创建
 *******************************************************************************/
void TIMER1_IRQHandler(void)
{
//			GPIO_ResetBits(GPIO1,GPIO_Pin_5);
		/*检查是否为TIMER1的CH0比较中断*/
		if(TIMER1->IF & 0xFFFFFFFE){
			TIMER1->IF = 0x7;
			/*关闭CH0的比较中断，设置CH0的比较值,然后启动DMA传输任务*/
			TIMER1->IE &= 0xFFFFFFFE;TIMER1->CMPT0 = 40;
			/*配置DMA的传输数目并使能对应的通道*/
			DMA_CH0->DMA_CCR  &= ~BIT0; /*关闭通道使能*/
			DMA_CH0->DMA_CTMS = 16;    /*配置DMA搬运轮数或次数*/
			DMA_CH0->DMA_CCR  |= BIT0;/*使能DMA搬运*/
		}
//			GPIO_SetBits(GPIO1,GPIO_Pin_5);
}

/*******************************************************************************
 函数名称：    void SW_IRQHandler(void)
 功能描述：    软件中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/15      V1.0        HuangMG        创建
 *******************************************************************************/
void SW_IRQHandler(void)
{
}

/*******************************************************************************
 函数名称：    void CMP_IRQHandler(void)
 功能描述：    比较器中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/15      V1.0        HuangMG        创建
 *******************************************************************************/
void CMP_IRQHandler(void)
{
//		GPIO_ResetBits(GPIO1,GPIO_Pin_5);
		if(CMP->IF & BIT0){
			CMP->IF = BIT0;
			BLDC_ZeroCrossCompTask();
		}
//		GPIO_SetBits(GPIO1,GPIO_Pin_5);
}

/*******************************************************************************
 函数名称：    void UART_IRQHandler(void)
 功能描述：    UART中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/15      V1.0        HuangMG        创建
 *******************************************************************************/
void UART_IRQHandler(void)
{
}

/*******************************************************************************
 函数名称：    void SysTick_Handler(void)
 功能描述：    系统滴答定时中断
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/15      V1.0        HuangMG        创建
 *******************************************************************************/
void SysTick_Handler(void)
{
}

/*******************************************************************************
 函数名称：    void WAKE_IRQHandler(void)
 功能描述：    休眠唤醒中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/15      V1.0        HuangMG        创建
 *******************************************************************************/
void WAKE_IRQHandler(void)
{
	while (1)
		;
}

/*******************************************************************************
 函数名称：    void GPIO_IRQHandler(void)
 功能描述：    GPIO中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/15      V1.0        HuangMG        创建
 *******************************************************************************/
void GPIO_IRQHandler(void)
{

}

/*******************************************************************************
 函数名称：    void I2C_IRQHandler(void)
 功能描述：    I2C中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/15      V1.0        HuangMG        创建
 *******************************************************************************/
void I2C_IRQHandler(void)
{
}

/*******************************************************************************
 函数名称：    void SPI_IRQHandler(void)
 功能描述：    SPI中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/15      V1.0        HuangMG        创建
 *******************************************************************************/
void SPI_IRQHandler(void)
{
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */