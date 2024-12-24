#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#include <stdint.h>

/*在这里添加用户头文件*/
#include "hardware_init.h"

#define STI static inline
#define sG_Logical1_DMA_Value (60u * 4u)
#define sG_Logical0_DMA_Value (30u * 4u)

/*在这里设定最大和最小的sG600协议每个数据位的持续脉宽（用来做协议类别分析），以及相应情况下的位采样点*/
#define sG600_MaxPulseWidth (80u + 10u)
#define sG600_MinPulseWidth (80u - 10u)
#define sG600_SamplingPoint (40u)
/*在这里设定最大和最小的sG300协议每个数据位的持续脉宽（用来做协议类别分析）*/
#define sG300_MaxPulseWidth (sG600_MaxPulseWidth * 2)
#define sG300_MinPulseWidth (sG600_MinPulseWidth * 2)
#define sG300_SamplingPoint (sG600_SamplingPoint * 2)
/*在这里设定最大和最小的sG150协议每个数据位的持续脉宽（用来做协议类别分析）*/
#define sG150_MaxPulseWidth (sG600_MaxPulseWidth * 4)
#define sG150_MinPulseWidth (sG600_MinPulseWidth * 4)
#define sG150_SamplingPoint (sG600_SamplingPoint * 4)

/*====================与UTimer相关的函数设定=======================*/

/*在这里设定接收时的采样点的函数*/


/*====================一些预定义的系统变量类型，请勿做修改===================*/

typedef enum{
	eProtocol_Type_Unkown = -1,
	eProtocol_Type_sG600 = 0,
	eProtocol_Type_sG300 = 1,
	eProtocol_Type_sG150 = 2
}ProtocolType;

typedef enum{
	sG_CMD_MC_Stop = 0,
	sG_CMD_Beep1 = 1,
	sG_CMD_Beep2 = 2,
	sG_CMD_Beep3 = 3,
	sG_CMD_Beep4 = 4,
	sG_CMD_Beep5 = 5,
	sG_CMD_ESC_Info = 6,
	sG_CMD_SPIN_Direction_1 = 7,
	sG_CMD_SPIN_Direction_2 = 8,
	sG_CMD_3D_Mode_Off = 9,
	sG_CMD_3D_Mode_On = 10,
	sG_CMD_Settings_Request = 11,
	sG_CMD_Settings_Save = 12,
	sG_CMD_SPIN_Direction_Normal = 13,
	sG_CMD_SPIN_Direction_Reverse = 14,
	sG_CMD_LED0_On = 15,
	sG_CMD_LED1_On = 16,
	sG_CMD_LED2_On = 17,
	sG_CMD_LED3_On = 18,
	sG_CMD_LED0_Off = 19,
	sG_CMD_LED1_Off = 20,
	sG_CMD_LED2_Off = 21,
	sG_CMD_LED3_Off = 22
}sGCmdType;

typedef enum{
	sG_Prog_Initial_Power = 0
}sGProgType;

typedef enum{
	eProtocol_Sys_Reset = 0,
	eProtocol_Sys_TypeCheck,
	eProtocol_Sys_Polling
}ProtocolStatus;

typedef struct{
	uint16_t transmitBuffer[16 + 2];
	uint16_t receiveBuffer[16];
	uint16_t receiveSamplingPoint;
	uint16_t signalPulseWidth;
	uint16_t testData;
	ProtocolStatus status;
	ProtocolType type;
	uint8_t signalFrameCounter;
}ProtocolHandler;

extern ProtocolHandler protocolHandler;
extern void (*protocolAnalysisFunc[])(void);

/*这里存放的是可供用户直接调用的函数*/

extern void protocol_PollingTask(void);

#endif

