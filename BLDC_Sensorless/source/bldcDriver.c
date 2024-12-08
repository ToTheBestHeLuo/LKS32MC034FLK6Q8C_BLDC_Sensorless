#include "bldcConfig.h"

/*正转换相表*/
static void (*BLDC_SwitchTableCW[])(uint16_t pwmCount) = {
		BLDC_PWM_UH_VL,
		BLDC_PWM_UH_WL,
		BLDC_PWM_VH_WL,
		BLDC_PWM_VH_UL,
		BLDC_PWM_WH_UL,
		BLDC_PWM_WH_VL
};
/*反转换相表*/
static void (*BLDC_SwitchTableCCW[])(uint16_t pwmCount) = {
		BLDC_PWM_UH_VL,
		BLDC_PWM_WH_VL,
		BLDC_PWM_WH_UL,
		BLDC_PWM_VH_UL,
		BLDC_PWM_VH_WL,
		BLDC_PWM_UH_WL
};
/*实际使用的换相表*/
static void (*BLDC_SwitchTable[6])(uint16_t pwmCount);

BLDC_SysHandler bldcSysHandler;

/*******************************************************************************
 函数名称：    static bool BLDC_Run_Mode_COMP_Polling_Commutation(void)
 功能描述：    轮询模式下，无感BLDC六步换相系统的过零检测函数，当返回true表示需要立即换相，当返回false时表示无需换相
 输入参数：    无         
 输出参数：    无
 返 回 值：    无
 其它说明：    无
 *******************************************************************************/
static bool BLDC_Run_Mode_COMP_Polling_Commutation(void)
{
		bool commutation = false;
		bool nowCompResult = BLDC_COMP_GetData_Filter();
	
		if(bldcSysHandler.bldcSensorlessHandler.comparePolarity != nowCompResult){
			bldcSysHandler.bldcSensorlessHandler.comparePolarity = nowCompResult;
			commutation = true;
		}
		return commutation;
}	
/*******************************************************************************
 函数名称：    static void BLDC_Run_Mode_COMP_Polling(void)
 功能描述：    无感BLDC六步换相系统工作在比较器轮询模式
 输入参数：    无         
 输出参数：    无
 返 回 值：    无
 其它说明：    无
 *******************************************************************************/
