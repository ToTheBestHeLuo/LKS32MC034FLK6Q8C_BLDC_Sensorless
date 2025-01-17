#ifndef _SG_SLAVE_H_
#define _SG_SLAVE_H_

#include "lks32mc03x_lib.h"

#include <stdint.h>
#include <stdbool.h>

#define STI static inline
#define sG_Logical1_DMA_Value (40u)
#define sG_Logical0_DMA_Value (120u)

#define sG_ReadPort_Shift 5
#define sG_ReadPort_Mask (1u << sG_ReadPort_Shift)

STI void System_DisableAllInt(void)
{
	__disable_irq();
}

STI void System_EnableAllInt(void)
{
	__enable_irq();
}

typedef enum{
	esG_CMD_RST = 0,
	/*只读的Get：12个，下标1开始*/
	esG_CMD_GetEscFixed_ID1,
	esG_CMD_GetEscFixed_ID2,
	esG_CMD_GetEscFixed_ID3,
	esG_CMD_GetEscFixed_ID4,
	esG_CMD_GetEscFixed_ID5,
	esG_CMD_GetEscFixed_ID6,
	esG_CMD_GetEscFixed_ID7,
	esG_CMD_GetEscFixed_ID8,
	esG_CMD_GetEscFixed_ID9,
	esG_CMD_GetEscFixed_ID10,
	esG_CMD_GetEscFixed_ID11,
	esG_CMD_GetEscFixed_ID12,
	/*Get：23个，下标1开始*/
	esG_CMD_GetEscID1,
	esG_CMD_GetEscID2,
	esG_CMD_GetEscID3,
	esG_CMD_GetEscID4,	
	esG_CMD_GetMotorDuty_Max,
	esG_CMD_GetMotorDuty_Min,
	esG_CMD_GetMotorBeepVolumeDuty,
	esG_CMD_GetMotorStartupDuty,
	esG_CMD_GetMotorStartupInitialCycle,
	esG_CMD_GetMotorStartupFinalCycle,
	esG_CMD_GetMotorStartupFixedCycle,
	esG_CMD_GetMotorStartupRotateStep,
	esG_CMD_GetMotorStartup_ZC_Filter1,
	esG_CMD_GetMotorStartup_ZC_Filter2,
	esG_CMD_GetMotorStartup_BlockThreshold,
	esG_CMD_GetMotorRun_ZC_Filter1,
	esG_CMD_GetMotorRun_ZC_Filter2,
	esG_CMD_GetMototRunThrottle_SpeedUpRate,
	esG_CMD_GetMototRunThrottle_SlowDownRate,
	esG_CMD_GetMotorRun_BlockThreshold,
	esG_CMD_GetMotorRun_SpeedFilterPar1,
	esG_CMD_GetMotorRun_SpeedFilterPar3,
	esG_CMD_GetMotorRun_CWCCW,
	/*Set：23，下标24开始*/
	esG_CMD_SetEscID1,
	esG_CMD_SetEscID2,
	esG_CMD_SetEscID3,
	esG_CMD_SetEscID4,
	esG_CMD_SetMotorDuty_Max,
	esG_CMD_SetMotorDuty_Min,
	esG_CMD_SetMotorBeepVolumeDuty,
	esG_CMD_SetMotorStartupDuty,
	esG_CMD_SetMotorStartupInitialCycle,
	esG_CMD_SetMotorStartupFinalCycle,
	esG_CMD_SetMotorStartupFixedCycle,
	esG_CMD_SetMotorStartupRotateStep,
	esG_CMD_SetMotorStartup_ZC_Filter1,
	esG_CMD_SetMotorStartup_ZC_Filter2,
	esG_CMD_SetMotorStartup_BlockThreshold,
	esG_CMD_SetMotorRun_ZC_Filter1,
	esG_CMD_SetMotorRun_ZC_Filter2,
	esG_CMD_SetMototRunThrottle_SpeedUpRate,
	esG_CMD_SetMototRunThrottle_SlowDownRate,
	esG_CMD_SetMotorRun_BlockThreshold,
	esG_CMD_SetMotorRun_SpeedFilterPar1,
	esG_CMD_SetMotorRun_SpeedFilterPar3,
	esG_CMD_SetMotorRun_CWCCW,
	/*base function*/
	esG_CMD_Beep_Audio_0,
	esG_CMD_Beep_Audio_1,
	esG_CMD_Beep_Audio_2,
	/*save parameters*/
	esG_CMD_SaveMotor,
	/*motor unlock*/
	esG_CMD_MotorUnlock
}sG_CMDType;

typedef enum{
	esG_Slave_SendEHzDataOut = 0,
	esG_Slave_RepeatCmd,
	esG_Slave_SendData
}sGMode;

typedef struct{
	sGMode mode;
	uint16_t transmitBuffer[16 + 2];
	uint16_t receiveBuffer[16 + 2];
	uint16_t receiveData,transmitData;
	sG_CMDType cmdType;
	bool isSendOrReceive,isSendOrReceiveFinished;
}sGHandler;

extern sGHandler sG;
extern bool sG_ProtocolProcess(uint16_t* dataOut);
extern void sG_TransmitWithDMA(uint16_t value);
extern bool sG_ReceiveWithDMA(uint16_t* value);

STI void sG_DMA_Switch2Receive(void)
{
		/*接收时调整DMA传输 ： GPIOx->PDI -> ReceiveBuffer*/
	
		/*开始设定DMA*/
		DMA_CH0->DMA_SADR = (uint32_t)&GPIO1->PDI;
		DMA_CH0->DMA_DADR = (uint32_t)&sG.receiveBuffer[0];
		/*PDI是16位对齐的，receiveBuffer是16位对齐的，调整地址递增对象*/
		DMA_CH0->DMA_CCR &= ~(BIT9 | BIT8 | BIT6 | BIT4);
		DMA_CH0->DMA_CCR |= (BIT8 | BIT4); 
}

STI void sG_DMA_Switch2Transmit(void)
{
		/*发送时调整DMA传输 ： TransmitBuffer -> TIMERx->CMPx*/
	
		/*开始设定DMA*/
		DMA_CH0->DMA_SADR = (uint32_t)&sG.transmitBuffer[0];
		DMA_CH0->DMA_DADR = (uint32_t)&TIMER1->CMPT1;
		DMA_CH0->DMA_CCR &= ~(BIT9 | BIT8 | BIT6 | BIT4);
		DMA_CH0->DMA_CCR |= (BIT9 | BIT6);
}

#endif

