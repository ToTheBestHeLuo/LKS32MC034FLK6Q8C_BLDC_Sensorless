#include "bldcConfig.h"
#include "sGSlave.h"

#define CW 1
#define CCW 55

/*λ�ڵ�62������*/
const sG_MotorFlashUnion slave_MotorData_Sector __attribute__((at(sectorMotorFlashAddr))) = {
	.motorPar = {
		.escID1 = 0x11,
		.escID2 = 0x22,
		.escID3 = 0x33,
		.escID4 = 0x44,
		
		.motorDuty_Max = 200,
		.motorDuty_Min = 50,
		.motorBeepVolumeDuty = 20,
		.motorStartupDuty = 17,
		
		.motorStartupInitialCycle = 150,
		.motorStartupFinalCycle = 40,
		.motorStartupFixedCycle = 250,
		
		.motorStartupRotateStep = 250,
		.motorStartup_ZC_Filter1 = 2,
		.motorStartup_ZC_Filter2 = 1,
		.motorStartup_BlockThreshold = 15,
		
		.motorRun_ZC_Filter1 = 5,
		.motorRun_ZC_Filter2 = 1,
		.mototRunThrottle_SpeedUpRate = 10,
		.mototRunThrottle_SlowDownRate = 10,
		.motorRun_BlockThreshold = 100,
		.motorRun_SpeedFilterPar1 = 1,
		.motorRun_SpeedFilterPar3 = 6,
		.motorRun_CWCCW = CW
	}
};

BLDC_SysHandler bldcSysHandler;

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

sG_MotorFlashUnion motorFlashData;

/*******************************************************************************
 �������ƣ�    static void BLDC_LoadFlashData_Static(void)
 ����������    ��Flash����������EEPROM���򣩼������ݵ�motorFlashData
 ����˵����    ��
 *******************************************************************************/
static void BLDC_LoadFlashData_Static(void)
{
		uint8_t* ptr = (uint8_t*)&motorFlashData.motorPar;
	
		/*��Flash���ص�����ƵĲ���*/
		const uint8_t* src = (const uint8_t*)&slave_MotorData_Sector.motorPar;

		for(int i = 0;i < sizeof(motorFlashData.motorPar);i++){
			ptr[i] = src[i];
			/*�����������Ƿ���Ч��0�Լ�255���ǲ������*/
			if(ptr[i] == 0 || ptr[i] == 255){
				break;
			}
		}
		
		bldcSysHandler.bldcSensorlessHandler.pwmCount = ((int16_t)motorFlashData.motorPar.motorStartupDuty * PWM_GAIN * 2 - PWM_PERIOD_COUNT);
		bldcSysHandler.bldcSensorlessHandler.pwmCountTarget = ((int16_t)motorFlashData.motorPar.motorStartupDuty * PWM_GAIN * 2 - PWM_PERIOD_COUNT);
		
		bldcSysHandler.bldcSensorlessHandler.speedUpCycle = motorFlashData.motorPar.motorStartupInitialCycle * PWM_GAIN2;
		bldcSysHandler.bldcSensorlessHandler.speedUpFinalCycle = motorFlashData.motorPar.motorStartupFinalCycle * PWM_GAIN2;
		bldcSysHandler.bldcSensorlessHandler.speedUpTimeCost = motorFlashData.motorPar.mototRunThrottle_SpeedUpRate;
		bldcSysHandler.bldcSensorlessHandler.slowDownTimeCost = motorFlashData.motorPar.mototRunThrottle_SlowDownRate;
		bldcSysHandler.bldcSensorlessHandler.rotorFixedCycle = motorFlashData.motorPar.motorStartupFixedCycle * PWM_GAIN2;
		bldcSysHandler.bldcSensorlessHandler.CWCCW = (motorFlashData.motorPar.motorRun_CWCCW == CW) ? true : false;
		
		bldcSysHandler.bldcSensorlessHandler.startupRotateStep = motorFlashData.motorPar.motorStartupRotateStep * PWM_GAIN2;
		
		bldcSysHandler.bldcSensorlessHandler.commutationFilter1 = motorFlashData.motorPar.motorRun_SpeedFilterPar1;
		bldcSysHandler.bldcSensorlessHandler.commutationFilter2 = (1 << motorFlashData.motorPar.motorRun_SpeedFilterPar3) - motorFlashData.motorPar.motorRun_SpeedFilterPar1;
		bldcSysHandler.bldcSensorlessHandler.commutationScaler = motorFlashData.motorPar.motorRun_SpeedFilterPar3;
		
		if(bldcSysHandler.bldcSensorlessHandler.CWCCW){
			BLDC_SwitchTable[0] = BLDC_SwitchTableCW[0];
			BLDC_SwitchTable[1] = BLDC_SwitchTableCW[1];
			BLDC_SwitchTable[2] = BLDC_SwitchTableCW[2];
			BLDC_SwitchTable[3] = BLDC_SwitchTableCW[3];
			BLDC_SwitchTable[4] = BLDC_SwitchTableCW[4];
			BLDC_SwitchTable[5] = BLDC_SwitchTableCW[5];
			
			bldcSysHandler.bldcSensorlessHandler.comparePolarity = true;
		}else{
			BLDC_SwitchTable[0] = BLDC_SwitchTableCCW[0];
			BLDC_SwitchTable[1] = BLDC_SwitchTableCCW[1];
			BLDC_SwitchTable[2] = BLDC_SwitchTableCCW[2];
			BLDC_SwitchTable[3] = BLDC_SwitchTableCCW[3];
			BLDC_SwitchTable[4] = BLDC_SwitchTableCCW[4];
			BLDC_SwitchTable[5] = BLDC_SwitchTableCCW[5];
			
			bldcSysHandler.bldcSensorlessHandler.comparePolarity = false;
		}
}
/*******************************************************************************
 �������ƣ�    bool BLDC_CheckFlashData_NoError(void)
 ����������    �����Ҫ��̵�Flash�Ƿ�Ϸ�
 ����˵����    ����1��û���󣬷�֮Ϊ�д���
 *******************************************************************************/