static void BLDC_Run_Mode_COMP_Polling(void)
{
		switch(bldcSysHandler.bldcSensorlessHandler.runStatus){
			case eBLDC_Run_Alignment:
				BLDC_SwitchTable[0]((uint16_t)BLDC_Startup_PWM_Count);
				if(bldcSysHandler.highSpeedCounter++ > 500){
					bldcSysHandler.highSpeedCounter = 0u;
					bldcSysHandler.bldcSensorlessHandler.runStatus = eBLDC_Run_SpeedUp;
				}
				break;
			case eBLDC_Run_SpeedUp:
				BLDC_SwitchTable[bldcSysHandler.bldcSensorlessHandler.sector]((uint16_t)BLDC_Startup_PWM_Count);
				if(bldcSysHandler.highSpeedCounter++ > bldcSysHandler.bldcSensorlessHandler.speedUpCycle){
					bldcSysHandler.highSpeedCounter = 0u;
					bldcSysHandler.bldcSensorlessHandler.sector = (bldcSysHandler.bldcSensorlessHandler.sector + 1) % 6;
					if(bldcSysHandler.bldcSensorlessHandler.speedUpCycle-- < BLDC_Startup_Final_Cycle){
						BLDC_COMP_SetFilter_LowDelay();
						bldcSysHandler.counter = 0u;
						
						/*在这里打开电机的堵转保护功能*/
						BLDC_HALL_SetThreshold_High();
						BLDC_HALL_ResetCounter();
						BLDC_HALL_OverFlowInt_TurnOn();
						
						bldcSysHandler.bldcSensorlessHandler.runStatus = eBLDC_Run_OpenLoop;
					}
				}
				break;
			case eBLDC_Run_OpenLoop:
				BLDC_SwitchTable[bldcSysHandler.bldcSensorlessHandler.sector]((uint16_t)BLDC_Startup_PWM_Count);
				if(bldcSysHandler.highSpeedCounter++ > bldcSysHandler.bldcSensorlessHandler.speedUpCycle){
					bldcSysHandler.highSpeedCounter = 0u;
					bldcSysHandler.bldcSensorlessHandler.sector = (bldcSysHandler.bldcSensorlessHandler.sector + 1) % 6;
				}
				if(BLDC_Run_Mode_COMP_Polling_Commutation() && ++bldcSysHandler.counter == 4u){
					BLDC_HALL_ResetCounter();
					bldcSysHandler.counter = 0u;
					bldcSysHandler.highSpeedCounter = 0u;
					bldcSysHandler.bldcSensorlessHandler.sector = (bldcSysHandler.bldcSensorlessHandler.sector + 1) % 6;
					BLDC_SwitchTable[bldcSysHandler.bldcSensorlessHandler.sector]((uint16_t)BLDC_Startup_PWM_Count);
					bldcSysHandler.bldcSensorlessHandler.runStatus = eBLDC_Run_ReadyForCloseLoop;
				}
				break;
			case eBLDC_Run_ReadyForCloseLoop:
				if(BLDC_Run_Mode_COMP_Polling_Commutation()){
					bldcSysHandler.bldcSensorlessHandler.commutationTime = BLDC_HALL_GetCounter();
					BLDC_HALL_ResetCounter();
					bldcSysHandler.counter++;
					bldcSysHandler.bldcSensorlessHandler.sector = (bldcSysHandler.bldcSensorlessHandler.sector + 1) % 6;
					BLDC_SwitchTable[bldcSysHandler.bldcSensorlessHandler.sector]((uint16_t)BLDC_Startup_PWM_Count);
				}
				if(bldcSysHandler.counter == 255){
					bldcSysHandler.counter = 0u;
					BLDC_COMP_SetFilter_HighDelay();
					bldcSysHandler.bldcSensorlessHandler.comparePolarity ? BLDC_COMP_Int_SetPolarity_Low() : BLDC_COMP_Int_SetPolarity_High();
					bldcSysHandler.bldcSensorlessHandler.runMode = eBLDC_Run_Mode_COMP_INT;
					BLDC_PWM_Int_TurnOff();
					CMP->IF = (BIT0 | BIT1);
					BLDC_HALL_ResetCounter();
					BLDC_HALL_SetThreshold_Low();
					BLDC_COMP_Int_TurnOn();
				}
				break;
			default:
				while(1);
		}
}
/*******************************************************************************
 函数名称：    static void BLDC_Run_Mode_COMP_Int(void)
 功能描述：    无感BLDC六步换相系统工作在比较器中断模式，用以确定过零点
 输入参数：    无         
 输出参数：    无
 返 回 值：    无
 其它说明：    无
 *******************************************************************************/
static void BLDC_Run_Mode_COMP_Int(void)
{
		bldcSysHandler.bldcSensorlessHandler.sector = (bldcSysHandler.bldcSensorlessHandler.sector + 1) % 6;
		BLDC_SwitchTable[bldcSysHandler.bldcSensorlessHandler.sector]((uint16_t)bldcSysHandler.bldcSensorlessHandler.pwmCount);
	
		BLDC_COMP_Int_TurnOff();
		CMP->IF = 0x3;
	
		bldcSysHandler.bldcSensorlessHandler.commutationTime = BLDC_HALL_GetCounter();
		BLDC_HALL_ResetCounter();
	
		BLDC_COMP_GetPolarity() ? BLDC_COMP_Int_SetPolarity_Low() : BLDC_COMP_Int_SetPolarity_High();
	
		if(bldcSysHandler.bldcSensorlessHandler.pwmCount < bldcSysHandler.bldcSensorlessHandler.pwmCountTarget && bldcSysHandler.counter++ > BLDC_StartCompleted_SpeedUpLimit){
			bldcSysHandler.counter = 0u;
			bldcSysHandler.bldcSensorlessHandler.pwmCount++;
		}else if(bldcSysHandler.bldcSensorlessHandler.pwmCount > bldcSysHandler.bldcSensorlessHandler.pwmCountTarget && bldcSysHandler.counter++ > BLDC_StartCompleted_SpeedUpLimit){
			bldcSysHandler.counter = 0u;
			bldcSysHandler.bldcSensorlessHandler.pwmCount--;
		}

		BLDC_COMP_Int_TurnOn();
}
/*******************************************************************************
 函数名称：    static void BLDC_SysReset(void)
 功能描述：    无感BLDC六步换相系统复位函数，主要负责一些变量的初始化
 输入参数：    无         
 输出参数：    无
 返 回 值：    无
 其它说明：    无
 *******************************************************************************/
