#include "sGSlave.h"
#include "bldcConfig.h"

sGHandler sG = {
	.transmitBuffer = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,UINT16_MAX,0},
	.isSendOrReceive = false,
	.isSendOrReceiveFinished = false,
	.mode = esG_Slave_RepeatCmd
};

#define FAKE_CODE ((uint16_t)esG_CMD_RST)

static const uint8_t slaveUniqueID[] = {'S','p','i','c','e','A','n','d','W','o','l','f'};

static uint8_t checkCnt = 0;
static bool escReady = false;
static int16_t minThrottle = -1200;
static int16_t maxThrottle = +1200;

bool sG_ProtocolProcess(uint16_t* dataOut)
{
		sGMode mode = sG.mode;
	
		bool pass = sG_ReceiveWithDMA(&sG.receiveData);
	
		uint16_t dataIn = sG.receiveData;
	
		if(mode == esG_Slave_SendEHzDataOut){
			if(pass){
				if(!escReady){
					if(checkCnt++ > 50){
						checkCnt = 0;
						minThrottle = motorFlashData.motorPar.motorDuty_Min * 12 - 1200;
						maxThrottle = motorFlashData.motorPar.motorDuty_Max * 12 - 1200;
						escReady = true;
					}
				}else{
					if(dataIn == 0 || dataIn > 2046){
						if(checkCnt++ > 100){
							checkCnt = 0;
							escReady = false;
							bldcSysHandler.bldcSensorlessHandler.pwmCountTarget = -1200;
							sG.mode = esG_Slave_RepeatCmd;
							BLDC_PWM_TurnOff();
							bldcSysHandler.sysStatus = eBLDC_Sys_Reset;
							return true;
						}
					}else if(bldcSysHandler.bldcSensorlessHandler.runMode == eBLDC_Run_Mode_COMP_INT){
						/*油门数据将被正确执行*/
						int16_t throttle = (int16_t)((int32_t)dataIn * 38437 / 32768 - 1200);
						if(throttle < minThrottle){
							throttle = minThrottle;
						}else if(throttle > maxThrottle){
							throttle = maxThrottle;
						}
						bldcSysHandler.bldcSensorlessHandler.pwmCountTarget = throttle;
					}
				}
			}
		  *dataOut = bldcSysHandler.bldcSensorlessHandler.estSpeedHz / 4;
			return true;
		}
		
		if(!pass){
			*dataOut = FAKE_CODE;
			sG.mode = esG_Slave_RepeatCmd;
			checkCnt = 0;
			return false;
		}
		
		if(dataIn == 0 || dataIn >= 0xFF){
			checkCnt = 0;
			*dataOut = FAKE_CODE;
			sG.mode = esG_Slave_RepeatCmd;
			return false;
		}
		
		if(mode == esG_Slave_RepeatCmd){
			
			sG.cmdType = (sG_CMDType)dataIn;
			*dataOut = dataIn;
			
			if(dataIn == (sG_CMDType)esG_CMD_MotorUnlock){
				if(checkCnt++ >= 10){
					checkCnt = 0;
					sG.mode = esG_Slave_SendEHzDataOut;
					return true;
				}
			}else{
				checkCnt = 0;
				sG.mode = esG_Slave_SendData;
				return false;
			}

		}else if(mode == esG_Slave_SendData){
			sG_CMDType cmdType = sG.cmdType;
			switch(cmdType){
				case esG_CMD_GetEscFixed_ID1:
				case esG_CMD_GetEscFixed_ID2:
				case esG_CMD_GetEscFixed_ID3:
				case esG_CMD_GetEscFixed_ID4:
				case esG_CMD_GetEscFixed_ID5:
				case esG_CMD_GetEscFixed_ID6:
				case esG_CMD_GetEscFixed_ID7:
				case esG_CMD_GetEscFixed_ID8:
				case esG_CMD_GetEscFixed_ID9:
				case esG_CMD_GetEscFixed_ID10:
				case esG_CMD_GetEscFixed_ID11:
				case esG_CMD_GetEscFixed_ID12:
					if(cmdType == (sG_CMDType)dataIn){
						*dataOut = slaveUniqueID[(uint16_t)cmdType - esG_CMD_GetEscFixed_ID1];
					}else{
						*dataOut = FAKE_CODE;
						sG.mode = esG_Slave_RepeatCmd;
					}
					sG.mode = esG_Slave_RepeatCmd;
					return true;
				case esG_CMD_GetEscID1:
				case esG_CMD_GetEscID2:
				case esG_CMD_GetEscID3:
				case esG_CMD_GetEscID4:
				case esG_CMD_GetMotorDuty_Max:
				case esG_CMD_GetMotorDuty_Min:
				case esG_CMD_GetMotorBeepVolumeDuty:
				case esG_CMD_GetMotorStartupDuty:
				case esG_CMD_GetMotorStartupInitialCycle:
				case esG_CMD_GetMotorStartupFinalCycle:
				case esG_CMD_GetMotorStartupFixedCycle:
				case esG_CMD_GetMotorStartupRotateStep:
				case esG_CMD_GetMotorStartup_ZC_Filter1:
				case esG_CMD_GetMotorStartup_ZC_Filter2:
				case esG_CMD_GetMotorStartup_BlockThreshold:
				case esG_CMD_GetMotorRun_ZC_Filter1:
				case esG_CMD_GetMotorRun_ZC_Filter2:
				case esG_CMD_GetMototRunThrottle_SpeedUpRate:
				case esG_CMD_GetMototRunThrottle_SlowDownRate:
				case esG_CMD_GetMotorRun_BlockThreshold:
				case esG_CMD_GetMotorRun_SpeedFilterPar1:
				case esG_CMD_GetMotorRun_SpeedFilterPar3:
				case esG_CMD_GetMotorRun_CWCCW:
					if(cmdType == (sG_CMDType)dataIn){
						*dataOut = ((const uint8_t*)&motorFlashData.motorPar)[(uint16_t)cmdType - (uint16_t)esG_CMD_GetEscID1];
					}else{
						*dataOut = FAKE_CODE;
						sG.mode = esG_Slave_RepeatCmd;
					}
					sG.mode = esG_Slave_RepeatCmd;
					return true;
				/*============================================================*/
				case esG_CMD_SetEscID1:
				case esG_CMD_SetEscID2:
				case esG_CMD_SetEscID3:
				case esG_CMD_SetEscID4:
				case esG_CMD_SetMotorDuty_Max:
				case esG_CMD_SetMotorDuty_Min:
				case esG_CMD_SetMotorBeepVolumeDuty:
				case esG_CMD_SetMotorStartupDuty:
				case esG_CMD_SetMotorStartupInitialCycle:
				case esG_CMD_SetMotorStartupFinalCycle:
				case esG_CMD_SetMotorStartupFixedCycle:
				case esG_CMD_SetMotorStartupRotateStep:
				case esG_CMD_SetMotorStartup_ZC_Filter1:
				case esG_CMD_SetMotorStartup_ZC_Filter2:
				case esG_CMD_SetMotorStartup_BlockThreshold:
				case esG_CMD_SetMotorRun_ZC_Filter1:
				case esG_CMD_SetMotorRun_ZC_Filter2:
				case esG_CMD_SetMototRunThrottle_SpeedUpRate:
				case esG_CMD_SetMototRunThrottle_SlowDownRate:
				case esG_CMD_SetMotorRun_BlockThreshold:
				case esG_CMD_SetMotorRun_SpeedFilterPar1:
				case esG_CMD_SetMotorRun_SpeedFilterPar3:
				case esG_CMD_SetMotorRun_CWCCW:
					((uint8_t*)&motorFlashData.motorPar)[(int16_t)cmdType - (int16_t)esG_CMD_SetEscID1] = dataIn;
					sG.mode = esG_Slave_RepeatCmd;
					return true;
				/*===========================================================*/
				case esG_CMD_Beep_Audio_0:
				case esG_CMD_Beep_Audio_1:
				case esG_CMD_Beep_Audio_2:
					*dataOut = (uint16_t)cmdType;
					BLDC_Beep_Audio_x((int16_t)cmdType - (int16_t)esG_CMD_Beep_Audio_0);
					sG.mode = esG_Slave_RepeatCmd;
					return true;
				case esG_CMD_SaveMotor:
					/*进入此步骤后屏蔽所有中断*/
					System_DisableAllInt();
					/*关闭电机驱动*/
					BLDC_PWM_TurnOff();
					if(BLDC_CheckFlashData_NoError()){
						/*擦除扇区*/
						erase_flag = 0x9A0D361F;
						EraseSector(sectorMotorFlashAddr);
						/*延时等待擦除完成*/
						SoftDelay(0xffff);
						/*编程扇区*/
						progm_flag = 0x9AFDA40C;
						ProgramPage(sectorMotorFlashAddr, sectorSize,(uint8_t*)&motorFlashData.motorPar);
						/*延时等待编程完成*/
						SoftDelay(0xffff);
					}
					/*重设SG状态*/
					System_Disable_sG_Int();
					*dataOut = FAKE_CODE;
					sG.mode = esG_Slave_RepeatCmd;
					/*中断恢复后自动进入复位状态*/
					bldcSysHandler.sysStatus = eBLDC_Sys_Reset;
					/*开启全部中断*/
					System_EnableAllInt();
					return true;
				default:
					*dataOut = FAKE_CODE;
					sG.mode = esG_Slave_RepeatCmd;
					return true;
			}
		}
		
		return false;
}

