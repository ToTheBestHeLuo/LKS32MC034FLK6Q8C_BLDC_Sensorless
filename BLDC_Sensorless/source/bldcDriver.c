#include "bldcConfig.h"

void (*BLDC_SwitchTableCW[])(uint16_t pwmCount) = {
		BLDC_PWM_UH_VL,
		BLDC_PWM_UH_WL,
		BLDC_PWM_VH_WL,
		BLDC_PWM_VH_UL,
		BLDC_PWM_WH_UL,
		BLDC_PWM_WH_VL
};

void (*BLDC_SwitchTableCCW[])(uint16_t pwmCount) = {
		BLDC_PWM_UH_VL,
		BLDC_PWM_WH_VL,
		BLDC_PWM_WH_UL,
		BLDC_PWM_VH_UL,
		BLDC_PWM_VH_WL,
		BLDC_PWM_UH_WL
};

BLDC_SysHandler bldcSysHandler;

/*******************************************************************************
 �������ƣ�    static bool BLDC_Run_Mode_COMP_Polling_Commutation(void)
 ����������    ��ѯģʽ�£��޸�BLDC��������ϵͳ�Ĺ����⺯����������true��ʾ��Ҫ�������࣬������falseʱ��ʾ���軻�࣬���⣬�Զ����ñȽ������жϴ�������
 ���������    ��         
 ���������    ��
 �� �� ֵ��    ��
 ����˵����    ��
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
 �������ƣ�    static void BLDC_Run_Mode_COMP_Polling(void)
 ����������    �޸�BLDC��������ϵͳ�����ڱȽ�����ѯģʽ
 ���������    ��         
 ���������    ��
 �� �� ֵ��    ��
 ����˵����    ��
 *******************************************************************************/
static void BLDC_Run_Mode_COMP_Polling(void)
{
		bool cwccw = bldcSysHandler.bldcSensorlessHandler.CWCCW;
		switch(bldcSysHandler.bldcSensorlessHandler.runStatus){
			case eBLDC_Run_Alignment:
				BLDC_SwitchTableCW[0]((uint16_t)BLDC_Startup_PWM_Count);
				if(bldcSysHandler.highSpeedCounter++ > 500){
					bldcSysHandler.highSpeedCounter = 0u;
					bldcSysHandler.bldcSensorlessHandler.runStatus = eBLDC_Run_SpeedUp;
				}
				break;
			case eBLDC_Run_SpeedUp:
				if(cwccw) BLDC_SwitchTableCW[bldcSysHandler.bldcSensorlessHandler.sector]((uint16_t)BLDC_Startup_PWM_Count);
				else BLDC_SwitchTableCCW[bldcSysHandler.bldcSensorlessHandler.sector]((uint16_t)BLDC_Startup_PWM_Count);
				if(bldcSysHandler.highSpeedCounter++ > bldcSysHandler.bldcSensorlessHandler.speedUpCycle){
					bldcSysHandler.highSpeedCounter = 0u;
					bldcSysHandler.bldcSensorlessHandler.sector = (bldcSysHandler.bldcSensorlessHandler.sector + 1) % 6;
					if(bldcSysHandler.bldcSensorlessHandler.speedUpCycle-- < BLDC_Startup_Final_Cycle){
						BLDC_COMP_SetFilter_LowDelay();
						bldcSysHandler.counter = 0u;
						
						/*������򿪵���Ķ�ת��������*/
						BLDC_HALL_SetThreshold();
						BLDC_HALL_ResetCounter();
						BLDC_HALL_OverFlowInt_TurnOn();
						
						bldcSysHandler.bldcSensorlessHandler.runStatus = eBLDC_Run_OpenLoop;
					}
				}
				break;
			case eBLDC_Run_OpenLoop:
				if(cwccw) BLDC_SwitchTableCW[bldcSysHandler.bldcSensorlessHandler.sector]((uint16_t)BLDC_Startup_PWM_Count);
				else BLDC_SwitchTableCCW[bldcSysHandler.bldcSensorlessHandler.sector]((uint16_t)BLDC_Startup_PWM_Count);
				if(bldcSysHandler.highSpeedCounter++ > bldcSysHandler.bldcSensorlessHandler.speedUpCycle){
					bldcSysHandler.highSpeedCounter = 0u;
					bldcSysHandler.bldcSensorlessHandler.sector = (bldcSysHandler.bldcSensorlessHandler.sector + 1) % 6;
				}
				if(BLDC_Run_Mode_COMP_Polling_Commutation() && ++bldcSysHandler.counter == 4u){
					BLDC_HALL_ResetCounter();
					bldcSysHandler.counter = 0u;
					bldcSysHandler.highSpeedCounter = 0u;
					bldcSysHandler.bldcSensorlessHandler.sector = (bldcSysHandler.bldcSensorlessHandler.sector + 1) % 6;
					if(cwccw) BLDC_SwitchTableCW[bldcSysHandler.bldcSensorlessHandler.sector]((uint16_t)BLDC_Startup_PWM_Count);
					else BLDC_SwitchTableCCW[bldcSysHandler.bldcSensorlessHandler.sector]((uint16_t)BLDC_Startup_PWM_Count);
					bldcSysHandler.bldcSensorlessHandler.runStatus = eBLDC_Run_ReadyForCloseLoop;
				}
				break;
			case eBLDC_Run_ReadyForCloseLoop:
				if(BLDC_Run_Mode_COMP_Polling_Commutation()){
					BLDC_HALL_ResetCounter();
					bldcSysHandler.counter++;
					bldcSysHandler.bldcSensorlessHandler.sector = (bldcSysHandler.bldcSensorlessHandler.sector + 1) % 6;
					if(cwccw) BLDC_SwitchTableCW[bldcSysHandler.bldcSensorlessHandler.sector]((uint16_t)BLDC_Startup_PWM_Count);
					else BLDC_SwitchTableCCW[bldcSysHandler.bldcSensorlessHandler.sector]((uint16_t)BLDC_Startup_PWM_Count);
				}
				if(bldcSysHandler.counter == 255){
					bldcSysHandler.counter = 0u;
					BLDC_COMP_SetFilter_HighDelay();
					bldcSysHandler.bldcSensorlessHandler.runMode = eBLDC_Run_Mode_COMP_INT;
					BLDC_PWM_Int_TurnOff();
					CMP->IF = (BIT0 | BIT1);
					BLDC_COMP_Int_TurnOn();
				}
				break;
			default:
				while(1);
		}
}
/*******************************************************************************
 �������ƣ�    static void BLDC_Run_Mode_COMP_Int(void)
 ����������    �޸�BLDC��������ϵͳ�����ڱȽ����ж�ģʽ������������ٶȱջ�����
 ���������    ��         
 ���������    ��
 �� �� ֵ��    ��
 ����˵����    ע��һ���ܹؼ��ĵ�
 *******************************************************************************/
