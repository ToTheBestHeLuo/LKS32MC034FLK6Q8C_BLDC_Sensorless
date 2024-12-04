#ifndef _BLDC_CONFIG_H
#define _BLDC_CONFIG_H

#include <stdint.h>

#define STI static inline

/*在这里添加用户头文件*/
#include "hardware_init.h"
#define PWM_PERIOD_COUNT (1200)

/*在这里设定BLDC的最大以及最小PWM值*/
#define BLDC_Max_PWM_Count (+1100)
#define BLDC_Min_PWM_Count (-900)
/*在这里设定启动时的定位需要多少个Cycle*/
#define BLDC_Startup_Alignment_Cycle (400)
/*在这里设定启动时的初始PWM值和初始时以及最终的周期Cycle*/
#define BLDC_Startup_PWM_Count (-900)
#define BLDC_Startup_Initial_Cycle (100)
#define BLDC_Startup_Final_Cycle (20)
/*在这里设定启动成功后占空比（油门）的响应速度，需要注意的是值不能太低，这会导致过高的响应速度，并可能导致换相错误*/
#define BLDC_StartCompleted_SpeedUpLimit (10u)
/*在这里设定母线欠电压和过电压保护时的值*/
#define BLDC_Bus_UnderVoltage_Protect (1000u)
#define BLDC_Bus_OverVoltage_Protect (2000u)
/*在这里设定过温阈值*/
#define BLDC_Driver_Temperature_Protect (400u)

/*====================与GPIO相关的函数设定=======================*/

/*在这里设定负责电机起动与停止的按键输入*/
STI bool BLDC_GPIO_MotorControl(void)
{
		static bool status = false;
		static uint16_t timeCnt = 0u;
		if(GPIO1->PDI & BIT6) timeCnt = 0u;
		else if(timeCnt++ > 500u){timeCnt = 0u;status = true;}
	
		return status;
}

/*====================与HALL计数器相关的函数设定）=======================*/

/*在这里设定HALL计数器溢出上限的函数，高阈值检测窗口*/
STI void BLDC_HALL_SetThreshold_High(void)
{
		//设定检测窗口为50Hz，也就是20ms，当20ms内没重置HALL的计数器，则认为产生了一次堵转事件
		HALL->TH = 960000 - 1;
}
/*在这里设定HALL计数器溢出上限的函数，低阈值检测窗口*/
STI void BLDC_HALL_SetThreshold_Low(void)
{
		//设定检测窗口为1200Hz，也就是0.833ms，当0.833ms内没重置HALL的计数器，则认为产生了一次换相错误事件
		HALL->TH = 40000 - 1;
}
/*在这里设定打开HALL计数器溢出中断的函数*/
STI void BLDC_HALL_OverFlowInt_TurnOn(void)
{
		HALL->INFO |= (BIT17);
		HALL->CFG |= (BIT29);
}
/*在这里设定关闭HALL计数器溢出中断的函数*/
STI void BLDC_HALL_OverFlowInt_TurnOff(void)
{
		HALL->INFO |= (BIT17);
		HALL->CFG &= ~(BIT29);
}
/*在这里设定清除HALL计数器值的函数*/
STI void BLDC_HALL_ResetCounter(void)
{
		HALL->CNT = 0; /*写入任意值清零，只要有写的操作就行*/
}
/*在这里设定读取HALL计数器值的函数*/
STI uint32_t BLDC_HALL_GetCounter(void)
{
		return HALL->CNT;
}
/*在这里设定HALL计数器溢出阈值的函数*/
STI void BLDC_HALL_SetThreshold(uint32_t threshold)
{
		HALL->TH = threshold;
}

/*====================与COMP相关的函数设定=======================*/

