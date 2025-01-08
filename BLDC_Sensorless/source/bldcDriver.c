#include "bldcConfig.h"

BLDC_SysHandler bldcSysHandler;

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

sG_MotorFlashUnion motorFlashData;

/*******************************************************************************
 函数名称：    static void BLDC_LoadFlashData_Static(void)
 功能描述：    从Flash区域（类似于EEPROM区域）加载数据到motorFlashData
 其它说明：    无
 *******************************************************************************/
static void BLDC_LoadFlashData_Static(void)
{
		/*目前先做测试，直接为给定值*/
		const sG_MotorParameterStruct motorPar = {
			.escID = 0x1234,
			.motroDutyCycle_Max = 1200,
			.motroDutyCycle_Min = -1000,
			.motorBeepVolume = -1000,
			.motorStartupDutyCycle = -1000,
			.motorStartupInitialCycle = 120,
			.motorStartupFinalCycle = 20,
			.motorStartupFixedCycle = 800,
			.motorStartupRotateStep = 255,
			.motorStartup_ZC_Filter1 = 5,
			.motorStartup_ZC_Filter2 = 0,
			.motorStartup_BlockThreshold = 960000 - 1,
			.motorRun_ZC_Filter1 = 5,
			.motorRun_ZC_Filter2 = 1,
			.mototRunThrottle_SpeedUpRate = 10,
			.mototRunThrottle_SlowDownRate = 10,
			.motorRun_BlockThreshold = 60000 - 1,
			.motorRun_SpeedFilterPar1 = 4,
			.motorRun_SpeedFilterPar2 = 60,
			.motorRun_SpeedFilterPar3 = 6,
			.motorRun_CWCCW = true
		};
		
		motorFlashData.motorPar = motorPar;
		
		/*检查占空比数据是否合法*/
		if(motorFlashData.motorPar.motroDutyCycle_Max < motorFlashData.motorPar.motroDutyCycle_Min){
			int16_t tmp = motorFlashData.motorPar.motroDutyCycle_Min;
			motorFlashData.motorPar.motroDutyCycle_Min = motorFlashData.motorPar.motroDutyCycle_Max;
			motorFlashData.motorPar.motroDutyCycle_Max = tmp;
		}
		if(motorFlashData.motorPar.motroDutyCycle_Max > 1200) motorFlashData.motorPar.motroDutyCycle_Max = 1200;
		if(motorFlashData.motorPar.motroDutyCycle_Min < -1200) motorFlashData.motorPar.motroDutyCycle_Min = -1200;
		
		/*检查起动占空比是否合法，如果不合法，给定一个默认值*/
		if(motorFlashData.motorPar.motorStartupDutyCycle < -1200 || motorFlashData.motorPar.motorStartupDutyCycle > 1200){
			motorFlashData.motorPar.motorStartupDutyCycle = -1150;
		}
		
		/*检查ZC滤波器参数*/
		if(motorFlashData.motorPar.motorStartup_ZC_Filter1 > 15){
			motorFlashData.motorPar.motorStartup_ZC_Filter1 = 15;
		}
		if(motorFlashData.motorPar.motorStartup_ZC_Filter2 > 7){
			motorFlashData.motorPar.motorStartup_ZC_Filter2 = 7;
		}
		if(motorFlashData.motorPar.motorRun_ZC_Filter1 > 15){
			motorFlashData.motorPar.motorRun_ZC_Filter1 = 15;
		}
		if(motorFlashData.motorPar.motorRun_ZC_Filter2 > 7){
			motorFlashData.motorPar.motorRun_ZC_Filter1 = 7;
		}		
		
		/*检查速度滤波器参数，如果不合法，则给定一个默认值*/
		if(motorFlashData.motorPar.motorRun_SpeedFilterPar1 + motorFlashData.motorPar.motorRun_SpeedFilterPar2 != (1 << motorFlashData.motorPar.motorRun_SpeedFilterPar3)){
			motorFlashData.motorPar.motorRun_SpeedFilterPar1 = 4;
			motorFlashData.motorPar.motorRun_SpeedFilterPar2 = 64;
			motorFlashData.motorPar.motorRun_SpeedFilterPar3 = 6;
		}
		
		/*将参数写入控制系统*/
		bldcSysHandler.bldcSensorlessHandler.speedUpCycle = motorFlashData.motorPar.motorStartupInitialCycle;
		bldcSysHandler.bldcSensorlessHandler.speedUpFinalCycle = motorFlashData.motorPar.motorStartupFinalCycle;
		bldcSysHandler.bldcSensorlessHandler.speedUpTimeCost = motorFlashData.motorPar.mototRunThrottle_SpeedUpRate;
		bldcSysHandler.bldcSensorlessHandler.slowDownTimeCost = motorFlashData.motorPar.mototRunThrottle_SlowDownRate;
		bldcSysHandler.bldcSensorlessHandler.pwmCount = motorFlashData.motorPar.motorStartupDutyCycle;
		bldcSysHandler.bldcSensorlessHandler.pwmCountTarget = motorFlashData.motorPar.motorStartupDutyCycle;
		bldcSysHandler.bldcSensorlessHandler.CWCCW = motorFlashData.motorPar.motorRun_CWCCW;
		
		bldcSysHandler.bldcSensorlessHandler.commutationFilter1 = motorFlashData.motorPar.motorRun_SpeedFilterPar1;
		bldcSysHandler.bldcSensorlessHandler.commutationFilter2 = motorFlashData.motorPar.motorRun_SpeedFilterPar2;
		bldcSysHandler.bldcSensorlessHandler.commutationScaler = motorFlashData.motorPar.motorRun_SpeedFilterPar3;
		
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

BLDC_MotorAudioHandler bldcAudioHandler;

static const uint8_t audioTone[] = {
	76,68,61,57,51,45,40
};

const BLDC_MotorTone motorAudio_0[7 * 4] = {
	eTone_1,eTone_1,eTone_1,eTone_1,eTone_1,eTone_1,eTone_1,
	eTone_1,eTone_1,eTone_1,eTone_1,eTone_1,eTone_1,eTone_1,
	eTone_1,eTone_1,eTone_1,eTone_1,eTone_1,eTone_1,eTone_1,
	eTone_1,eTone_1,eTone_1,eTone_1,eTone_1,eTone_1,eTone_1
};

const BLDC_MotorTone motorAudio_1[7 * 4] = {
	eTone_2,eTone_2,eTone_2,eTone_2,eTone_2,eTone_2,eTone_2,
	eTone_2,eTone_2,eTone_2,eTone_2,eTone_2,eTone_2,eTone_2,
	eTone_2,eTone_2,eTone_2,eTone_2,eTone_2,eTone_2,eTone_2,
	eTone_2,eTone_2,eTone_2,eTone_2,eTone_2,eTone_2,eTone_2
};

const BLDC_MotorTone motorAudio_2[7 * 4] = {
	eTone_3,eTone_3,eTone_3,eTone_3,eTone_3,eTone_3,eTone_3,
	eTone_3,eTone_3,eTone_3,eTone_3,eTone_3,eTone_3,eTone_3,
	eTone_3,eTone_3,eTone_3,eTone_3,eTone_3,eTone_3,eTone_3,
	eTone_3,eTone_3,eTone_3,eTone_3,eTone_3,eTone_3,eTone_3
};

const BLDC_MotorTone motorAudio_3[7 * 4] = {
	eTone_1,eTone_3,eTone_3,eTone_3,eTone_3,eTone_6,eTone_3,
	eTone_1,eTone_4,eTone_3,eTone_2,eTone_5,eTone_3,eTone_1,
	eTone_1,eTone_2,eTone_7,eTone_3,eTone_2,eTone_7,eTone_3,
	eTone_1,eTone_6,eTone_3,eTone_4,eTone_4,eTone_5,eTone_1
};

/*******************************************************************************
 函数名称：    bool BLDC_AudioInit(BLDC_MotorTone* audioToPlay,uint8_t toneNums)
 功能描述：    无
 其它说明：    最多支持256个tone
 *******************************************************************************/
bool BLDC_AudioInit(BLDC_MotorTone* audioToPlay,uint8_t toneNums)
{
		if((uint32_t)audioToPlay == 0) return false;
	
		if(bldcAudioHandler.audioStatus == eAudio_Init){
			bldcAudioHandler.audioToPlay = audioToPlay;
			bldcAudioHandler.inTotal = toneNums;
			bldcAudioHandler.index = 0;
			bldcAudioHandler.audioStatus = eAudio_WaitPlay;
			return true;
		}
		
		return false;
}

/*******************************************************************************
 函数名称：    static bool BLDC_Run_Mode_COMP_Polling_Commutation(void)
 功能描述：    轮询模式下，无感BLDC六步换相系统的过零检测函数，当返回true表示需要立即换相，当返回false时表示无需换相
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
 其它说明：    无
 *******************************************************************************/
static void BLDC_Run_Mode_COMP_Polling(void)
{
		switch(bldcSysHandler.bldcSensorlessHandler.runStatus){
			case eBLDC_Run_Audio:
				if(bldcAudioHandler.audioStatus == eAudio_WaitPlay){
					BLDC_SwitchTable[0]((uint16_t)motorFlashData.motorPar.motorBeepVolume);
					bldcAudioHandler.audioStatus = eAudio_NoPlay;
				}else if(bldcAudioHandler.audioStatus == eAudio_NoPlay){
					BLDC_SwitchTable[0]((uint16_t)-1200);
					bldcSysHandler.highSpeedCounter++;
					if(bldcSysHandler.highSpeedCounter == audioTone[bldcAudioHandler.audioToPlay[bldcAudioHandler.index]]){
						bldcSysHandler.highSpeedCounter = 0;
						bldcAudioHandler.count++;
						if(bldcAudioHandler.count == 1){
							bldcAudioHandler.count = 0;
							bldcAudioHandler.index++;
							if(bldcAudioHandler.index == bldcAudioHandler.inTotal){
								bldcAudioHandler.index = 0;
								bldcAudioHandler.audioStatus = eAudio_Finished;
							}else{
								bldcAudioHandler.audioStatus = eAudio_WaitPlay;
							}
						}
					}
				}else if(bldcAudioHandler.audioStatus == eAudio_Finished){
					if(bldcSysHandler.highSpeedCounter++ == 5000){
						bldcAudioHandler.audioStatus = eAudio_Init;
						bldcSysHandler.highSpeedCounter = 0;
						BLDC_AudioInit((BLDC_MotorTone*)motorAudio_1,28);
					}
				}
				break;
			case eBLDC_Run_Alignment:
				BLDC_SwitchTable[0]((uint16_t)bldcSysHandler.bldcSensorlessHandler.pwmCount);
				if(bldcSysHandler.highSpeedCounter++ > 500){
					bldcSysHandler.highSpeedCounter = 0u;
					bldcSysHandler.bldcSensorlessHandler.runStatus = eBLDC_Run_SpeedUp;
				}
				break;
			case eBLDC_Run_SpeedUp:
				BLDC_SwitchTable[bldcSysHandler.bldcSensorlessHandler.sector]((uint16_t)bldcSysHandler.bldcSensorlessHandler.pwmCount);
				if(bldcSysHandler.highSpeedCounter++ > bldcSysHandler.bldcSensorlessHandler.speedUpCycle){
					bldcSysHandler.highSpeedCounter = 0u;
					bldcSysHandler.bldcSensorlessHandler.sector = (bldcSysHandler.bldcSensorlessHandler.sector + 1) % 6;
					if(bldcSysHandler.bldcSensorlessHandler.speedUpCycle-- < bldcSysHandler.bldcSensorlessHandler.speedUpFinalCycle){
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
				BLDC_SwitchTable[bldcSysHandler.bldcSensorlessHandler.sector]((uint16_t)bldcSysHandler.bldcSensorlessHandler.pwmCount);
				if(bldcSysHandler.highSpeedCounter++ > bldcSysHandler.bldcSensorlessHandler.speedUpCycle){
					bldcSysHandler.highSpeedCounter = 0u;
					bldcSysHandler.bldcSensorlessHandler.sector = (bldcSysHandler.bldcSensorlessHandler.sector + 1) % 6;
				}
				if(BLDC_Run_Mode_COMP_Polling_Commutation() && ++bldcSysHandler.counter == 4u){
					BLDC_HALL_ResetCounter();
					bldcSysHandler.counter = 0u;
					bldcSysHandler.highSpeedCounter = 0u;
					bldcSysHandler.bldcSensorlessHandler.sector = (bldcSysHandler.bldcSensorlessHandler.sector + 1) % 6;
					BLDC_SwitchTable[bldcSysHandler.bldcSensorlessHandler.sector]((uint16_t)bldcSysHandler.bldcSensorlessHandler.pwmCount);
					bldcSysHandler.bldcSensorlessHandler.runStatus = eBLDC_Run_ReadyForCloseLoop;
				}
				break;
			case eBLDC_Run_ReadyForCloseLoop:
				if(BLDC_Run_Mode_COMP_Polling_Commutation()){
					bldcSysHandler.bldcSensorlessHandler.commutationTime = (BLDC_HALL_GetCounter() * bldcSysHandler.bldcSensorlessHandler.commutationFilter1 \
																																	+ bldcSysHandler.bldcSensorlessHandler.commutationFilter2 * bldcSysHandler.bldcSensorlessHandler.commutationTime) \
																																	>> bldcSysHandler.bldcSensorlessHandler.commutationScaler;
					bldcSysHandler.bldcSensorlessHandler.estSpeedHz = BLDC_Div(8000000,bldcSysHandler.bldcSensorlessHandler.commutationTime);
					BLDC_HALL_ResetCounter();
					bldcSysHandler.counter++;
					bldcSysHandler.bldcSensorlessHandler.sector = (bldcSysHandler.bldcSensorlessHandler.sector + 1) % 6;
					BLDC_SwitchTable[bldcSysHandler.bldcSensorlessHandler.sector]((uint16_t)bldcSysHandler.bldcSensorlessHandler.pwmCount);
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
 其它说明：    无
 *******************************************************************************/
static void BLDC_Run_Mode_COMP_Int(void)
{
		bldcSysHandler.bldcSensorlessHandler.sector = (bldcSysHandler.bldcSensorlessHandler.sector + 1) % 6;
		BLDC_SwitchTable[bldcSysHandler.bldcSensorlessHandler.sector]((uint16_t)bldcSysHandler.bldcSensorlessHandler.pwmCount);
	
		BLDC_COMP_Int_TurnOff();
		CMP->IF = 0x3;
	
		bldcSysHandler.bldcSensorlessHandler.commutationTime = (BLDC_HALL_GetCounter() * bldcSysHandler.bldcSensorlessHandler.commutationFilter1 \
																														+ bldcSysHandler.bldcSensorlessHandler.commutationFilter2 * bldcSysHandler.bldcSensorlessHandler.commutationTime) \
																														>> bldcSysHandler.bldcSensorlessHandler.commutationScaler;
		bldcSysHandler.bldcSensorlessHandler.estSpeedHz = BLDC_Div(8000000,bldcSysHandler.bldcSensorlessHandler.commutationTime);
	
		BLDC_HALL_ResetCounter();
	
		BLDC_COMP_GetPolarity() ? BLDC_COMP_Int_SetPolarity_Low() : BLDC_COMP_Int_SetPolarity_High();
	
		if(bldcSysHandler.bldcSensorlessHandler.pwmCount < bldcSysHandler.bldcSensorlessHandler.pwmCountTarget && bldcSysHandler.counter++ > bldcSysHandler.bldcSensorlessHandler.speedUpTimeCost){
			bldcSysHandler.counter = 0u;
			bldcSysHandler.bldcSensorlessHandler.pwmCount++;
		}else if(bldcSysHandler.bldcSensorlessHandler.pwmCount > bldcSysHandler.bldcSensorlessHandler.pwmCountTarget && bldcSysHandler.counter++ > bldcSysHandler.bldcSensorlessHandler.slowDownTimeCost){
			bldcSysHandler.counter = 0u;
			bldcSysHandler.bldcSensorlessHandler.pwmCount--;
		}

		BLDC_COMP_Int_TurnOn();
}
/*******************************************************************************
 函数名称：    static void BLDC_SysReset(void)
 功能描述：    无感BLDC六步换相系统复位函数，主要负责一些变量的初始化
 其它说明：    部分参数的复位值是没有效果的，因为后续会重新从内存区域加载相应的变量，从而覆盖掉复位值
 *******************************************************************************/
static void BLDC_SysReset(void)
{
		/*复位bldcSysHandler*/
		bldcSysHandler.sysStatus = eBLDC_Sys_Reset;
		bldcSysHandler.sysErrorCode = eBLDC_Sys_Error_None;
		bldcSysHandler.lowSpeedCounter = 0u;
		bldcSysHandler.highSpeedCounter = 0u;
		bldcSysHandler.counter = 0u;
	
		bldcSysHandler.bldcSensorlessHandler.sector = 0u;
		bldcSysHandler.bldcSensorlessHandler.runStatus = eBLDC_Run_Audio;
		bldcSysHandler.bldcSensorlessHandler.runMode = eBLDC_Run_Mode_Wait;
		bldcSysHandler.bldcSensorlessHandler.comparePolarity = true;
		bldcSysHandler.bldcSensorlessHandler.commutationTime = 0;
		bldcSysHandler.bldcSensorlessHandler.estSpeedHz = 0;
	
		bldcSysHandler.bldcSensorlessHandler.speedUpCycle = 0;
		bldcSysHandler.bldcSensorlessHandler.speedUpFinalCycle = 0;
		bldcSysHandler.bldcSensorlessHandler.speedUpTimeCost = 0;
		bldcSysHandler.bldcSensorlessHandler.slowDownTimeCost = 0;
		bldcSysHandler.bldcSensorlessHandler.pwmCount = 0;
		bldcSysHandler.bldcSensorlessHandler.pwmCountTarget = 0;
		bldcSysHandler.bldcSensorlessHandler.CWCCW = true;
		bldcSysHandler.bldcSensorlessHandler.commutationFilter1 = 4;
		bldcSysHandler.bldcSensorlessHandler.commutationFilter2 = 60;
		bldcSysHandler.bldcSensorlessHandler.commutationScaler = 6;
	
		bldcSysHandler.adcSensorHandler.adcBusVoltageValue = 0;
		bldcSysHandler.adcSensorHandler.adcDriverTemperatureValue = 0;
		bldcSysHandler.adcSensorHandler.adcBusCurrent = 0;
		bldcSysHandler.adcSensorHandler.adcBusCurrentOffset = 0;
		
		/*复位bldcAudioHandler*/
		bldcAudioHandler.audioToPlay = (BLDC_MotorTone*)0;
		bldcAudioHandler.index = 0;
		bldcAudioHandler.inTotal = 0;
		bldcAudioHandler.count = 0;
		bldcAudioHandler.audioStatus = eAudio_Init;
		
		/**/
		BLDC_AudioInit((BLDC_MotorTone*)motorAudio_0,28);
}
/*******************************************************************************
 函数名称：    void BLDC_LowSpeedTask(void)
 功能描述：    无感BLDC六步换相低速时钟任务，主要负责处理一些安全任务和低速通信任务
 其它说明：    由ADC完成中断进行调用，中断优先级小于高速时钟任务
 *******************************************************************************/
void BLDC_LowSpeedTask(void)
{
		static int32_t busCurrentOffset = 0;
		static uint16_t busErrorCnt = 0u,tempErrorCnt = 0u;

		BLDC_SysStatus status = bldcSysHandler.sysStatus;
		bldcSysHandler.adcSensorHandler.adcBusVoltageValue = (BLDC_GetBusVoltage() * 4 + bldcSysHandler.adcSensorHandler.adcBusVoltageValue * 60) / 64;
		bldcSysHandler.adcSensorHandler.adcDriverTemperatureValue = BLDC_GetDriverTemperature();
	
		int16_t busCurrent = BLDC_GetBusCurrent() - bldcSysHandler.adcSensorHandler.adcBusCurrentOffset;
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
				busCurrentOffset += busCurrent;
				if(bldcSysHandler.lowSpeedCounter++ > 127){
					bldcSysHandler.adcSensorHandler.adcBusCurrentOffset = busCurrentOffset / 128;
					bldcSysHandler.lowSpeedCounter = 0u;
					BLDC_PWM_AllSides_TurnOff();
					bldcSysHandler.sysStatus = eBLDC_Sys_LoadMotorParameter;
				}
				break;
			case eBLDC_Sys_LoadMotorParameter:
				BLDC_LoadFlashData_Static();
				bldcSysHandler.sysStatus = eBLDC_Sys_WaitStart;
				break;
			case eBLDC_Sys_WaitStart:
				if(BLDC_GPIO_MotorControl()){
					bldcSysHandler.bldcSensorlessHandler.runMode = eBLDC_Run_Mode_COMP_Polling;
					bldcSysHandler.sysStatus = eBLDC_Sys_Polling;
				}
				break;
			case eBLDC_Sys_Polling:
			
				bldcSysHandler.adcSensorHandler.adcBusCurrent = (busCurrent * 4 + bldcSysHandler.adcSensorHandler.adcBusCurrent * 60) / 64;
			
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
 其它说明：    由COMP边沿中断进行调用，中断优先级与MCPWM中断同等级
 *******************************************************************************/
void BLDC_ZeroCrossCompTask(void)
{
		if(bldcSysHandler.bldcSensorlessHandler.runMode == eBLDC_Run_Mode_COMP_INT && bldcSysHandler.sysErrorCode == eBLDC_Sys_Error_None){
			BLDC_Run_Mode_COMP_Int();
		}else return;
}