static void BLDC_Run_Mode_COMP_Int(void)
{
		static bool commutationError = false;
	
		bool cwccw = bldcSysHandler.bldcSensorlessHandler.CWCCW;
		bldcSysHandler.bldcSensorlessHandler.sector = (bldcSysHandler.bldcSensorlessHandler.sector + 1) % 6;
		if(cwccw) BLDC_SwitchTableCW[bldcSysHandler.bldcSensorlessHandler.sector]((uint16_t)bldcSysHandler.bldcSensorlessHandler.pwmCount);
		else BLDC_SwitchTableCCW[bldcSysHandler.bldcSensorlessHandler.sector]((uint16_t)bldcSysHandler.bldcSensorlessHandler.pwmCount);
		BLDC_COMP_GetPolarity() ? BLDC_COMP_Int_SetPolarity_Low() : BLDC_COMP_Int_SetPolarity_High();
	
		bool comp = BLDC_COMP_GetData_Filter();
	
		if(commutationError != comp && bldcSysHandler.highSpeedCounter++ > 10){
			bldcSysHandler.sysErrorCode = eBLDC_Sys_Error_Commutation;
		}else{
			commutationError = comp;
		}
	
	
		bldcSysHandler.bldcSensorlessHandler.commutationTime = BLDC_HALL_GetCounter();
		BLDC_HALL_ResetCounter();
	
		if(bldcSysHandler.bldcSensorlessHandler.pwmCount < bldcSysHandler.bldcSensorlessHandler.pwmCountTarget && bldcSysHandler.counter++ == 10u){
			bldcSysHandler.counter = 0u;
			bldcSysHandler.bldcSensorlessHandler.pwmCount++;
		}else if(bldcSysHandler.bldcSensorlessHandler.pwmCount > bldcSysHandler.bldcSensorlessHandler.pwmCountTarget && bldcSysHandler.counter++ == 10u){
			bldcSysHandler.counter = 0u;
			bldcSysHandler.bldcSensorlessHandler.pwmCount--;
		}
		BLDC_COMP_Int_TurnOff();
		CMP->IF = 0x3;
		BLDC_COMP_Int_TurnOn();
}
/*******************************************************************************
 �������ƣ�    static void BLDC_SysReset(void)
 ����������    �޸�BLDC��������ϵͳ��λ��������Ҫ����һЩ�����ĳ�ʼ��
 ���������    ��         
 ���������    ��
 �� �� ֵ��    ��
 ����˵����    ��
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
		bldcSysHandler.bldcSensorlessHandler.CWCCW = false;
		bldcSysHandler.bldcSensorlessHandler.comparePolarity = true;
		bldcSysHandler.bldcSensorlessHandler.commutationTime = 0u;
	
		bldcSysHandler.adcSensorHandler.adcBusVoltageValue = 0;
		bldcSysHandler.adcSensorHandler.adcDriverTemperatureValue = 0;
		bldcSysHandler.adcSensorHandler.adcBusCurrent = 0;
		bldcSysHandler.adcSensorHandler.adcBusCurrentOffset = 0;

	
		if(bldcSysHandler.bldcSensorlessHandler.CWCCW) BLDC_COMP_Int_SetPolarity_High();
		else BLDC_COMP_Int_SetPolarity_Low();
}
/*******************************************************************************
 �������ƣ�    void BLDC_LowSpeedTask(void)
 ����������    �޸�BLDC�����������ʱ��������Ҫ������һЩ��ȫ����͵���ͨ������
 ���������    ��         
 ���������    ��
 �� �� ֵ��    ��
 ����˵����    ��ADC����жϽ��е��ã��ж����ȼ�С�ڸ���ʱ������
 *******************************************************************************/