bool BLDC_CheckFlashData_NoError(void)
{
		uint8_t* ptr = (uint8_t*)&motorFlashData.motorPar;
	
		for(int i = 0;i < sizeof(motorFlashData.motorPar);i++){
			if(ptr[i] == 0 || ptr[i] == 255){

				return false;
			}
		}
		
		/*�����������Ƿ�����Ӧ��Χ��*/
		if(motorFlashData.motorPar.motorDuty_Max < motorFlashData.motorPar.motorDuty_Min) return false;
		if(motorFlashData.motorPar.motorDuty_Max > 200) return false;
		if(motorFlashData.motorPar.motorDuty_Min > 200) return false;
		if(motorFlashData.motorPar.motorBeepVolumeDuty > 200) return false;
		if(motorFlashData.motorPar.motorStartupDuty > 200) return false;
		if(motorFlashData.motorPar.motorStartup_ZC_Filter1 > 15) return false;
		if(motorFlashData.motorPar.motorStartup_ZC_Filter2 > 7) return false;
		if(motorFlashData.motorPar.motorRun_ZC_Filter1 > 15) return false;
		if(motorFlashData.motorPar.motorRun_ZC_Filter2 > 7) return false;
		if(motorFlashData.motorPar.motorRun_SpeedFilterPar1 > (1 << motorFlashData.motorPar.motorRun_SpeedFilterPar3)) return false;
		
		return true;
}


BLDC_MotorAudioHandler bldcAudioHandler;

static const uint8_t audioTone[] = {
	76,68,61,57,51,45,40
};

static const BLDC_MotorTone motorAudio_0[] = {
	eTone_1,eTone_1,eTone_1,eTone_1,eTone_1,eTone_1,eTone_1,eTone_1,eTone_1,
	eTone_1,eTone_1,eTone_1,eTone_1,eTone_1,eTone_1,eTone_1,eTone_1,eTone_1,
	eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,
	eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,
	eTone_3,eTone_3,eTone_3,eTone_3,eTone_3,eTone_3,eTone_3,eTone_3,eTone_3,
	eTone_3,eTone_3,eTone_3,eTone_3,eTone_3,eTone_3,eTone_3,eTone_3,eTone_3,
	eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,
	eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None
};