/*在这里设定调整COMP硬件滤波器时钟的函数：低延迟特性，用于电机开环启动环节*/
STI void BLDC_COMP_SetFilter_LowDelay(void)
{
		CMP->TCLK &= ~(BIT0 | BIT1 | BIT2);
}
/*在这里设定调整COMP硬件滤波器时钟的函数：高延迟特性，用于电机闭环运行环节*/
STI void BLDC_COMP_SetFilter_HighDelay(void)
{
		CMP->TCLK |= (BIT0);
}
/*在这里设定获取COMP比较结果（硬件滤波后）的函数*/
STI bool BLDC_COMP_GetData_Filter(void)
{
		return (CMP->DATA & BIT8);
}
/*在这里设定打开COMP中断的函数*/
STI void BLDC_COMP_Int_TurnOn(void)
{
		CMP->IE |= BIT0;
}
/*在这里设定关闭COMP中断的函数*/
STI void BLDC_COMP_Int_TurnOff(void)
{
		CMP->IE &= ~BIT0;
}
/*在这里设定COMP为高电平有效*/
STI void BLDC_COMP_Int_SetPolarity_High(void)
{
		CMP->CFG &= ~BIT0;
}
/*在这里设定COMP为低电平有效*/
STI void BLDC_COMP_Int_SetPolarity_Low(void)
{
		CMP->CFG |= BIT0;
}
/*在这里设定获取COMP电平极型的函数*/
STI bool BLDC_COMP_GetPolarity(void)
{
		return !(CMP->CFG & BIT0);
}

/*====================与PWM相关的函数设定=======================*/

/*在这里设定打开PWM中断的函数*/
STI void BLDC_PWM_Int_TurnOn(void)
{
		MCPWM0->PWM_IE0 |= BIT13;
}
/*在这里设定关闭PWM中断的函数*/
STI void BLDC_PWM_Int_TurnOff(void)
{
		MCPWM0->PWM_IE0 &= ~BIT13;
}

