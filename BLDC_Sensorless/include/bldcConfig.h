#ifndef _BLDC_CONFIG_H
#define _BLDC_CONFIG_H

#include <stdint.h>

#define STI static inline

/*在这里添加用户头文件*/
#include "hardware_init.h"

/*在这里设定母线欠电压和过电压保护时的值*/
#define BLDC_Bus_UnderVoltage_Protect (100)
#define BLDC_Bus_OverVoltage_Protect (200)

STI void System_Disable_sG_Int(void)
{
		NVIC_DisableIRQ(DMA_IRQn);
		NVIC_DisableIRQ(TIMER1_IRQn);
}

STI void System_Enable_sG_Int(void)
{
		NVIC_EnableIRQ(DMA_IRQn);
		NVIC_EnableIRQ(TIMER1_IRQn);
}

/*下面的结构体为电机的静态参数，这部分参数的调整必须在电机运行前调整。当电机进入运行后，这些参数将被锁定。
	可以通过复位电机到停机状态后，才可以重新调整静态参数。最后，这部分参数都可以通过sG单线协议进行修改*/
typedef struct{
	/*电调的8位ID1，不得为0*/
	uint8_t escID1;
	/*电调的8位ID2，不得为0*/
	uint8_t escID2;
	/*电调的8位ID3，不得为0*/
	uint8_t escID3;
	/*电调的8位ID4，不得为0*/
	uint8_t escID4;
	/*电机所能达到的最大占空比值，范围[1,+200]，
		实际写入为 x * 12 - 1200*/
	uint8_t motorDuty_Max;
	/*电机所能达到的最小占空比值，范围[1,+200]，
		实际写入为 x * 12 - 1200*/
	uint8_t motorDuty_Min;
	/*电机发出哔哔声的音量，也就是占空比值，且不受上面两个参数的限制，需要注意的是，过大的音量值可能导致损坏电机，范围[1,+200]，
		实际写入为 x * 12 - 1200*/
	uint8_t motorBeepVolumeDuty;
	/*开环起动，电机的起动占空比，范围[1,+200]，实际写入为 x * 12 - 1200*/
	uint8_t motorStartupDuty;
	/*开环起动，电机的起动周期，不得为0*/
	uint8_t motorStartupInitialCycle;
	/*开环起动，电机的最终周期，不得为0*/
	uint8_t motorStartupFinalCycle;
	/*开环起动，电机的定位时长，实际写入为 x * 12，不得为0*/
	uint8_t motorStartupFixedCycle;
	/*开环起动，电机旋转多少个电气步数进入闭环（6个电气步数为1个完整的电气圈数），不得为0*/
	uint8_t motorStartupRotateStep;
	/*开环起动，过零信号的滤波系数，滤波时长的计算公式为：3MHz除以1+motorStartup_ZC_Filter1）再除以2^(motorStartup_ZC_Filter2)，
		motorStartup_ZC_Filter1范围[1,15],motorStartup_ZC_Filter2范围[1,7]*/
	uint8_t motorStartup_ZC_Filter1,motorStartup_ZC_Filter2;
	/*开环起动，堵转检测阈值，其频率为48MHz除以motorStartup_BlockThreshold，若未在这段时间内产生换相信号则认为产生堵转事件,
	实际写入为 x * 75000，不得为0*/
	uint8_t motorStartup_BlockThreshold;
	/*闭环模式下，过零信号的滤波系数，滤波时长的计算公式为：3MHz除以1+motorStartup_ZC_Filter1）再除以2^(motorStartup_ZC_Filter2)，不得为0*/
	uint8_t motorRun_ZC_Filter1,motorRun_ZC_Filter2;
	/*闭环模式下，电机的油门响应速度（也即占空比变化速度），指的是每个Step比较中断下油门的最大变化速度，其中第一个为加速过程、第二个为减速过程
	需要注意的是，这个值越小，响应速度越快，不得为0*/
	uint8_t  mototRunThrottle_SpeedUpRate,mototRunThrottle_SlowDownRate;
	/*闭环模式下，丢步或堵转检测阈值，其频率为48MHz除以motorRun_BlockThreshold，若未在这段时间内产生换相信号则认为产生堵转事件，
	实际写入为 x * 750，不得为0*/
	uint8_t motorRun_BlockThreshold;
	/*闭环模式下，速度滤波器参数，其中应当满足：motorRun_SpeedFilterPar1 + motorRun_SpeedFilterPar2 = (1 << motorRun_SpeedFilterPar3)，不得为0*/
	uint8_t motorRun_SpeedFilterPar1,motorRun_SpeedFilterPar3;
	/*开环起动以及闭环模式下的默认转向，1为CW，255为CCW*/
	uint8_t motorRun_CWCCW;
}sG_MotorParameterStruct;

