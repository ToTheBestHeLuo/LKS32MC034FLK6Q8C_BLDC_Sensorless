#ifndef _BLDC_CONFIG_H
#define _BLDC_CONFIG_H

#include <stdint.h>

#define STI static inline

/*在这里添加用户头文件*/
#include "hardware_init.h"

/////*在这里设定BLDC的最大以及最小PWM值*/
//#define BLDC_Max_PWM_Count (+1200)
//#define BLDC_Min_PWM_Count (-1000)
///*在这里设定启动时的定位需要多少个Cycle*/
//#define BLDC_Startup_Alignment_Cycle (800)
///*在这里设定启动时的初始PWM值和初始时以及最终的周期Cycle*/
//#define BLDC_Startup_PWM_Count (-1000)
//#define BLDC_Startup_Initial_Cycle (120)
//#define BLDC_Startup_Final_Cycle (30)
///*在这里设定启动成功后占空比（油门）的响应速度，需要注意的是值不能太低，尤其是在带负载情况下，这会导致过高的响应速度，并可能导致换相错误*/
//#define BLDC_StartCompleted_SpeedUpLimit (10u)


/*在这里设定母线欠电压和过电压保护时的值*/
#define BLDC_Bus_UnderVoltage_Protect (1000u)
#define BLDC_Bus_OverVoltage_Protect (2000u)

/*下面的结构体为电机的静态参数，这部分参数的调整必须在电机运行前调整。当电机进入运行后，这些参数将被锁定。
	可以通过复位电机到停机状态后，才可以重新调整静态参数。最后，这部分参数都可以通过sG单线协议进行修改*/
typedef struct{
	/*电调的16位ID*/
	uint16_t escID;
	/*电机所能达到的最大占空比值，范围[-1200,+1200]*/
	int16_t motroDutyCycle_Max;
	/*电机所能达到的最小占空比值，范围[-1200,+1200]*/
	int16_t motroDutyCycle_Min;
	/*电机发出哔哔声的音量，也就是占空比值，且不受上面两个参数的限制，需要注意的是，过大的音量值可能导致损坏电机*/
	int16_t motorBeepVolume;
	/*开环起动，电机的起动占空比*/
	int16_t motorStartupDutyCycle;
	/*开环起动，电机的起动周期*/
	uint16_t motorStartupInitialCycle;
	/*开环起动，电机的最终周期*/
	uint16_t motorStartupFinalCycle;
	/*开环起动，电机的定位时长*/
	uint16_t motorStartupFixedCycle;
	/*开环起动，电机旋转多少个电气步数进入闭环（6个电气步数为1个完整的电气圈数）*/
	uint16_t motorStartupRotateStep;
	/*开环起动，过零信号的滤波系数，滤波时长的计算公式为：3MHz除以1+motorStartup_ZC_Filter1）再除以2^(motorStartup_ZC_Filter2)，
		motorStartup_ZC_Filter1范围[0,15],motorStartup_ZC_Filter2范围[0,7]*/
	uint8_t motorStartup_ZC_Filter1,motorStartup_ZC_Filter2;
	/*开环起动，堵转检测阈值，其频率为48MHz除以motorStartup_BlockThreshold，若未在这段时间内产生换相信号则认为产生堵转事件*/
	uint32_t motorStartup_BlockThreshold;
	/*闭环模式下，过零信号的滤波系数，滤波时长的计算公式为：3MHz除以1+motorStartup_ZC_Filter1）再除以2^(motorStartup_ZC_Filter2)*/
	uint8_t motorRun_ZC_Filter1,motorRun_ZC_Filter2;
	/*闭环模式下，电机的油门响应速度（也即占空比变化速度），指的是每个Step比较中断下油门的最大变化速度，其中第一个为加速过程、第二个为减速过程
		需要注意的是，这个值越小，响应速度越快*/
	uint8_t  mototRunThrottle_SpeedUpRate,mototRunThrottle_SlowDownRate;
	/*闭环模式下，丢步或堵转检测阈值，其频率为48MHz除以motorRun_BlockThreshold，若未在这段时间内产生换相信号则认为产生堵转事件*/
	uint32_t motorRun_BlockThreshold;
	/*闭环模式下，速度滤波器参数，其中应当满足：motorRun_SpeedFilterPar1 + motorRun_SpeedFilterPar2 = (1 << motorRun_SpeedFilterPar3)*/
	uint8_t motorRun_SpeedFilterPar1,motorRun_SpeedFilterPar2,motorRun_SpeedFilterPar3;
	/*开环起动以及闭环模式下的默认转向*/
	bool motorRun_CWCCW;
}sG_MotorParameterStruct;