static void BLDC_SysReset(void)
{
		bldcSysHandler.sysStatus = eBLDC_Sys_Reset;
		bldcSysHandler.sysErrorCode = eBLDC_Sys_Error_None;
		bldcSysHandler.lowSpeedCounter = 0u;
		bldcSysHandler.highSpeedCounter = 0u;
		bldcSysHandler.counter = 0u;
	
		bldcSysHandler.bldcSensorlessHandler.sector = 0u;
		bldcSysHandler.bldcSensorlessHandler.runStatus = eBLDC_Run_Alignment;
		bldcSysHandler.bldcSensorlessHandler.runMode = eBLDC_Run_Mode_Wait;
		bldcSysHandler.bldcSensorlessHandler.speedUpCycle = BLDC_Startup_Initial_Cycle;
		bldcSysHandler.bldcSensorlessHandler.pwmCount = BLDC_Startup_PWM_Count;
		bldcSysHandler.bldcSensorlessHandler.pwmCountTarget = BLDC_Startup_PWM_Count;
		bldcSysHandler.bldcSensorlessHandler.CWCCW = true;
		bldcSysHandler.bldcSensorlessHandler.comparePolarity = true;
		bldcSysHandler.bldcSensorlessHandler.commutationTime = 0u;
	
		bldcSysHandler.adcSensorHandler.adcBusVoltageValue = 0;
		bldcSysHandler.adcSensorHandler.adcDriverTemperatureValue = 0;
		bldcSysHandler.adcSensorHandler.adcBusCurrent = 0;
		bldcSysHandler.adcSensorHandler.adcBusCurrentOffset = 0;
	
		if(bldcSysHandler.bldcSensorlessHandler.CWCCW){
			BLDC_SwitchTable[0] = BLDC_SwitchTableCW[0];
			BLDC_SwitchTable[1] = BLDC_SwitchTableCW[1];
			BLDC_SwitchTable[2] = BLDC_SwitchTableCW[2];
			BLDC_SwitchTable[3] = BLDC_SwitchTableCW[3];
			BLDC_SwitchTable[4] = BLDC_SwitchTableCW[4];
			BLDC_SwitchTable[5] = BLDC_SwitchTableCW[5];
		}else{
			BLDC_SwitchTable[0] = BLDC_SwitchTableCCW[0];
			BLDC_SwitchTable[1] = BLDC_SwitchTableCCW[1];
			BLDC_SwitchTable[2] = BLDC_SwitchTableCCW[2];
			BLDC_SwitchTable[3] = BLDC_SwitchTableCCW[3];
			BLDC_SwitchTable[4] = BLDC_SwitchTableCCW[4];
			BLDC_SwitchTable[5] = BLDC_SwitchTableCCW[5];
		}
}
/*******************************************************************************
 函数名称：    void BLDC_LowSpeedTask(void)
 功能描述：    无感BLDC六步换相低速时钟任务，主要负责处理一些安全任务和低速通信任务
 输入参数：    无         
 输出参数：    无
 返 回 值：    无
 其它说明：    由ADC完成中断进行调用，中断优先级小于高速时钟任务
 *******************************************************************************/