static uint16_t sG_CalculateWithCRC(uint16_t value,bool isSendOrReceive)
{
		uint16_t pack;
		/*当Slave处于发送状态时，发送的Check位必须为1*/
		if(isSendOrReceive) pack = (value << 1) | (1);
		/*当Slave处于接收状态时，Check位必须为0*/
		else pack = (value << 1);
    uint16_t sum = 0,tmp = pack;
    for(int i = 0;i < 3;i++){
        sum ^= tmp;tmp >>= 4;
    }
    pack = (pack << 4) | (sum & 0xf);
    return pack;
}

void sG_TransmitWithDMA(uint16_t value)
{
    value = (value > 2047) ? 2047 : value;
    value = sG_CalculateWithCRC(value,true);
    for(int i = 0;i < 16;i++){
        sG.transmitBuffer[i] = (value & 0x8000) ? sG_Logical1_DMA_Value : sG_Logical0_DMA_Value;
        value <<= 1;
    }
}

bool sG_ReceiveWithDMA(uint16_t* value)
{
    uint16_t val = 0x0000;
    uint16_t realData = 0x0000;

		for(int i = 0;i < 16;i++){
				realData <<= 1;
				realData |= ((sG.receiveBuffer[i] & sG_ReadPort_Mask) >> sG_ReadPort_Shift);
		}
		
		val = realData >> 5;

		if(sG_CalculateWithCRC(val,false) != realData) return false;
		
		uint8_t checkBit = realData & 0x10;
		
		/*作为Slave接收时，由Master发送的Check必须为0*/
		
		if(checkBit) return false;
		
		*value = val; 
		
    return true;
}