void BLDC_LowSpeedTask(void)
{
		static int32_t busCurrentOffset = 0;
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
				bldcSysHandler.sysStatus = eBLDC_Sys_WaitBus;
				break;
			case eBLDC_Sys_WaitBus:
				if(bldcSysHandler.adcSensorHandler.adcBusVoltageValue > BLDC_Bus_UnderVoltage_Protect && bldcSysHandler.adcSensorHandler.adcBusVoltageValue < BLDC_Bus_OverVoltage_Protect){
					if(bldcSysHandler.lowSpeedCounter++ > 500u){
						BLDC_PWM_TurnOn();
						BLDC_PWM_LowSides_TurnOn();
						bldcSysHandler.lowSpeedCounter = 0u;
						bldcSysHandler.sysStatus = eBLDC_Sys_WaitCap;
					}
				}else bldcSysHandler.lowSpeedCounter = 0u;
				break;
			case eBLDC_Sys_WaitCap:
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
					if(bldcSysHandler.lowSpeedCounter++ > 100u){
						BLDC_PWM_TurnOff();
						bldcSysHandler.lowSpeedCounter = 0u;
						bldcSysHandler.sysStatus = eBLDC_Sys_Reset;
					}
				}else bldcSysHandler.lowSpeedCounter = 0u;
				
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
 �������ƣ�    void BLDC_HighSpeedTask(void)
 ����������    �޸�BLDC�����������ʱ��������Ҫ����һϵ�е�����Լ����������
 ���������    ��         
 ���������    ��
 �� �� ֵ��    ��
 ����˵����    ��MCPWM�жϽ��е��ã��ж����ȼ����ڵ���ʱ������
 *******************************************************************************/
void BLDC_HighSpeedTask(void)
{	
		if(bldcSysHandler.bldcSensorlessHandler.runMode == eBLDC_Run_Mode_COMP_Polling && bldcSysHandler.sysErrorCode == eBLDC_Sys_Error_None){
			BLDC_Run_Mode_COMP_Polling();
		}else return;
}
/*******************************************************************************
 �������ƣ�    void BLDC_ZeroCrossCompTask(void)
 ����������    �޸�BLDC��������Ƚ��������ź�������Ҫ����ջ��µĵ��������������
 ���������    ��         
 ���������    ��
 �� �� ֵ��    ��
 ����˵����    ��COMP�����жϽ��е��ã��ж����ȼ���MCPWM�ж�ͬ�ȼ�
 *******************************************************************************/
void BLDC_ZeroCrossCompTask(void)
{
		if(bldcSysHandler.bldcSensorlessHandler.runMode == eBLDC_Run_Mode_COMP_INT && bldcSysHandler.sysErrorCode == eBLDC_Sys_Error_None){
			BLDC_Run_Mode_COMP_Int();
		}else return;
}