/*在这里设定关闭PWM通道的函数，调整所有相的桥臂占空比为0%，需要关断PWM的通道的总开关*/
STI void BLDC_PWM_TurnOff(void)
{
    MCPWM0->PWM_PRT = 0x0000DEAD;
		MCPWM0->PWM_FAIL012 &= ~BIT6;
		MCPWM0->PWM_TH00 = MCPWM0->PWM_TH01 = (uint16_t)-PWM_PERIOD_COUNT;
		MCPWM0->PWM_TH10 = MCPWM0->PWM_TH11 = (uint16_t)-PWM_PERIOD_COUNT;
		MCPWM0->PWM_TH20 = MCPWM0->PWM_TH21 = (uint16_t)-PWM_PERIOD_COUNT;
		MCPWM0->PWM_UPDATE = 0xFFFFFFFF & ~(BIT15 | BIT14);
		MCPWM0->PWM_FAIL012 &= ~BIT6;
    MCPWM0->PWM_PRT = 0xFFFFFFFF;
}
/*在这里设定PWM三相的所有桥臂占空比为0%，需要打开PWM通道的总开关*/
STI void BLDC_PWM_TurnOn(void)
{
    MCPWM0->PWM_PRT = 0x0000DEAD;
		MCPWM0->PWM_TH00 = MCPWM0->PWM_TH01 = (uint16_t)-PWM_PERIOD_COUNT;
		MCPWM0->PWM_TH10 = MCPWM0->PWM_TH11 = (uint16_t)-PWM_PERIOD_COUNT;
		MCPWM0->PWM_TH20 = MCPWM0->PWM_TH21 = (uint16_t)-PWM_PERIOD_COUNT;
		MCPWM0->PWM_UPDATE = 0xFFFFFFFF & ~(BIT15 | BIT14);
		MCPWM0->PWM_FAIL012 |= BIT6;
    MCPWM0->PWM_PRT = 0xFFFFFFFF;
}
/*在这里设定PWM三相的所有下桥臂（占空比为100%）同时关断所有上桥臂（占空比为0%）的函数*/
STI void BLDC_PWM_LowSides_TurnOn(void)
{
		MCPWM0->PWM_TH00 = MCPWM0->PWM_TH10 = MCPWM0->PWM_TH20 = (uint16_t)-PWM_PERIOD_COUNT;
		MCPWM0->PWM_TH01 = MCPWM0->PWM_TH11 = MCPWM0->PWM_TH21 = (uint16_t)+PWM_PERIOD_COUNT;
		MCPWM0->PWM_UPDATE = 0xFFFFFFFF & ~(BIT15 | BIT14);
}
/*在这里设定PWM三相的所有上桥臂与下桥臂的占空比为0*/
STI void BLDC_PWM_AllSides_TurnOff(void)
{
		MCPWM0->PWM_TH00 = MCPWM0->PWM_TH10 = MCPWM0->PWM_TH20 = (uint16_t)-PWM_PERIOD_COUNT;
		MCPWM0->PWM_TH01 = MCPWM0->PWM_TH11 = MCPWM0->PWM_TH21 = (uint16_t)-PWM_PERIOD_COUNT;
		MCPWM0->PWM_UPDATE = 0xFFFFFFFF & ~(BIT15 | BIT14);
}
/*在这里设定UH占空比，UL=0%，VH=0%，VL=100%，WH=0%，WL=0%，同时设置比较器的正向输入端为W相浮空输入*/
STI void BLDC_PWM_UH_VL(const uint16_t pwmCount)
{
		SYS_WR_PROTECT = 0x7A83;SYS_AFE_REG1 |= (BIT10 | BIT9 | BIT8);SYS_AFE_REG1 &= ~BIT9;SYS_WR_PROTECT = 0x0000;
		MCPWM0->PWM_TH00 = pwmCount;MCPWM0->PWM_TH11 = (uint16_t)+PWM_PERIOD_COUNT;
		MCPWM0->PWM_TH01 = MCPWM0->PWM_TH10 = MCPWM0->PWM_TH20 = MCPWM0->PWM_TH21 = (uint16_t)-PWM_PERIOD_COUNT;
		MCPWM0->PWM_UPDATE = 0xFFFFFFFF & ~(BIT15 | BIT14);
}
/*在这里设定UH占空比，UL=0%，VH=0%，VL=0%，WH=0%，WL=100%，同时设置比较器的正向输入端为V相浮空输入*/
STI void BLDC_PWM_UH_WL(const uint16_t pwmCount)
{
		SYS_WR_PROTECT = 0x7A83;SYS_AFE_REG1 |= (BIT10 | BIT9 | BIT8);SYS_AFE_REG1 &= ~BIT10;SYS_WR_PROTECT = 0x0000;
		MCPWM0->PWM_TH00 = pwmCount;MCPWM0->PWM_TH21 = (uint16_t)+PWM_PERIOD_COUNT;
		MCPWM0->PWM_TH01 = MCPWM0->PWM_TH10 = MCPWM0->PWM_TH11 = MCPWM0->PWM_TH20 = (uint16_t)-PWM_PERIOD_COUNT;
		MCPWM0->PWM_UPDATE = 0xFFFFFFFF & ~(BIT15 | BIT14);	
}
/*在这里设定VH占空比，VL=0%，UH=0%，UL=100%，WH=0%，WL=0%，同时设置比较器的正向输入端为W相浮空输入*/
STI void BLDC_PWM_VH_UL(const uint16_t pwmCount)
{
		SYS_WR_PROTECT = 0x7A83;SYS_AFE_REG1 |= (BIT10 | BIT9 | BIT8);SYS_AFE_REG1 &= ~BIT9;SYS_WR_PROTECT = 0x0000;
		MCPWM0->PWM_TH10 = pwmCount;MCPWM0->PWM_TH01 = (uint16_t)+PWM_PERIOD_COUNT;
		MCPWM0->PWM_TH11 = MCPWM0->PWM_TH00 = MCPWM0->PWM_TH20 = MCPWM0->PWM_TH21 = (uint16_t)-PWM_PERIOD_COUNT;
		MCPWM0->PWM_UPDATE = 0xFFFFFFFF & ~(BIT15 | BIT14);	
}
/*在这里设定VH占空比，VL=0%，UH=0%，UL=0%，WH=0%，WL=100%，同时设置比较器的正向输入端为U相浮空输入*/
STI void BLDC_PWM_VH_WL(const uint16_t pwmCount)
{
		SYS_WR_PROTECT = 0x7A83;SYS_AFE_REG1 |= (BIT10 | BIT9 | BIT8);SYS_AFE_REG1 &= ~(BIT9 | BIT8);SYS_WR_PROTECT = 0x0000;
		MCPWM0->PWM_TH10 = pwmCount;MCPWM0->PWM_TH21 = (uint16_t)+PWM_PERIOD_COUNT;
		MCPWM0->PWM_TH11 = MCPWM0->PWM_TH00 = MCPWM0->PWM_TH01 = MCPWM0->PWM_TH20 = (uint16_t)-PWM_PERIOD_COUNT;
		MCPWM0->PWM_UPDATE = 0xFFFFFFFF & ~(BIT15 | BIT14);	
}
/*在这里设定WH占空比，WL=0%，UH=0%，UL=100%，VH=0%，VL=0%，同时设置比较器的正向输入端为V相浮空输入*/
STI void BLDC_PWM_WH_UL(const uint16_t pwmCount)
{
		SYS_WR_PROTECT = 0x7A83;SYS_AFE_REG1 |= (BIT10 | BIT9 | BIT8);SYS_AFE_REG1 &= ~BIT10;SYS_WR_PROTECT = 0x0000;
		MCPWM0->PWM_TH20 = pwmCount;MCPWM0->PWM_TH01 = (uint16_t)+PWM_PERIOD_COUNT;
		MCPWM0->PWM_TH00 = MCPWM0->PWM_TH10 = MCPWM0->PWM_TH11 = MCPWM0->PWM_TH21 = (uint16_t)-PWM_PERIOD_COUNT;
		MCPWM0->PWM_UPDATE = 0xFFFFFFFF & ~(BIT15 | BIT14);	
}
/*在这里设定WH占空比，WL=0%，UH=0%，UL=0%，VH=0%，VL=100%，同时设置比较器的正向输入端为U相浮空输入*/
STI void BLDC_PWM_WH_VL(const uint16_t pwmCount)
{
		SYS_WR_PROTECT = 0x7A83;SYS_AFE_REG1 |= (BIT10 | BIT9 | BIT8);SYS_AFE_REG1 &= ~(BIT9 | BIT8);SYS_WR_PROTECT = 0x0000;
		MCPWM0->PWM_TH20 = pwmCount;MCPWM0->PWM_TH11 = (uint16_t)+PWM_PERIOD_COUNT;
		MCPWM0->PWM_TH00 = MCPWM0->PWM_TH01 = MCPWM0->PWM_TH10 = MCPWM0->PWM_TH21 = (uint16_t)-PWM_PERIOD_COUNT;
		MCPWM0->PWM_UPDATE = 0xFFFFFFFF & ~(BIT15 | BIT14);	
}