#define sectorSize 512
#define sectorMotorFlashAddr 0x00007C00

typedef union{
	sG_MotorParameterStruct motorPar;
	uint8_t sector[sectorSize];
}sG_MotorFlashUnion;

#define TOKENPASTE(x, y) x##y
#define UNIQUE_STATIC_ASSERT_ID TOKENPASTE(_static_assertion_, __LINE__)
#define STATIC_ASSERT(COND, MSG) typedef char __attribute__((unused)) UNIQUE_STATIC_ASSERT_ID[(COND) ? -1 : 1]

STATIC_ASSERT(sizeof(sG_MotorFlashUnion) > sectorSize,"size of sG_MotorFlashUnion shouldn't be more than 512");

extern sG_MotorFlashUnion motorFlashData;
extern const sG_MotorFlashUnion slave_MotorData_Sector;

#define PWM_PERIOD_COUNT (1200)
#define PWM_GAIN (((PWM_PERIOD_COUNT) / 200))
#define PWM_GAIN2 (1200 / (PWM_PERIOD_COUNT))

/*====================与硬件除法相关的函数设定=======================*/

STI int32_t BLDC_Div(int32_t dividend,int32_t divisor)
{
		DSP_DID = dividend;
		DSP_DIS = divisor;
		return DSP_QUO;
}

/*====================与温度保护相关的函数设定=======================*/

