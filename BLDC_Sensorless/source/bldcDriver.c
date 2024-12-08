#include "bldcConfig.h"

/*��ת�����*/
static void (*BLDC_SwitchTableCW[])(uint16_t pwmCount) = {
		BLDC_PWM_UH_VL,
		BLDC_PWM_UH_WL,
		BLDC_PWM_VH_WL,
		BLDC_PWM_VH_UL,
		BLDC_PWM_WH_UL,
		BLDC_PWM_WH_VL
};
/*��ת�����*/
static void (*BLDC_SwitchTableCCW[])(uint16_t pwmCount) = {
		BLDC_PWM_UH_VL,
		BLDC_PWM_WH_VL,
		BLDC_PWM_WH_UL,
		BLDC_PWM_VH_UL,
		BLDC_PWM_VH_WL,
		BLDC_PWM_UH_WL
};
/*ʵ��ʹ�õĻ����*/
static void (*BLDC_SwitchTable[6])(uint16_t pwmCount);

BLDC_SysHandler bldcSysHandler;

/*******************************************************************************
 �������ƣ�    static bool BLDC_Run_Mode_COMP_Polling_Commutation(void)
 ����������    ��ѯģʽ�£��޸�BLDC��������ϵͳ�Ĺ����⺯����������true��ʾ��Ҫ�������࣬������falseʱ��ʾ���軻��
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
						
						/*������򿪵���Ķ�ת��������*/
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
 �������ƣ�    static void BLDC_Run_Mode_COMP_Int(void)
 ����������    �޸�BLDC��������ϵͳ�����ڱȽ����ж�ģʽ������ȷ�������
 ���������    ��         
 ���������    ��
 �� �� ֵ��    ��
 ����˵����    ��
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
					/*����Ӧ�����������ʱҲû������˵͵Ĺ����¶�*/
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