void BLDC_LowSpeedTask(void)
{
		static int32_t busCurrentOffset = 0;
		static uint16_t busErrorCnt = 0u,tempErrorCnt = 0u;
		BLDC_SysStatus status = bldcSysHandler.sysStatus;
		bldcSysHandler.adcSensorHandler.adcBusVoltageValue = BLDC_GetBusVoltage();
		bldcSysHandler.adcSensorHandler.adcDriverTemperatureValue = BLDC_GetDriverTemperature();
		bldcSysHandler.adcSensorHandler.adcBusCurrent = BLDC_GetBusCurrent() - bldcSysHandler.adcSensorHandler.adcBusCurrentOffset;
		switch(status){
			case eBLDC_Sys_Reset:
				BLDC_PWM_Int_TurnOn();
				BLDC_COMP_Int_TurnOff();
				BLDC_HALL_OverFlowInt_TurnOff();
				busCurrentOffset = 0;
				BLDC_SysReset();
				bldcSysHandler.sysStatus = eBLDC_Sys_WaitBusAndTemp;
				break;
			case eBLDC_Sys_WaitBusAndTemp:
				if(bldcSysHandler.adcSensorHandler.adcBusVoltageValue > BLDC_Bus_UnderVoltage_Protect &&  \
						bldcSysHandler.adcSensorHandler.adcBusVoltageValue < BLDC_Bus_OverVoltage_Protect && \
						!BLDC_TEMP_Temperature_TooHigh(bldcSysHandler.adcSensorHandler.adcDriverTemperatureValue) && \
						!BLDC_TEMP_Temperature_TooLow(bldcSysHandler.adcSensorHandler.adcDriverTemperatureValue)){
					if(bldcSysHandler.lowSpeedCounter++ > 500u){
						BLDC_PWM_TurnOn();
						BLDC_PWM_LowSides_TurnOn();
						bldcSysHandler.lowSpeedCounter = 0u;
						bldcSysHandler.sysStatus = eBLDC_Sys_WaitCapCharge;
					}
				}else bldcSysHandler.lowSpeedCounter = 0u;
				break;
			case eBLDC_Sys_WaitCapCharge:
				busCurrentOffset += bldcSysHandler.adcSensorHandler.adcBusCurrent;
				if(bldcSysHandler.lowSpeedCounter++ > 127){
					bldcSysHandler.adcSensorHandler.adcBusCurrentOffset = busCurrentOffset / 128;
					bldcSysHandler.lowSpeedCounter = 0u;
					BLDC_PWM_AllSides_TurnOff();
					bldcSysHandler.sysStatus = eBLDC_Sys_WaitStart;
				}
				break;
			case eBLDC_Sys_WaitStart:
				if(BLDC_GPIO_MotorControl()){
					bldcSysHandler.bldcSensorlessHandler.runMode = eBLDC_Run_Mode_COMP_Polling;
					bldcSysHandler.sysStatus = eBLDC_Sys_Polling;
				}
				break;
			case eBLDC_Sys_Polling:
				if(bldcSysHandler.adcSensorHandler.adcBusVoltageValue < BLDC_Bus_UnderVoltage_Protect || bldcSysHandler.adcSensorHandler.adcBusVoltageValue > BLDC_Bus_OverVoltage_Protect){
					if(busErrorCnt++ > 100u){
						BLDC_PWM_TurnOff();
						bldcSysHandler.sysErrorCode = eBLDC_Sys_Error_Bus;
						busErrorCnt = 0u;
						bldcSysHandler.sysStatus = eBLDC_Sys_Reset;
					}
				}else busErrorCnt = 0u;
				
				if(BLDC_TEMP_Temperature_TooHigh(bldcSysHandler.adcSensorHandler.adcDriverTemperatureValue)){
					if(tempErrorCnt++ > 100u){
						BLDC_PWM_TurnOff();
						bldcSysHandler.sysErrorCode = eBLDC_Sys_Error_Temp;
						tempErrorCnt = 0u;
						bldcSysHandler.sysStatus = eBLDC_Sys_Reset;
					}
				}else if(BLDC_TEMP_Temperature_TooLow(bldcSysHandler.adcSensorHandler.adcDriverTemperatureValue)){
					/*程序不应当跑入这里，暂时也没考虑如此低的工作温度*/
					while(1);
				}else tempErrorCnt = 0u;
				
				if(!BLDC_GPIO_MotorControl()){
					BLDC_PWM_TurnOff();
					bldcSysHandler.lowSpeedCounter = 0u;
					bldcSysHandler.sysStatus = eBLDC_Sys_Reset;
				}
				
				if(bldcSysHandler.sysErrorCode != eBLDC_Sys_Error_None)	
					bldcSysHandler.sysStatus = eBLDC_Sys_Reset;
				break;
			default:
				while(1);
		}
}
/*******************************************************************************
 函数名称：    void BLDC_HighSpeedTask(void)
 功能描述：    无感BLDC六步换相高速时钟任务，主要负责一系列电机起动以及换相等任务
 输入参数：    无         
 输出参数：    无
 返 回 值：    无
 其它说明：    由MCPWM中断进行调用，中断优先级高于低速时钟任务
 *******************************************************************************/
void BLDC_HighSpeedTask(void)
{	
		if(bldcSysHandler.bldcSensorlessHandler.runMode == eBLDC_Run_Mode_COMP_Polling && bldcSysHandler.sysErrorCode == eBLDC_Sys_Error_None){
			BLDC_Run_Mode_COMP_Polling();
		}else return;
}
/*******************************************************************************
 函数名称：    void BLDC_ZeroCrossCompTask(void)
 功能描述：    无感BLDC六步换相比较器过零信号任务，主要负责闭环下的电机高速运行任务
 输入参数：    无         
 输出参数：    无
 返 回 值：    无
 其它说明：    由COMP边沿中断进行调用，中断优先级与MCPWM中断同等级
 *******************************************************************************/
void BLDC_ZeroCrossCompTask(void)
{
		if(bldcSysHandler.bldcSensorlessHandler.runMode == eBLDC_Run_Mode_COMP_INT && bldcSysHandler.sysErrorCode == eBLDC_Sys_Error_None){
			BLDC_Run_Mode_COMP_Int();
		}else return;
}

