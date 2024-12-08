#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#include <stdint.h>

/*在这里添加用户头文件*/
#include "hardware_init.h"

#define STI static inline
#define dShot_Logical1_DMA_Value (60u * 4u)
#define dShot_Logical0_DMA_Value (30u * 4u)

/*在这里设定最大和最小的dShot600协议每个数据位的持续脉宽（用来做协议类别分析），以及相应情况下的位采样点*/
#define dShot600_MaxPulseWidth (80u + 10u)
#define dShot600_MinPulseWidth (80u - 10u)
#define dShot600_SamplingPoint (40u)
/*在这里设定最大和最小的dShot300协议每个数据位的持续脉宽（用来做协议类别分析）*/
#define dShot300_MaxPulseWidth (dShot600_MaxPulseWidth * 2)
#define dShot300_MinPulseWidth (dShot600_MinPulseWidth * 2)
#define dShot300_SamplingPoint (dShot600_SamplingPoint * 2)
/*在这里设定最大和最小的dShot150协议每个数据位的持续脉宽（用来做协议类别分析）*/
#define dShot150_MaxPulseWidth (dShot600_MaxPulseWidth * 4)
#define dShot150_MinPulseWidth (dShot600_MinPulseWidth * 4)
#define dShot150_SamplingPoint (dShot600_SamplingPoint * 4)

/*====================与UTimer相关的函数设定=======================*/

/*在这里设定dShot接收时的采样点的函数*/


/*====================一些预定义的系统变量类型，请勿做修改===================*/

typedef enum{
	eProtocol_Type_Unkown = -1,
	eProtocol_Type_dShot600 = 0,
	eProtocol_Type_dShot300 = 1,
	eProtocol_Type_dShot150 = 2
}ProtocolType;

typedef enum{
	eProtocol_Sys_Reset = 0,
	eProtocol_Sys_TypeCheck,
	eProtocol_Sys_Polling
}ProtocolStatus;

typedef struct{
	uint16_t dShotTransmitBuffer[16 + 2];
	uint16_t dShotReceiveBuffer[16];
	uint16_t dShotReceiveSamplingPoint;
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