static const BLDC_MotorTone motorAudio_1[] = {
	eTone_2,eTone_2,eTone_2,eTone_2,eTone_2,eTone_2,eTone_2,eTone_2,eTone_2,
	eTone_2,eTone_2,eTone_2,eTone_2,eTone_2,eTone_2,eTone_2,eTone_2,eTone_2,
	eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,
	eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,
	eTone_2,eTone_2,eTone_2,eTone_2,eTone_2,eTone_2,eTone_2,eTone_2,eTone_2,
	eTone_2,eTone_2,eTone_2,eTone_2,eTone_2,eTone_2,eTone_2,eTone_2,eTone_2,
	eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,
	eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None
};

static const BLDC_MotorTone motorAudio_2[] = {
	eTone_4,eTone_4,eTone_4,eTone_4,eTone_4,eTone_4,eTone_4,eTone_4,eTone_4,
	eTone_4,eTone_4,eTone_4,eTone_4,eTone_4,eTone_4,eTone_4,eTone_4,eTone_4,
	eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,
	eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,
	eTone_4,eTone_4,eTone_4,eTone_4,eTone_4,eTone_4,eTone_4,eTone_4,eTone_4,
	eTone_4,eTone_4,eTone_4,eTone_4,eTone_4,eTone_4,eTone_4,eTone_4,eTone_4,
	eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,
	eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None,eTone_None
};

/*******************************************************************************
 �������ƣ�    bool BLDC_AudioInit(BLDC_MotorTone* audioToPlay,uint8_t toneNums)
 ����������    ��
 ����˵����    ���֧��256��tone
 *******************************************************************************/
static bool BLDC_AudioInit(BLDC_MotorTone* audioToPlay,uint8_t toneNums)
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
 �������ƣ�    void BLDC_Beep_Audio_0(void)
 ����������    ��
 ����˵����    ��
 *******************************************************************************/
void BLDC_Beep_Audio_0(void)
{

}

/*******************************************************************************
 �������ƣ�    void BLDC_Beep_Audio_1(void)
 ����������    ��
 ����˵����    ��
 *******************************************************************************/
void BLDC_Beep_Audio_1(void)
{
		BLDC_AudioInit((BLDC_MotorTone*)motorAudio_1,sizeof(motorAudio_1) / sizeof(BLDC_MotorTone));		
}

/*******************************************************************************
 �������ƣ�    void BLDC_Beep_Audio_2(void)
 ����������    ��
 ����˵����    ��
 *******************************************************************************/
void BLDC_Beep_Audio_2(void)
{
		BLDC_AudioInit((BLDC_MotorTone*)motorAudio_2,sizeof(motorAudio_2) / sizeof(BLDC_MotorTone));	
}

/*******************************************************************************
 �������ƣ�    void BLDC_Beep_Audio_x(uint8_t which)
 ����������    ��
 ����˵����    ��
 *******************************************************************************/
void BLDC_Beep_Audio_x(uint8_t which)
{
		if(which == 0) BLDC_AudioInit((BLDC_MotorTone*)motorAudio_0,sizeof(motorAudio_0) / sizeof(BLDC_MotorTone));
		else if(which == 1) BLDC_AudioInit((BLDC_MotorTone*)motorAudio_1,sizeof(motorAudio_1) / sizeof(BLDC_MotorTone));
		else if(which == 2) BLDC_AudioInit((BLDC_MotorTone*)motorAudio_2,sizeof(motorAudio_2) / sizeof(BLDC_MotorTone));
		else return;
}

/*******************************************************************************
 �������ƣ�    static bool BLDC_Run_Mode_COMP_Polling_Commutation(void)
 ����������    ��ѯģʽ�£��޸�BLDC��������ϵͳ�Ĺ����⺯����������true��ʾ��Ҫ�������࣬������falseʱ��ʾ���軻��
 ����˵����    ��
 *******************************************************************************/