typedef union{
	sG_MotorParameterStruct motorPar;
	uint8_t sector[512];
}sG_MotorFlashUnion;

extern sG_MotorFlashUnion motorFlashData;

#define PWM_PERIOD_COUNT (1200)

/*====================与硬件除法相关的函数设定=======================*/

STI int32_t BLDC_Div(int32_t dividend,int32_t divisor)
{
		DSP_DID = dividend;
		DSP_DIS = divisor;
		return DSP_QUO;
}

/*====================与温度保护相关的函数设定=======================*/

/*在这里设定指示温度过高的函数*/
STI bool BLDC_TEMP_Temperature_TooHigh(int16_t adcData)
{
		return (adcData < 1000) ? true : false;
}
/*在这里设定指示温度过低的函数*/
STI bool BLDC_TEMP_Temperature_TooLow(int16_t adcData)
{
		return (adcData > 15000) ? true : false;
}

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
		HALL->TH = motorFlashData.motorPar.motorStartup_BlockThreshold;
}
/*在这里设定HALL计数器溢出上限的函数，低阈值检测窗口*/
STI void BLDC_HALL_SetThreshold_Low(void)
{
		//设定检测窗口为1200Hz，也就是0.833ms，当0.833ms内没重置HALL的计数器，则认为产生了一次换相错误事件
		//但需要注意的是：空载情况与带桨（带负载情况下的阈值不同，用于空载和用于负载的值不可通用）
		HALL->TH = motorFlashData.motorPar.motorRun_BlockThreshold;
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
		CMP->TCLK &= ~(BIT0 | BIT1 | BIT2 | BIT4 | BIT5 | BIT6 | BIT7);
		CMP->TCLK |= (motorFlashData.motorPar.motorStartup_ZC_Filter1 << 4) | motorFlashData.motorPar.motorStartup_ZC_Filter2;
}
/*在这里设定调整COMP硬件滤波器时钟的函数：高延迟特性，用于电机闭环运行环节*/
STI void BLDC_COMP_SetFilter_HighDelay(void)
{
		CMP->TCLK &= ~(BIT0 | BIT1 | BIT2 | BIT4 | BIT5 | BIT6 | BIT7);
		CMP->TCLK |= (motorFlashData.motorPar.motorRun_ZC_Filter1 << 4) | motorFlashData.motorPar.motorRun_ZC_Filter2;
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
		eBLDC_Sys_WaitBusAndTemp,
		eBLDC_Sys_WaitCapCharge,
		eBLDC_Sys_LoadMotorParameter,
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
		int32_t commutationTime,estSpeedHz;
		uint8_t commutationFilter1,commutationFilter2,commutationScaler;
		uint32_t speedUpCycle,speedUpFinalCycle;
		uint8_t speedUpTimeCost,slowDownTimeCost;
		int16_t pwmCount,pwmCountTarget;
		BLDC_RunStatus runStatus;
		BLDC_RunMode runMode;
		uint8_t sector;
		bool CWCCW,comparePolarity;
}BLDC_SensorlessHandler;

typedef enum{
	eBLDC_Sys_Error_None = 0,
	eBLDC_Sys_Error_Bus,
	eBLDC_Sys_Error_Temp,
	eBLDC_Sys_Error_DriverBrake,
	eBLDC_Sys_Error_RotorBlock,
	eBLDC_Sys_Error_Commutation
}BLDC_Sys_Error_Code;

typedef struct{		
		BLDC_SysStatus sysStatus;
		BLDC_Sys_Error_Code sysErrorCode;
		uint32_t lowSpeedCounter;
		uint32_t highSpeedCounter;
		BLDC_ADCSensorHandler adcSensorHandler;
		BLDC_SensorlessHandler bldcSensorlessHandler;
		uint16_t counter;
}BLDC_SysHandler;

extern BLDC_SysHandler bldcSysHandler;

/*这里存放的是可供用户直接调用的函数*/

extern void BLDC_LowSpeedTask(void);
extern void BLDC_HighSpeedTask(void);
extern void BLDC_ZeroCrossCompTask(void);
extern void BLDC_DelayCommutationTask(void);

#endif