/*在这里设定指示温度过高的函数*/
STI bool BLDC_TEMP_Temperature_TooHigh(int32_t tmp)
{
		return (tmp > 600) ? true : false;
}
/*在这里设定指示温度过低的函数*/
STI bool BLDC_TEMP_Temperature_TooLow(int32_t tmp)
{
		return (tmp < 50) ? true : false;
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
		HALL->TH = (uint32_t)motorFlashData.motorPar.motorStartup_BlockThreshold * 75000;
}
/*在这里设定HALL计数器溢出上限的函数，低阈值检测窗口*/
STI void BLDC_HALL_SetThreshold_Low(void)
{
		//设定检测窗口为1200Hz，也就是0.833ms，当0.833ms内没重置HALL的计数器，则认为产生了一次换相错误事件
		//但需要注意的是：空载情况与带桨（带负载情况下的阈值不同，用于空载和用于负载的值不可通用）
		HALL->TH = (uint32_t)motorFlashData.motorPar.motorRun_BlockThreshold * 3000;
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

/*在这里设定调整COMP硬件滤波器时钟的函数：用于电机开环启动环节*/
STI void BLDC_COMP_SetFilter_Startup(void)
{
		CMP->TCLK &= ~(BIT0 | BIT1 | BIT2 | BIT4 | BIT5 | BIT6 | BIT7);
		CMP->TCLK |= (motorFlashData.motorPar.motorStartup_ZC_Filter1 << 4) | motorFlashData.motorPar.motorStartup_ZC_Filter2;
}
/*在这里设定调整COMP硬件滤波器时钟的函数：用于电机闭环运行环节*/
STI void BLDC_COMP_SetFilter_Run(void)
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
/*在这里设定清COMP中断标志位的函数*/
STI void BLDC_COMP_ClearIntFlag(void)
{
		CMP->IF = 0x3;
}
/*在这里设定关闭比较输入的函数*/
STI void BLDC_COMP_TurnOff(void)
{
		CMP->CFG &= ~(BIT0);
}
/*在这里设定打开比较输入的函数*/
STI void BLDC_COMP_TurnOn(void)
{
		CMP->CFG |= (BIT0);
}

/*====================与ADC采样相关的函数设定===================*/

/*在这里设定触发ADC采样的时刻的函数*/
STI void BLDC_SetADCTriggerPoint(int16_t triggerPoint)
{
		MCPWM0->PWM_TMR3 = (uint16_t)((triggerPoint * 2 - PWM_PERIOD_COUNT * 2) / 4);
}

/*在这里设定获取母线电压的函数，单位：100mV，0.1V*/
STI int32_t BLDC_GetBusVoltage(void)
{
    return ADC->DAT2 * 99 / 128;
}
/*在这里设定获取母线电流的函数，单位：100mA，0.1A*/
STI int32_t BLDC_GetBusCurrent(void)
{
		return ADC->DAT0 * 225 / 256 / 4;
}
/*在这里设定获取传感器温度的函数，单位：0.1度*/
STI int32_t BLDC_GetDriverTemperature(void)
{
    int16_t t_Temperture = (m_TempertureCof.nOffsetB - ((int32_t)m_TempertureCof.nCofA * ADC->DAT1) * 131 / 131072);
		return t_Temperture;
}

/*====================一些预定义的系统变量类型，请勿做修改===================*/

typedef enum{
		eBLDC_Sys_Reset = 0,
		eBLDC_Sys_WaitBusAndTemp,
		eBLDC_Sys_WaitCapCharge,
		eBLDC_Sys_LoadMotorParameter,
		eBLDC_Sys_StartupAudio,
		eBLDC_Sys_WaitStart,
		eBLDC_Sys_Polling
}BLDC_SysStatus;

typedef enum{
		eBLDC_Run_Audio = 0,
		eBLDC_Run_Alignment,
		eBLDC_Run_SpeedUp,
		eBLDC_Run_OpenLoop,
		eBLDC_Run_ReadyForCloseLoop,
		eBLDC_Run_CloseLoop
}BLDC_RunStatus;

typedef struct{
		int32_t adcDriverTemperatureValue,adcBusCurrent,adcBusVoltageValue;
		int32_t adcBusCurrentOffset;
}BLDC_ADCSensorHandler;

typedef enum{
	eBLDC_Run_Mode_Wait = 0,
	eBLDC_Run_Mode_COMP_Polling,
	eBLDC_Run_Mode_COMP_INT
}BLDC_RunMode;

typedef struct{
		int32_t commutationTime,estSpeedHz;
		uint8_t commutationFilter1,commutationFilter2,commutationScaler;
		uint32_t speedUpCycle,speedUpFinalCycle,rotorFixedCycle;
		uint8_t speedUpTimeCost,slowDownTimeCost;
		int16_t pwmCount,pwmCountTarget,startupRotateStep;
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
		uint32_t counter,counter1;
		uint32_t switchPhaseMask;
		BLDC_ADCSensorHandler adcSensorHandler;
		BLDC_SensorlessHandler bldcSensorlessHandler;
}BLDC_SysHandler;

typedef enum{
	eTone_None = 0,
	eTone_1,
	eTone_2,
	eTone_3,
	eTone_4,
	eTone_5,
	eTone_6,
	eTone_7
}BLDC_MotorTone;

typedef enum{
	eAudio_Init = 0,
	eAudio_WaitPlay,
	eAudio_NoPlay,
	eAudio_Finished
}BLDC_AudioStatus;

typedef struct{
		/*计数器*/
		uint16_t count;
		/*播放状态*/
		BLDC_AudioStatus audioStatus;
		/*最多支持连续播放256个音调*/
		BLDC_MotorTone* audioToPlay;
		/*一共有多少个*/
		uint8_t inTotal;
		/*当前播放到了哪里*/
		uint8_t index;
}BLDC_MotorAudioHandler;

extern bool BLDC_CheckFlashData_NoError(void);
extern void BLDC_Beep_Audio_0(void);
extern void BLDC_Beep_Audio_1(void);
extern void BLDC_Beep_Audio_2(void);
extern void BLDC_Beep_Audio_x(uint8_t which);
extern BLDC_MotorAudioHandler bldcAudioHandler;
extern BLDC_SysHandler bldcSysHandler;

/*====================与PWM相关的函数设定=======================*/

/*在这里设定打开PWM中断的函数*/
STI void BLDC_PWM_Int_TurnOn(void)
{
		MCPWM0->PWM_IE0 |= BIT0;
}
/*在这里设定关闭PWM中断的函数*/
STI void BLDC_PWM_Int_TurnOff(void)
{
		MCPWM0->PWM_IE0 &= ~BIT0;
}

#define MCPWM_UPDATE_MASK0 (0xFFFFFFFF & ~(BIT15 | BIT14))
#define MCPWM_UPDATE_MASK1 (0xFFFFFFFF)

/*在这里设定关闭PWM通道的函数，调整所有相的桥臂占空比为0%，需要关断PWM的通道的总开关*/
STI void BLDC_PWM_TurnOff(void)
{
    MCPWM0->PWM_PRT = 0x0000DEAD;
		MCPWM0->PWM_FAIL012 &= ~BIT6;
		MCPWM0->PWM_TH00 = MCPWM0->PWM_TH01 = (uint16_t)-PWM_PERIOD_COUNT;
		MCPWM0->PWM_TH10 = MCPWM0->PWM_TH11 = (uint16_t)-PWM_PERIOD_COUNT;
		MCPWM0->PWM_TH20 = MCPWM0->PWM_TH21 = (uint16_t)-PWM_PERIOD_COUNT;
		MCPWM0->PWM_UPDATE = bldcSysHandler.switchPhaseMask;
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
		MCPWM0->PWM_UPDATE = bldcSysHandler.switchPhaseMask;
		MCPWM0->PWM_FAIL012 |= BIT6;
    MCPWM0->PWM_PRT = 0xFFFFFFFF;
}
/*在这里设定PWM三相的所有下桥臂（占空比为100%）同时关断所有上桥臂（占空比为0%）的函数*/
STI void BLDC_PWM_LowSides_TurnOn(void)
{
		MCPWM0->PWM_TH00 = MCPWM0->PWM_TH10 = MCPWM0->PWM_TH20 = (uint16_t)-PWM_PERIOD_COUNT;
		MCPWM0->PWM_TH01 = MCPWM0->PWM_TH11 = MCPWM0->PWM_TH21 = (uint16_t)+PWM_PERIOD_COUNT;
		MCPWM0->PWM_UPDATE = bldcSysHandler.switchPhaseMask;
}
/*在这里设定PWM三相的所有上桥臂与下桥臂的占空比为0*/
STI void BLDC_PWM_AllSides_TurnOff(void)
{
		MCPWM0->PWM_TH00 = MCPWM0->PWM_TH10 = MCPWM0->PWM_TH20 = (uint16_t)-PWM_PERIOD_COUNT;
		MCPWM0->PWM_TH01 = MCPWM0->PWM_TH11 = MCPWM0->PWM_TH21 = (uint16_t)-PWM_PERIOD_COUNT;

		MCPWM0->PWM_UPDATE = bldcSysHandler.switchPhaseMask;
}
/*在这里设定UH占空比，UL=0%，VH=0%，VL=100%，WH=0%，WL=0%，同时设置比较器的正向输入端为W相浮空输入*/
STI void BLDC_PWM_UH_VL(const uint16_t pwmCount)
{
		SYS_WR_PROTECT = 0x7A83;SYS_AFE_REG1 |= (BIT10 | BIT9 | BIT8);SYS_AFE_REG1 &= ~BIT9;SYS_WR_PROTECT = 0x0000;
		MCPWM0->PWM_TH00 = pwmCount;MCPWM0->PWM_TH11 = (uint16_t)+PWM_PERIOD_COUNT;
		MCPWM0->PWM_TH01 = MCPWM0->PWM_TH10 = MCPWM0->PWM_TH20 = MCPWM0->PWM_TH21 = (uint16_t)-PWM_PERIOD_COUNT;
	
	
		MCPWM0->PWM_UPDATE = bldcSysHandler.switchPhaseMask;
}
/*在这里设定UH占空比，UL=0%，VH=0%，VL=0%，WH=0%，WL=100%，同时设置比较器的正向输入端为V相浮空输入*/
STI void BLDC_PWM_UH_WL(const uint16_t pwmCount)
{
		SYS_WR_PROTECT = 0x7A83;SYS_AFE_REG1 |= (BIT10 | BIT9 | BIT8);SYS_AFE_REG1 &= ~BIT10;SYS_WR_PROTECT = 0x0000;
		MCPWM0->PWM_TH00 = pwmCount;MCPWM0->PWM_TH21 = (uint16_t)+PWM_PERIOD_COUNT;
		MCPWM0->PWM_TH01 = MCPWM0->PWM_TH10 = MCPWM0->PWM_TH11 = MCPWM0->PWM_TH20 = (uint16_t)-PWM_PERIOD_COUNT;
	
		MCPWM0->PWM_UPDATE = bldcSysHandler.switchPhaseMask;	
}
/*在这里设定VH占空比，VL=0%，UH=0%，UL=100%，WH=0%，WL=0%，同时设置比较器的正向输入端为W相浮空输入*/
STI void BLDC_PWM_VH_UL(const uint16_t pwmCount)
{
		SYS_WR_PROTECT = 0x7A83;SYS_AFE_REG1 |= (BIT10 | BIT9 | BIT8);SYS_AFE_REG1 &= ~BIT9;SYS_WR_PROTECT = 0x0000;
		MCPWM0->PWM_TH10 = pwmCount;MCPWM0->PWM_TH01 = (uint16_t)+PWM_PERIOD_COUNT;
		MCPWM0->PWM_TH11 = MCPWM0->PWM_TH00 = MCPWM0->PWM_TH20 = MCPWM0->PWM_TH21 = (uint16_t)-PWM_PERIOD_COUNT;
	
		MCPWM0->PWM_UPDATE = bldcSysHandler.switchPhaseMask;	
}
/*在这里设定VH占空比，VL=0%，UH=0%，UL=0%，WH=0%，WL=100%，同时设置比较器的正向输入端为U相浮空输入*/
STI void BLDC_PWM_VH_WL(const uint16_t pwmCount)
{
		SYS_WR_PROTECT = 0x7A83;SYS_AFE_REG1 |= (BIT10 | BIT9 | BIT8);SYS_AFE_REG1 &= ~(BIT9 | BIT8);SYS_WR_PROTECT = 0x0000;
		MCPWM0->PWM_TH10 = pwmCount;MCPWM0->PWM_TH21 = (uint16_t)+PWM_PERIOD_COUNT;
		MCPWM0->PWM_TH11 = MCPWM0->PWM_TH00 = MCPWM0->PWM_TH01 = MCPWM0->PWM_TH20 = (uint16_t)-PWM_PERIOD_COUNT;
	
		MCPWM0->PWM_UPDATE = bldcSysHandler.switchPhaseMask;	
}
/*在这里设定WH占空比，WL=0%，UH=0%，UL=100%，VH=0%，VL=0%，同时设置比较器的正向输入端为V相浮空输入*/
STI void BLDC_PWM_WH_UL(const uint16_t pwmCount)
{
		SYS_WR_PROTECT = 0x7A83;SYS_AFE_REG1 |= (BIT10 | BIT9 | BIT8);SYS_AFE_REG1 &= ~BIT10;SYS_WR_PROTECT = 0x0000;
		MCPWM0->PWM_TH20 = pwmCount;MCPWM0->PWM_TH01 = (uint16_t)+PWM_PERIOD_COUNT;
		MCPWM0->PWM_TH00 = MCPWM0->PWM_TH10 = MCPWM0->PWM_TH11 = MCPWM0->PWM_TH21 = (uint16_t)-PWM_PERIOD_COUNT;
	
		MCPWM0->PWM_UPDATE = bldcSysHandler.switchPhaseMask;	
}
/*在这里设定WH占空比，WL=0%，UH=0%，UL=0%，VH=0%，VL=100%，同时设置比较器的正向输入端为U相浮空输入*/
STI void BLDC_PWM_WH_VL(const uint16_t pwmCount)
{
		SYS_WR_PROTECT = 0x7A83;SYS_AFE_REG1 |= (BIT10 | BIT9 | BIT8);SYS_AFE_REG1 &= ~(BIT9 | BIT8);SYS_WR_PROTECT = 0x0000;
		MCPWM0->PWM_TH20 = pwmCount;MCPWM0->PWM_TH11 = (uint16_t)+PWM_PERIOD_COUNT;
		MCPWM0->PWM_TH00 = MCPWM0->PWM_TH01 = MCPWM0->PWM_TH10 = MCPWM0->PWM_TH21 = (uint16_t)-PWM_PERIOD_COUNT;
	
		MCPWM0->PWM_UPDATE = bldcSysHandler.switchPhaseMask;	
}

/*这里存放的是可供用户直接调用的函数*/

extern void BLDC_LowSpeedTask(void);
extern void BLDC_HighSpeedTask(void);
extern void BLDC_ZeroCrossCompTask(void);
extern void BLDC_CommutationHallTask(void);

#endif


