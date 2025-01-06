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

typedef struct{
	uint16_t transmitBuffer[16 + 2];
	uint16_t receiveBuffer[16 + 2];
	uint16_t receiveSamplingPoint;
	uint16_t signalPulseWidth;
	uint16_t testData;
	uint8_t signalFrameCounter;
	bool isSendOrReceive,isSendOrReceiveFinished;
}sGHandler;

extern sGHandler sG;
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