static bool BLDC_Run_Mode_COMP_Polling_Commutation(void)
{
		bool commutation = false;
		bool nowCompResult = BLDC_COMP_GetData_Filter();
	
		if(bldcSysHandler.bldcSensorlessHandler.comparePolarity != nowCompResult){
			bldcSysHandler.highSpeedCounter++;
			if(bldcSysHandler.highSpeedCounter > 8){
				bldcSysHandler.highSpeedCounter = 0;
				bldcSysHandler.bldcSensorlessHandler.comparePolarity = nowCompResult;
				commutation = true;
			}
		}else{
			bldcSysHandler.highSpeedCounter = 0;
		}
		return commutation;
}	
/*******************************************************************************
 �������ƣ�    static void BLDC_Run_Mode_COMP_Polling(void)
 ����������    �޸�BLDC��������ϵͳ�����ڱȽ�����ѯģʽ
 ����˵����    ��
 *******************************************************************************/
static void BLDC_Run_Mode_COMP_Polling(void)
{
		bool commutation;
		/*�̶�Ϊ��ͨռ�ձȵ�1/2��������*/
		BLDC_SetADCTriggerPoint(bldcSysHandler.bldcSensorlessHandler.pwmCount);
		switch(bldcSysHandler.bldcSensorlessHandler.runStatus){
			case eBLDC_Run_Audio:
				if(bldcAudioHandler.audioStatus == eAudio_WaitPlay){
					BLDC_SwitchTable[0]((uint16_t)motorFlashData.motorPar.motorBeepVolumeDuty * PWM_GAIN * 2 - PWM_PERIOD_COUNT);
					bldcAudioHandler.audioStatus = eAudio_NoPlay;
				}else if(bldcAudioHandler.audioStatus == eAudio_NoPlay){
					BLDC_SwitchTable[0]((uint16_t)-PWM_PERIOD_COUNT);
					bldcSysHandler.highSpeedCounter++;
					if(bldcSysHandler.highSpeedCounter >= audioTone[bldcAudioHandler.audioToPlay[bldcAudioHandler.index]] * PWM_GAIN2){
						bldcSysHandler.highSpeedCounter = 0;
						bldcAudioHandler.count++;
						if(bldcAudioHandler.count >= 2){
							bldcAudioHandler.count = 0;
							bldcAudioHandler.index++;
							if(bldcAudioHandler.index >= bldcAudioHandler.inTotal){
								bldcAudioHandler.index = 0;
								bldcAudioHandler.audioStatus = eAudio_Finished;
							}else{
								bldcAudioHandler.audioStatus = eAudio_WaitPlay;
							}
						}
					}
				}else if(bldcAudioHandler.audioStatus == eAudio_Finished){
					if(bldcSysHandler.highSpeedCounter++ >= 20000 * PWM_GAIN2){
						bldcAudioHandler.audioStatus = eAudio_Init;
						bldcSysHandler.highSpeedCounter = 0;
					}
				}
				break;
			case eBLDC_Run_Alignment:
				BLDC_SwitchTable[0]((uint16_t)bldcSysHandler.bldcSensorlessHandler.pwmCount);
				if(bldcSysHandler.highSpeedCounter++ > bldcSysHandler.bldcSensorlessHandler.rotorFixedCycle * 3){
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
						BLDC_COMP_SetFilter_Startup();
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
				commutation = BLDC_Run_Mode_COMP_Polling_Commutation();
				if(commutation){
					bldcSysHandler.bldcSensorlessHandler.sector = (bldcSysHandler.bldcSensorlessHandler.sector + 1) % 6;
					BLDC_SwitchTable[bldcSysHandler.bldcSensorlessHandler.sector]((uint16_t)bldcSysHandler.bldcSensorlessHandler.pwmCount);
				}else{
					bldcSysHandler.counter1++;
					if(bldcSysHandler.counter1 > 48u){
						bldcSysHandler.counter1 = 0u;
						bldcSysHandler.bldcSensorlessHandler.pwmCount = bldcSysHandler.bldcSensorlessHandler.pwmCount + 1;
					}
				}
				if(commutation && ++bldcSysHandler.counter >= 4u){
					BLDC_HALL_ResetCounter();
					bldcSysHandler.counter = 0u;
					bldcSysHandler.counter1 = 0u;
					bldcSysHandler.highSpeedCounter = 0u;
					
					bldcSysHandler.bldcSensorlessHandler.runStatus = eBLDC_Run_ReadyForCloseLoop;
				}
				break;
			case eBLDC_Run_ReadyForCloseLoop:
				commutation = BLDC_Run_Mode_COMP_Polling_Commutation();
				if(commutation){
					bldcSysHandler.bldcSensorlessHandler.commutationTime = (BLDC_HALL_GetCounter() * bldcSysHandler.bldcSensorlessHandler.commutationFilter1 \
																																	+ bldcSysHandler.bldcSensorlessHandler.commutationFilter2 * bldcSysHandler.bldcSensorlessHandler.commutationTime) \
																																	>> bldcSysHandler.bldcSensorlessHandler.commutationScaler;
					bldcSysHandler.bldcSensorlessHandler.estSpeedHz = BLDC_Div(8000000,bldcSysHandler.bldcSensorlessHandler.commutationTime);
					BLDC_HALL_ResetCounter();
					bldcSysHandler.bldcSensorlessHandler.sector = (bldcSysHandler.bldcSensorlessHandler.sector + 1) % 6;
						
					BLDC_SwitchTable[bldcSysHandler.bldcSensorlessHandler.sector]((uint16_t)(bldcSysHandler.bldcSensorlessHandler.pwmCount));
					if(bldcSysHandler.counter++ >= bldcSysHandler.bldcSensorlessHandler.startupRotateStep){
						BLDC_PWM_Int_TurnOff();
						bldcSysHandler.counter = 0u;
						bldcSysHandler.counter1 = 0u;
						BLDC_COMP_SetFilter_Run();
						bldcSysHandler.bldcSensorlessHandler.comparePolarity ? BLDC_COMP_Int_SetPolarity_Low() : BLDC_COMP_Int_SetPolarity_High();
						CMP->IF = (BIT0 | BIT1);
						BLDC_HALL_ResetCounter();
						BLDC_HALL_SetThreshold_Low();
						bldcSysHandler.switchPhaseMask = MCPWM_UPDATE_MASK1;
						bldcSysHandler.bldcSensorlessHandler.pwmCountTarget = ((int16_t)motorFlashData.motorPar.motorDuty_Min * PWM_GAIN * 2 - PWM_PERIOD_COUNT);
						bldcSysHandler.bldcSensorlessHandler.runMode = eBLDC_Run_Mode_COMP_INT;
						BLDC_COMP_Int_TurnOn();
					}
				}else{
					bldcSysHandler.counter1++;
					if(bldcSysHandler.counter1 > 48u){
						bldcSysHandler.counter1 = 0u;
						bldcSysHandler.bldcSensorlessHandler.pwmCount = bldcSysHandler.bldcSensorlessHandler.pwmCount + 1;
					}
				}
				break;
			/*�ⲿ��Ϊ������ѯ�Ĵ��룬δʹ�ã���Ҳ��Ҫɾ��*/	
			case eBLDC_Run_CloseLoop:
				if(BLDC_Run_Mode_COMP_Polling_Commutation()){
					bldcSysHandler.bldcSensorlessHandler.sector = (bldcSysHandler.bldcSensorlessHandler.sector + 1) % 6;
					BLDC_SwitchTable[bldcSysHandler.bldcSensorlessHandler.sector]((uint16_t)bldcSysHandler.bldcSensorlessHandler.pwmCount);
				
					bldcSysHandler.bldcSensorlessHandler.commutationTime = (BLDC_HALL_GetCounter() * bldcSysHandler.bldcSensorlessHandler.commutationFilter1 \
																																	+ bldcSysHandler.bldcSensorlessHandler.commutationFilter2 * bldcSysHandler.bldcSensorlessHandler.commutationTime) \
																																	>> bldcSysHandler.bldcSensorlessHandler.commutationScaler;
					BLDC_HALL_ResetCounter();
					bldcSysHandler.bldcSensorlessHandler.pwmCountTarget = 0;
					bldcSysHandler.bldcSensorlessHandler.estSpeedHz = BLDC_Div(8000000,bldcSysHandler.bldcSensorlessHandler.commutationTime);
					if(bldcSysHandler.bldcSensorlessHandler.pwmCount < bldcSysHandler.bldcSensorlessHandler.pwmCountTarget && bldcSysHandler.counter++ > bldcSysHandler.bldcSensorlessHandler.speedUpTimeCost){
						bldcSysHandler.counter = 0u;
						bldcSysHandler.bldcSensorlessHandler.pwmCount++;
					}else if(bldcSysHandler.bldcSensorlessHandler.pwmCount > bldcSysHandler.bldcSensorlessHandler.pwmCountTarget && bldcSysHandler.counter++ > bldcSysHandler.bldcSensorlessHandler.slowDownTimeCost){
						bldcSysHandler.counter = 0u;
						bldcSysHandler.bldcSensorlessHandler.pwmCount--;
					}
				}
				break;
			default:
				while(1);
		}
}
/*******************************************************************************
 �������ƣ�    static void BLDC_Run_Mode_COMP_Int(void)
 ����������    �޸�BLDC��������ϵͳ�����ڱȽ����ж�ģʽ������ȷ�������
 ����˵����    ��
 *******************************************************************************/
static void BLDC_Run_Mode_COMP_Int(void)
{
		BLDC_COMP_ClearIntFlag();

		BLDC_COMP_GetPolarity() ? BLDC_COMP_Int_SetPolarity_Low() : BLDC_COMP_Int_SetPolarity_High();
		
		bldcSysHandler.bldcSensorlessHandler.sector = (bldcSysHandler.bldcSensorlessHandler.sector + 1) % 6;
		BLDC_SetADCTriggerPoint(bldcSysHandler.bldcSensorlessHandler.pwmCount);
	
		uint32_t getHall = BLDC_HALL_GetCounter();
		BLDC_HALL_ResetCounter();
		BLDC_SwitchTable[bldcSysHandler.bldcSensorlessHandler.sector]((uint16_t)bldcSysHandler.bldcSensorlessHandler.pwmCount);
		bldcSysHandler.bldcSensorlessHandler.commutationTime = (getHall * bldcSysHandler.bldcSensorlessHandler.commutationFilter1 \
																														+ bldcSysHandler.bldcSensorlessHandler.commutationFilter2 * bldcSysHandler.bldcSensorlessHandler.commutationTime) \
																														>> bldcSysHandler.bldcSensorlessHandler.commutationScaler;
		bldcSysHandler.bldcSensorlessHandler.estSpeedHz = BLDC_Div(8000000,bldcSysHandler.bldcSensorlessHandler.commutationTime);
		if(bldcSysHandler.bldcSensorlessHandler.pwmCount < bldcSysHandler.bldcSensorlessHandler.pwmCountTarget && bldcSysHandler.counter++ > bldcSysHandler.bldcSensorlessHandler.speedUpTimeCost){
			bldcSysHandler.counter = 0u;
			bldcSysHandler.bldcSensorlessHandler.pwmCount++;
		}else if(bldcSysHandler.bldcSensorlessHandler.pwmCount > bldcSysHandler.bldcSensorlessHandler.pwmCountTarget && bldcSysHandler.counter++ > bldcSysHandler.bldcSensorlessHandler.slowDownTimeCost){
			bldcSysHandler.counter = 0u;
			bldcSysHandler.bldcSensorlessHandler.pwmCount--;
		}
}
/*******************************************************************************
 �������ƣ�    static void BLDC_SysReset(void)
 ����������    �޸�BLDC��������ϵͳ��λ��������Ҫ����һЩ�����ĳ�ʼ��
 ����˵����    ���ֲ����ĸ�λֵ��û��Ч���ģ���Ϊ���������´��ڴ����������Ӧ�ı������Ӷ����ǵ���λֵ
 *******************************************************************************/
static void BLDC_SysReset(void)
{
		/*��λbldcSysHandler*/
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
	
		bldcSysHandler.adcSensorHandler.adcBusVoltageValue = 0;
		bldcSysHandler.adcSensorHandler.adcDriverTemperatureValue = 0;
		bldcSysHandler.adcSensorHandler.adcBusCurrent = 0;
		bldcSysHandler.adcSensorHandler.adcBusCurrentOffset = 0;
		
		/*��λbldcAudioHandler*/
		bldcAudioHandler.audioToPlay = (BLDC_MotorTone*)0;
		bldcAudioHandler.index = 0;
		bldcAudioHandler.inTotal = 0;
		bldcAudioHandler.count = 0;
		bldcAudioHandler.audioStatus = eAudio_Init;
}
/*******************************************************************************
 �������ƣ�    void BLDC_LowSpeedTask(void)
 ����������    �޸�BLDC�����������ʱ��������Ҫ������һЩ��ȫ����͵���ͨ������
 ����˵����    ��ADC����жϽ��е��ã��ж����ȼ�С�ڸ���ʱ������
 *******************************************************************************/
void BLDC_LowSpeedTask(void)
{
		static int32_t busCurrentOffset = 0;
		static uint16_t busErrorCnt = 0u,tempErrorCnt = 0u;

		BLDC_SysStatus status = bldcSysHandler.sysStatus;
		bldcSysHandler.adcSensorHandler.adcBusVoltageValue = BLDC_GetBusVoltage();
		bldcSysHandler.adcSensorHandler.adcDriverTemperatureValue = BLDC_GetDriverTemperature();
	
		int16_t busCurrent = BLDC_GetBusCurrent() - bldcSysHandler.adcSensorHandler.adcBusCurrentOffset;
		switch(status){
			case eBLDC_Sys_Reset:
				bldcSysHandler.switchPhaseMask = MCPWM_UPDATE_MASK0;
				BLDC_PWM_Int_TurnOn();
				BLDC_COMP_Int_TurnOff();
				BLDC_HALL_OverFlowInt_TurnOff();
				BLDC_PWM_LowSides_TurnOn();
				busCurrentOffset = 0;
				BLDC_SysReset();
				bldcSysHandler.sysStatus = eBLDC_Sys_WaitBusAndTemp;
				break;
			case eBLDC_Sys_WaitBusAndTemp:
				if(bldcSysHandler.adcSensorHandler.adcBusVoltageValue > BLDC_Bus_UnderVoltage_Protect &&  \
						bldcSysHandler.adcSensorHandler.adcBusVoltageValue < BLDC_Bus_OverVoltage_Protect && \
						!BLDC_TEMP_Temperature_TooHigh(bldcSysHandler.adcSensorHandler.adcDriverTemperatureValue) && \
						!BLDC_TEMP_Temperature_TooLow(bldcSysHandler.adcSensorHandler.adcDriverTemperatureValue)){
					if(bldcSysHandler.lowSpeedCounter++ > 1000u){
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
				BLDC_AudioInit((BLDC_MotorTone*)motorAudio_0,sizeof(motorAudio_0) / sizeof(BLDC_MotorTone));
				bldcSysHandler.bldcSensorlessHandler.runMode = eBLDC_Run_Mode_COMP_Polling;
				bldcSysHandler.sysStatus = eBLDC_Sys_StartupAudio;
				break;
			case eBLDC_Sys_StartupAudio:
				if(bldcAudioHandler.audioStatus == eAudio_Finished){
					System_Enable_sG_Int();
					bldcSysHandler.sysStatus = eBLDC_Sys_WaitStart;
				}
				break;
			case eBLDC_Sys_WaitStart:
				if(sG.mode == esG_Slave_SendEHzDataOut){
					/*���������ͬʱsG��׼����ʧЧ*/
					bldcSysHandler.bldcSensorlessHandler.runStatus = eBLDC_Run_Alignment;
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
					/*����Ӧ�����������ʱҲû������˵͵Ĺ����¶�*/
					while(1);
				}else tempErrorCnt = 0u;
				
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
 ����˵����    ��COMP�����жϽ��е��ã��ж����ȼ���MCPWM�ж�ͬ�ȼ�
 *******************************************************************************/
void BLDC_ZeroCrossCompTask(void)
{
		if(bldcSysHandler.bldcSensorlessHandler.runMode == eBLDC_Run_Mode_COMP_INT && bldcSysHandler.sysErrorCode == eBLDC_Sys_Error_None){
			BLDC_Run_Mode_COMP_Int();
		}else return;
}