/*====================与ADC采样相关的函数设定===================*/

/*在这里设定获取母线电压的函数*/
STI uint32_t BLDC_GetBusVoltage(void)
{
    return 1500u;
}
/*在这里设定获取母线电流的函数*/
STI uint32_t BLDC_GetBusCurrent(void)
{
		return ADC->DAT0;
}
/*在这里设定获取传感器温度的函数*/
STI uint32_t BLDC_GetDriverTemperature(void)
{
		return ADC->DAT1;
}

/*====================一些预定义的系统变量类型，请勿做修改===================*/

typedef enum{
		eBLDC_Sys_Reset = 0,
		eBLDC_Sys_WaitBus,
		eBLDC_Sys_WaitCap,
		eBLDC_Sys_WaitStart,
		eBLDC_Sys_Polling
}BLDC_SysStatus;

typedef enum{
		eBLDC_Run_Alignment = 0,
		eBLDC_Run_SpeedUp,
		eBLDC_Run_OpenLoop,
		eBLDC_Run_ReadyForCloseLoop
}BLDC_RunStatus;

typedef struct{
		int16_t adcDriverTemperatureValue,adcBusCurrent,adcBusVoltageValue;
		int16_t adcBusCurrentOffset;
}BLDC_ADCSensorHandler;

typedef enum{
	eBLDC_Run_Mode_Wait = 0,
	eBLDC_Run_Mode_COMP_Polling,
	eBLDC_Run_Mode_COMP_INT
}BLDC_RunMode;

typedef struct{
		BLDC_RunStatus runStatus;
		BLDC_RunMode runMode;
		uint32_t commutationTime;
		uint32_t speedUpCycle;
		int16_t pwmCount,pwmCountTarget;
		bool CWCCW,comparePolarity;
		uint8_t sector;
}BLDC_SensorlessHandler;

typedef enum{
	eBLDC_Sys_Error_None = 0,
	eBLDC_Sys_Error_DriverBrake,
	eBLDC_Sys_Error_RotorBlock,
	eBLDC_Sys_Error_Commutation
}BLDC_Sys_Error_Code;

typedef struct{
		BLDC_SysStatus sysStatus;
		BLDC_Sys_Error_Code sysErrorCode;
		uint32_t lowSpeedCounter;
		uint32_t highSpeedCounter;
		uint8_t counter;
		BLDC_ADCSensorHandler adcSensorHandler;
		BLDC_SensorlessHandler bldcSensorlessHandler;
}BLDC_SysHandler;

extern BLDC_SysHandler bldcSysHandler;

/*这里存放的是可供用户直接调用的函数*/

extern void BLDC_LowSpeedTask(void);
extern void BLDC_HighSpeedTask(void);
extern void BLDC_ZeroCrossCompTask(void);
extern void BLDC_DelayCommutationTask(void);

#endif


